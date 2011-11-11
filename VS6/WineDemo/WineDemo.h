#ifndef _CWineDemoApp_h_
#define _CWineDemoApp_h_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CWineDemoApp : public CWinApp
{
public:
	CWineDemoApp ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWineDemoApp)
	public:
	virtual BOOL InitInstance ();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWineDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
