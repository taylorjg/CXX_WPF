#ifndef _CWineDemoDlg_
#define _CWineDemoDlg_

#include "WineList.h"

class CWineListCtrl;

class CWineDemoDlg : public CDialog
{
// Construction
public:
	CWineDemoDlg (CWnd* pParent = NULL);
	~CWineDemoDlg ();

// Dialog Data
	//{{AFX_DATA(CWineDemoDlg)
	enum { IDD = IDD_WINEDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWineDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon16;
	HICON m_hIcon32;

	// Generated message map functions
	//{{AFX_MSG(CWineDemoDlg)
	virtual BOOL OnInitDialog ();
	afx_msg void OnSysCommand (UINT nID, LPARAM lParam);
	afx_msg void OnPaint ();
	afx_msg void OnSize (UINT nType, int cx, int cy);
	afx_msg LRESULT OnNcHitTest (CPoint point);
	afx_msg HCURSOR OnQueryDragIcon ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP ()

private:

	// We use these member variables to hold the current size of the window.
	int m_cx;
	int m_cy;

	CWineListCtrl* m_pWineListCtrl;
	CWineList m_WineListCtrl;
	CStatic m_lblSeparator;
	CButton m_btnOK;
	CButton m_btnCancel;

	// These member variables hold the current size of each of the controls
	// on the window. We use these to help resize and reposition the controls
	// when resizing the window.
	CRect m_rcWineListCtrl;
	CRect m_rcSeparator;
	CRect m_rcOK;
	CRect m_rcCancel;
	CRect m_rcGripper;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
