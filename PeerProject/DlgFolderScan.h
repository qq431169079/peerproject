//
// DlgFolderScan.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2010
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

#include "DlgSkinDialog.h"


class CFolderScanDlg : public CSkinDialog
{
// Construction
public:
	CFolderScanDlg(CWnd* pParent = NULL);
	virtual ~CFolderScanDlg();

	enum { IDD = IDD_FOLDER_SCAN };

// Dialog Data
public:
	//{{AFX_DATA(CFolderScanDlg)
	CStatic	m_wndVolume;
	CStatic	m_wndFiles;
	CStatic	m_wndFile;
	//}}AFX_DATA

// Operations
public:
	static void Update(LPCTSTR pszName, DWORD nVolume);	//, BOOL bLock);
	void	InstanceUpdate(LPCTSTR pszName, DWORD nVolume);

// Data
protected:
	static	CFolderScanDlg*	m_pDialog;
	DWORD	m_nCookie;
	DWORD	m_nFiles;
	DWORD	m_nVolume;
	DWORD	m_tLastUpdate;
	BOOL	m_bActive;

// Overrides
protected:
	//{{AFX_VIRTUAL(CFolderScanDlg)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CFolderScanDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
