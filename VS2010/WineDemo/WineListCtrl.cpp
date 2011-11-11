/*
 * References:
 *
 * Advanced Control Programming
 *   Owner-Draw List Boxes
 * http://aclacl.brinkster.net/MFC/ch07c.htm
 *
 * Displaying a JPG in your MFC Application
 * http://msdn.microsoft.com/en-us/magazine/cc301454.aspx
 */

#include "stdafx.h"
#include "WineDemo.h"
#include "WineListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWineListCtrl, CListBox)
	//{{AFX_MSG_MAP(CWineListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
//* Function Name: Constructor
//*   Description: 
//*****************************************************************************
CWineListCtrl::CWineListCtrl ()
{
}


//*****************************************************************************
//* Function Name: Destructor
//*   Description: 
//*****************************************************************************
CWineListCtrl::~CWineListCtrl ()
{
}


//*****************************************************************************
//* Function Name: PreCreateWindow
//*   Description: 
//*****************************************************************************
BOOL CWineListCtrl::PreCreateWindow (CREATESTRUCT& p_cs) 
{
	p_cs.style &= ~LBS_SORT;
	p_cs.dwExStyle |= WS_EX_CLIENTEDGE;

	return CListBox::PreCreateWindow (p_cs);
}


//*****************************************************************************
//* Function Name: MeasureItem
//*   Description: 
//*****************************************************************************
void CWineListCtrl::MeasureItem (LPMEASUREITEMSTRUCT p_pMeasureItemStruct) 
{
	p_pMeasureItemStruct->itemHeight = 100;
}


//*****************************************************************************
//* Function Name: DrawItem
//*   Description: 
//*****************************************************************************
void CWineListCtrl::DrawItem (LPDRAWITEMSTRUCT p_pDrawItemStruct) 
{
	CDC l_dc;
	l_dc.Attach (p_pDrawItemStruct->hDC);

	CRect l_rcItem = p_pDrawItemStruct->rcItem;
	UINT l_nIndex = p_pDrawItemStruct->itemID;

	BOOL l_bSelected = p_pDrawItemStruct->itemState & ODS_SELECTED;
	CBrush* l_pBrush = new CBrush (::GetSysColor ((l_bSelected) ? COLOR_HIGHLIGHT : COLOR_WINDOW));
	l_dc.FillRect (l_rcItem, l_pBrush);
	delete l_pBrush;

	if (p_pDrawItemStruct->itemState & ODS_FOCUS) {
		l_dc.DrawFocusRect (l_rcItem);
	}

	if (l_nIndex != static_cast<UINT>(-1)) {

		CItemData* l_pItemData = reinterpret_cast<CItemData*>(p_pDrawItemStruct->itemData);

		const CProduct* l_pProduct = l_pItemData->GetProduct ();
		boost::shared_ptr<CLabel> l_pLabel = l_pProduct->GetLabel ();
		IPicturePtr l_spPicture = l_pItemData->GetPicture ();
		bool l_bPictureLoaded = l_spPicture;

		if (!l_bPictureLoaded) {

			CString l_strLabelLargeUrl  = l_pLabel->GetLargeUrl ();
			CString l_strLabelMediumUrl = l_pLabel->GetMediumUrl ();

			HRESULT l_hr = E_FAIL;

			if (!l_strLabelLargeUrl.IsEmpty ()) {
				l_hr = OleLoadPicturePath (
					_bstr_t (l_strLabelLargeUrl),
					NULL,
					0,
					0,
					__uuidof (l_spPicture),
					reinterpret_cast<void**> (&l_spPicture));
			}

			if (FAILED (l_hr)) {
				if (!l_strLabelMediumUrl.IsEmpty ()) {
					l_hr = OleLoadPicturePath (
						_bstr_t (l_strLabelMediumUrl),
						NULL,
						0,
						0,
						__uuidof (l_spPicture),
						reinterpret_cast<void**> (&l_spPicture));
				}
			}

			if (SUCCEEDED (l_hr)) {
				// Cache the loaded picture in the item data.
				l_pItemData->SetPicture (l_spPicture);
				l_bPictureLoaded = true;
			}
		}

		if (l_bPictureLoaded) {

			OLE_XSIZE_HIMETRIC l_Width;
			OLE_YSIZE_HIMETRIC l_Height;

			l_spPicture->get_Width  (&l_Width);
			l_spPicture->get_Height (&l_Height);

			l_spPicture->Render (
				p_pDrawItemStruct->hDC,
				l_rcItem.left + 2,
				l_rcItem.top + 2,
				96,
				96,
				0,
				l_Height,
				l_Width,
				-l_Height,
				NULL);
		}

		INT l_iTextLeft = l_rcItem.left + 110;
		INT l_iTextTop = l_rcItem.top + 5;

		l_dc.TextOut (l_iTextLeft, l_iTextTop, l_pProduct->GetName ());

		l_iTextTop += 18;
		CString l_strVintage;
		l_strVintage.Format (_T("Vintage: %s"), l_pProduct->GetVintage ());
		l_dc.TextOut (l_iTextLeft, l_iTextTop, l_strVintage);

		l_iTextTop += 18;
		CString l_strPrice;
		l_strPrice.Format (
			_T("Price: min $%6.2f, max $%6.2f, retail $%6.2f"),
			l_pProduct->GetPriceMin (),
			l_pProduct->GetPriceMax (),
			l_pProduct->GetPriceRetail ());
		l_dc.TextOut (l_iTextLeft, l_iTextTop, l_strPrice);

		l_iTextTop += 18;
		CString l_strUrl;
		l_strUrl.Format (_T("Url: %s"), l_pProduct->GetUrl ());
		l_dc.TextOut (l_iTextLeft, l_iTextTop, l_strUrl);
	}

	l_dc.Detach ();
}


//*****************************************************************************
//* Function Name: DrawItem
//*   Description: 
//*****************************************************************************
void CWineListCtrl::DeleteItem (LPDELETEITEMSTRUCT p_pDeleteItemStruct) 
{
	CItemData* l_pItemData = reinterpret_cast<CItemData*>(p_pDeleteItemStruct->itemData);
	delete l_pItemData;

	CListBox::DeleteItem (p_pDeleteItemStruct);
}
