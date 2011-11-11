#include "stdafx.h"
#include "WineList.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Interop;

BEGIN_MESSAGE_MAP(CWineList, CWnd)
	ON_WM_CREATE ()
	ON_WM_SIZE ()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CWineList, CWnd)

//*****************************************************************************
//* Function Name: Constructor
//*   Description: 
//*****************************************************************************
CWineList::CWineList () :
	m_ObjHandle (nullptr)
{
}


//*****************************************************************************
//* Function Name: Destructor
//*   Description: 
//*****************************************************************************
CWineList::~CWineList ()
{
}


//*****************************************************************************
//* Function Name: OnCreate
//*   Description: 
//*****************************************************************************
int CWineList::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate (lpCreateStruct) == -1)
		return -1;

	WineDemoUserControls::WineList^ control = gcnew WineDemoUserControls::WineList ();
	m_ObjHandle = control;

	CRect rect;
	GetClientRect (&rect);

	HwndSourceParameters sourceParams ("CustomHost");
	sourceParams.PositionX = 0;
	sourceParams.PositionY = 0;
	sourceParams.Width = rect.Width ();
	sourceParams.Height = rect.Height ();
	sourceParams.ParentWindow = (IntPtr)m_hWnd;
	sourceParams.WindowStyle = WS_VISIBLE | WS_CHILD; 

	HwndSource^ source = gcnew HwndSource (sourceParams);
	source->SizeToContent = SizeToContent::WidthAndHeight;
	source->RootVisual = control;

	return 0;
}


//*****************************************************************************
//* Function Name: OnSize
//*   Description: 
//*****************************************************************************
void CWineList::OnSize (UINT nType, int cx, int cy) 
{
	CWnd::OnSize (nType, cx, cy);

	if (m_ObjHandle) {
		CRect rect;
		GetClientRect (&rect);
		m_ObjHandle->Width = rect.Width ();
		m_ObjHandle->Height = rect.Height ();
	}
}


//*****************************************************************************
//* Function Name: DisplayProducts
//*   Description: 
//*****************************************************************************
void CWineList::DisplayProducts (const CEntityCollection<CProduct>::type& p_mfcProducts)
{
	auto l_ProductList = gcnew List<Product^> ();

	for (auto it = p_mfcProducts.get ()->begin (); it != p_mfcProducts.get ()->end (); ++it) {
		const CProduct& l_mfcProduct = *(*it).get ();
		auto l_Product = gcnew Product (l_mfcProduct);
		l_ProductList->Add (l_Product);
	}

	m_ObjHandle->Products = l_ProductList;
}
