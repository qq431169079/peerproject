//
// PongCache.cpp
//
// This file is part of PeerProject (peerproject.org) � 2008-2010
// Portions Copyright Shareaza Development Team, 2002-2007.
//
// PeerProject is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or later version (at your option).
//
// PeerProject is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 3.0
// along with PeerProject; if not, write to Free Software Foundation, Inc.
// 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA  (www.fsf.org)
//

#include "StdAfx.h"
#include "PeerProject.h"
#include "Settings.h"
#include "Network.h"
#include "PongCache.h"
#include "G1Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// CPongCache construction

CPongCache::CPongCache()
	: m_nTime ( 0 )
{
}

CPongCache::~CPongCache()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// CPongCache clear

void CPongCache::Clear()
{
	for ( POSITION pos = m_pCache.GetHeadPosition() ; pos ; )
	{
		CPongItem* pItem = m_pCache.GetNext( pos );
		delete pItem;
	}

	m_pCache.RemoveAll();

	m_nTime = GetTickCount();
}

BOOL CPongCache::ClearIfOld()
{
	ASSUME_LOCK( Network.m_pSection );

	if ( GetTickCount() - m_nTime >= Settings.Gnutella1.PongCache )
	{
		Clear();
		return TRUE;
	}

	return FALSE;
}

void CPongCache::ClearNeighbour(CNeighbour* pNeighbour)
{
	ASSUME_LOCK( Network.m_pSection );

	for ( POSITION pos = m_pCache.GetHeadPosition() ; pos ; )
	{
		CPongItem* pItem = m_pCache.GetNext( pos );
		if ( pItem->m_pNeighbour == pNeighbour )
		{
			delete pItem;
			m_pCache.RemoveAt( pos );
		}
	}

	m_nTime = GetTickCount();
}

//////////////////////////////////////////////////////////////////////
// CPongCache add

CPongItem* CPongCache::Add(CNeighbour* pNeighbour, IN_ADDR* pAddress, WORD nPort, BYTE nHops, DWORD nFiles, DWORD nVolume)
{
	ASSUME_LOCK( Network.m_pSection );

	for ( POSITION pos = m_pCache.GetHeadPosition() ; pos ; )
	{
		CPongItem* pItem = m_pCache.GetNext( pos );

		if ( pItem->m_nPort != nPort ) continue;
		if ( pItem->m_nHops != nHops ) continue;

		if ( memcmp( &pItem->m_pAddress, pAddress, sizeof(IN_ADDR) ) == 0 )
		{
			pItem->m_nFiles		= nFiles;
			pItem->m_nVolume	= nVolume;
			return pItem;
		}
	}

	CPongItem* pItem = new CPongItem( pNeighbour, pAddress, nPort, nHops, nFiles, nVolume );

	m_pCache.AddTail( pItem );

	return pItem;
}

//////////////////////////////////////////////////////////////////////
// CPongCache lookup

CPongItem* CPongCache::Lookup(CNeighbour* pNotFrom, BYTE nHops, CList< CPongItem* >* pIgnore)
{
	ASSUME_LOCK( Network.m_pSection );

	for ( POSITION pos = m_pCache.GetHeadPosition() ; pos ; )
	{
		CPongItem* pItem = m_pCache.GetNext( pos );

		if ( pItem->m_nHops != nHops ) continue;
		if ( pItem->m_pNeighbour == pNotFrom ) continue;

		if ( pIgnore && pIgnore->Find( pItem ) ) continue;

		return pItem;
	}

	return NULL;
}

CPongItem* CPongCache::Lookup(CNeighbour* pFrom)
{
	ASSUME_LOCK( Network.m_pSection );

	for ( POSITION pos = m_pCache.GetHeadPosition() ; pos ; )
	{
		CPongItem* pItem = m_pCache.GetNext( pos );

		if ( pItem->m_pNeighbour == pFrom )
			return pItem;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
// CPongCache list access

//POSITION CPongCache::GetIterator() const
//{
//	ASSUME_LOCK( Network.m_pSection );
//
//	return m_pCache.GetHeadPosition();
//}

//CPongItem* CPongCache::GetNext(POSITION& pos) const
//{
//	ASSUME_LOCK( Network.m_pSection );
//
//	return m_pCache.GetNext( pos );
//}


//////////////////////////////////////////////////////////////////////
// CPongItem construction

CPongItem::CPongItem(CNeighbour* pNeighbour, IN_ADDR* pAddress, WORD nPort, BYTE nHops, DWORD nFiles, DWORD nVolume)
	: m_pNeighbour	( pNeighbour )
	, m_pAddress	( *pAddress )
	, m_nPort		( nPort )
	, m_nHops		( nHops )
	, m_nFiles		( nFiles )
	, m_nVolume		( nVolume )
{
}

CPongItem::~CPongItem()
{
}

//////////////////////////////////////////////////////////////////////
// CPongItem packet conversion

CG1Packet* CPongItem::ToPacket(int nTTL, const Hashes::Guid& oGUID)
{
	CG1Packet* pPong = CG1Packet::New( G1_PACKET_PONG, nTTL, oGUID );

	if ( pPong != NULL )
	{
		pPong->m_nHops = m_nHops;

		pPong->WriteShortLE( m_nPort );
		pPong->WriteLongLE( *(DWORD*)&m_pAddress );
		pPong->WriteLongLE( m_nFiles );
		pPong->WriteLongLE( m_nVolume );
	}

	return pPong;
}
