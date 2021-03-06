//
// DlgCloseMode.h
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


class CCloseModeDlg : public CSkinDialog
{
// Construction
public:
	CCloseModeDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_CLOSE_MODE };

// Dialog Data
public:
	//{{AFX_DATA(CCloseModeDlg)
	int		m_nMode;
	//}}AFX_DATA

// Overrides
protected:
	//{{AFX_VIRTUAL(CCloseModeDlg)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CCloseModeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	//DECLARE_MESSAGE_MAP()
};
