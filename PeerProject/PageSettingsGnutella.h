//
// PageSettingsGnutella.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2012
// Portions copyright Shareaza Development Team, 2002-2007.
//
// PeerProject is free software. You may redistribute and/or modify it
// under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation (fsf.org);
// version 3 or later at your option. (AGPLv3)
//
// PeerProject is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Affero General Public License 3.0 for details:
// (http://www.gnu.org/licenses/agpl.html)
//

#pragma once

#include "WndSettingsPage.h"


class CGnutellaSettingsPage : public CSettingsPage
{
	DECLARE_DYNCREATE(CGnutellaSettingsPage)

// Construction
public:
	CGnutellaSettingsPage();
	virtual ~CGnutellaSettingsPage();

	enum { IDD = IDD_SETTINGS_GNUTELLA };

// Dialog Data
public:
	//{{AFX_DATA(CGnutellaSettingsPage)
	CSpinButtonCtrl	m_wndG2Peers;
	CSpinButtonCtrl	m_wndG2Leafs;
	CSpinButtonCtrl	m_wndG2Hubs;
	CSpinButtonCtrl	m_wndG1Peers;
	CSpinButtonCtrl	m_wndG1Leafs;
	CSpinButtonCtrl	m_wndG1Hubs;
	BOOL	m_bG2Today;
	BOOL	m_bG2Always;
	BOOL	m_bG1Today;
	BOOL	m_bG1Always;
	CComboBox m_wndG2ClientMode;
	CComboBox m_wndG1ClientMode;
	int		m_nG2Hubs;
	int		m_nG2Leafs;
	int		m_nG2Peers;
	int		m_nG1Hubs;
	int		m_nG1Leafs;
	int		m_nG1Peers;
	BOOL	m_bDeflateHub2Hub;
	BOOL	m_bDeflateLeaf2Hub;
	BOOL	m_bDeflateHub2Leaf;
	BOOL	m_bAgent;
	//}}AFX_DATA

// Overrides
public:
	//{{AFX_VIRTUAL(CGnutellaSettingsPage)
	virtual BOOL OnSetActive();
	virtual void OnOK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CGnutellaSettingsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnG2Today();
	afx_msg void OnG1Today();
	afx_msg void OnG2Always();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
