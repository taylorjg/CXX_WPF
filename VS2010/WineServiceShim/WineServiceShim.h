// WineServiceShim.h : main header file for the WineServiceShim DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWineServiceShimApp
// See WineServiceShim.cpp for the implementation of this class
//

class CWineServiceShimApp : public CWinApp
{
public:
	CWineServiceShimApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
