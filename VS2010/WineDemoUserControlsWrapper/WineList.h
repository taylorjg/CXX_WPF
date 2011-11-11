#pragma once

#include "..\WineService\WineService.h"
//#include "..\WineServiceShim\Product.h"

class AFX_EXT_CLASS CWineList : public CWnd
{
	DECLARE_DYNAMIC(CWineList)

public:
	CWineList ();
	virtual ~CWineList ();

	void DisplayProducts (const CEntityCollection<CProduct>::type& p_mfcProducts);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize (UINT nType, int cx, int cy);

private:
#ifdef _MANAGED
	gcroot<WineDemoUserControls::WineList^> m_ObjHandle;
#else
	intptr_t m_ObjHandle;
#endif
};
