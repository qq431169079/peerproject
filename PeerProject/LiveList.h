//
// LiveList.h
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

#pragma once


class CLiveItem : public CObject
{
	DECLARE_DYNAMIC( CLiveItem )

public:
	CLiveItem(int nColumns, DWORD_PTR nParam);
	virtual ~CLiveItem();

#ifdef _DEBUG
	virtual void AssertValid() const
	{
		CObject::AssertValid();
		ASSERT( m_nImage >= I_IMAGECALLBACK && m_nImage < 1000 );
		ASSERT( m_pColumn );
	}
#endif

	void	Set(int nColumn, LPCTSTR pszText);
	void	SetImage(int nImage);
	void	SetMaskOverlay(UINT nMaskOverlay);
	void	Format(int nColumn, LPCTSTR pszFormat, ...);
	int		Add(CListCtrl* pCtrl, int nItem, int nColumns);
	BOOL	Update(CListCtrl* pCtrl, int nItem, int nColumns);
	BOOL	SetImage(CListCtrl* pCtrl, int nParam, int nColumn, int nImageIndex);

public:
	DWORD_PTR	m_nParam;
	int			m_nImage;
	UINT		m_nMaskOverlay;
	UINT		m_nMaskState;
	CString*	m_pColumn;
	UINT		m_nModified;	// Modified columns (bitmask)
	bool		m_bModified;	// Is data modified?
	bool		m_bOld;			// Is item old? (marked for deletion)
};

typedef CLiveItem* CLiveItemPtr;


class CLiveList : public CObject
{
	DECLARE_DYNAMIC( CLiveList )

public:
	CLiveList(int nColumns, UINT nHash = 0);
	virtual ~CLiveList();

public:
	static CBitmap		m_bmSortAsc;
	static CBitmap		m_bmSortDesc;

#ifdef _DEBUG
	virtual void		AssertValid() const
	{
		CObject::AssertValid();
		ASSERT( m_nColumns > 0 && m_nColumns < 100 );
		ASSERT_VALID( &m_pItems );
		ASSERT_VALID( &m_pSection );
		ASSERT_VALID( &m_bmSortAsc );
		ASSERT_VALID( &m_bmSortDesc );
	}
#endif

protected:
	typedef CMap< DWORD_PTR, DWORD_PTR, CLiveItem*, CLiveItem*& > CLiveItemMap;

	CLiveItemMap		m_pItems;
	CCriticalSection	m_pSection;
	int					m_nColumns;

public:
	CLiveItem*			Add(DWORD_PTR nParam);
	CLiveItem*			Add(LPVOID pParam);
	void				Apply(CListCtrl* pCtrl, BOOL bSort = FALSE);

// Sort Helpers
	static void			Sort(CListCtrl* pCtrl, int nColumn = -1, BOOL bGraphic = TRUE);
	static int CALLBACK	SortCallback(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int			SortProc(LPCTSTR sA, LPCTSTR sB, BOOL bNumeric = FALSE);
	static bool			Less(const CLiveItemPtr& _Left, const CLiveItemPtr& _Right, int nSortColumn);
	static inline BOOL	IsNumber(LPCTSTR pszString);

// Drag Helpers
	static HBITMAP		CreateDragImage(CListCtrl* pList, const CPoint& ptMouse, CPoint& ptMiddle);
	static CImageList*	CreateDragImage(CListCtrl* pList, const CPoint& ptMouse);

protected:
	void				Clear();
};


#ifndef CDRF_NOTIFYSUBITEMDRAW	// Prior to Win98/IE4 (Obsolete)

#define CDRF_NOTIFYSUBITEMDRAW	0x00000020
#define CDDS_SUBITEM			0x00020000

#define LVS_EX_DOUBLEBUFFER 	0x00010000
#define LVS_EX_NOHSCROLL		0x10000000
#define LVS_EX_FLATSB			0x00000100
#define LVS_EX_REGIONAL			0x00000200
#define LVS_EX_INFOTIP			0x00000400
#define LVS_EX_LABELTIP			0x00004000
#define LVS_EX_UNDERLINEHOT		0x00000800
#define LVS_EX_UNDERLINECOLD	0x00001000
#define LVS_EX_MULTIWORKAREAS	0x00002000

#define LVM_GETSUBITEMRECT      (LVM_FIRST + 56)
#define ListView_GetSubItemRect(hwnd, iItem, iSubItem, code, prc) \
	(BOOL)SNDMSG((hwnd), LVM_GETSUBITEMRECT, (WPARAM)(int)(iItem), \
	((prc) ? ((((LPRECT)(prc))->top = iSubItem), (((LPRECT)(prc))->left = code), (LPARAM)(prc)) : (LPARAM)(LPRECT)NULL))

#endif // CDRF_NOTIFYSUBITEMDRAW


class CLiveListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CLiveListCtrl)

public:
	CLiveListCtrl();
	virtual ~CLiveListCtrl();

protected:
	typedef std::map< DWORD_PTR, CLiveItemPtr >		CLiveMap;
	typedef std::pair< DWORD_PTR, CLiveItemPtr >	CLiveMapPair;
	typedef std::vector< CLiveItemPtr >				CLiveIndex;

	CLiveMap		m_pItems;
	CLiveIndex		m_pIndex;
	int				m_nColumns;

public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int nColumns);

	void Apply();
	void Sort(int nColumn = -1);

	CLiveItemPtr Add(DWORD_PTR nParam);
	CLiveItemPtr Add(LPVOID pParam);

	DWORD_PTR GetItemData(int nItem) const;
	UINT GetItemOverlayMask(int nItem) const;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnGetDispInfo(NMHDR *pNMHDR, LRESULT *pResult);	// OnLvnGetDispInfoW/OnLvnGetDispInfoA
	afx_msg void OnLvnOdFindItem(NMHDR *pNMHDR, LRESULT *pResult);	// OnLvnOdFindItemW/OnLvnOdFindItemA
	afx_msg void OnLvnOdCacheHint(NMHDR *pNMHDR, LRESULT *pResult);
};
