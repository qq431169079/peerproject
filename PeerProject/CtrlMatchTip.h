//
// CtrlMatchTip.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2011
// Portions copyright Shareaza Development Team, 2002-2007.
//
// PeerProject is free software; you can redistribute it and/or
// modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation (fsf.org);
// either version 3 of the License, or later version at your option.
//
// PeerProject is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Affero General Public License 3.0 (AGPLv3) for details:
// (http://www.gnu.org/licenses/agpl.html)
//

#pragma once

#include "MetaList.h"

class CMatchFile;
class CQueryHit;


class CMatchTipCtrl : public CWnd
{
// Construction
public:
	CMatchTipCtrl();
	virtual ~CMatchTipCtrl();

// Attributes
protected:
	CWnd*			m_pOwner;
	BOOL			m_bVisible;
	CMatchFile*		m_pFile;
	CQueryHit*		m_pHit;
	CPoint			m_pOpen;
	DWORD			m_tOpen;
protected:
	CString			m_sName;
	CString			m_sUser;
	CString			m_sCountryCode;
	CString			m_sCountry;
	CString			m_sSHA1;
	CString			m_sTiger;
	CString			m_sED2K;
	CString			m_sBTH;
	CString			m_sMD5;
	CString			m_sType;
	CString			m_sSize;
	CString			m_sBusy;	// Busy status message
	CString			m_sPush;	// Firewalled status message
	CString			m_sUnstable; // Unstable status message
	int				m_nIcon;
	CString			m_sStatus;
	COLORREF		m_crStatus;
	CString			m_sPartial;
	CString			m_sQueue;
	CSchemaPtr		m_pSchema;
	CMetaList		m_pMetadata;
	int				m_nKeyWidth;
	int				m_nRating;

public:
	static LPCTSTR	m_hClass;	// CWnd Style
protected:
	static CBrush	m_brBack;
	static COLORREF	m_crBack;
	static COLORREF	m_crText;
	static COLORREF	m_crBorder;
	static COLORREF	m_crWarnings; // Color of warning messages

// Operations
public:
	void		Show(CMatchFile* pFile, CQueryHit* pHit);
	void		Hide();
protected:
	void		ShowInternal();
	void		LoadFromFile();
	void		LoadFromHit();
	BOOL		LoadTypeInfo();
	CSize		ComputeSize();
	void		ExpandSize(CDC& dc, CSize& sz, const CString& strText, int nBase = 0);
	void		DrawText(CDC& dc, CPoint& pt, const CString& strText);

// Overrides
public:
	//{{AFX_VIRTUAL(CMatchTipCtrl)
	virtual BOOL Create(CWnd* pParentWnd);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CMatchTipCtrl)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#define IDC_MATCH_TIP	111
