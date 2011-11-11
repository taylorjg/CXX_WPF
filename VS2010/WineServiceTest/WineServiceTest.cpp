#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <afx.h>
#include <stdio.h>
#include <tchar.h>

#include "WineService.h"

//*****************************************************************************
//* Function Name: main
//*   Description: 
//*****************************************************************************
int main ()
{
	CoInitializeEx (NULL, COINIT_APARTMENTTHREADED);

	CWineServiceContext l_WineServiceContext ("http://wine.cloudapp.net");

	ProductDataServiceQueryPtr l_pProductQuery (l_WineServiceContext.GetProducts ());
	l_pProductQuery->AddQueryOption ("apikey", API_KEY);
	l_pProductQuery->AddQueryOption ("$top", "5");

	CEntityCollection<CProduct>::type l_pProducts = l_pProductQuery->Execute ();

	for (auto it = l_pProducts->begin (); it != l_pProducts->end (); ++it) {

		const CProduct* l_pProduct = (*it).get ();

		(void) _tprintf (
			_T("Id: %s; Name: %s; Description: %s\n"),
			l_pProduct->GetId (),
			l_pProduct->GetName (),
			l_pProduct->GetDescription ());

		(void) _tprintf (
			_T("PriceMin: %6.2f; PriceMax: %6.2f; PriceRetail: %6.2f\n"),
			l_pProduct->GetPriceMin (),
			l_pProduct->GetPriceMax (),
			l_pProduct->GetPriceRetail ());

		(void) _tprintf (
			_T("Type: %s; Url: %s; Vintage: %s; Year: %s\n"),
			l_pProduct->GetType (),
			l_pProduct->GetUrl (),
			l_pProduct->GetVintage (),
			l_pProduct->GetYear ());

		boost::shared_ptr<CLabel> l_pLabel = l_pProduct->GetLabel ();
		if (l_pLabel) {
			(void) _tprintf (_T("Label Url (M): %s\n"), l_pLabel->GetMediumUrl ());
			(void) _tprintf (_T("Label Url (L): %s\n"), l_pLabel->GetLargeUrl ());
		}

		boost::shared_ptr<CGeoLocation> l_pGeoLocation = l_pProduct->GetGeoLocation ();
		if (l_pGeoLocation) {
			(void) _tprintf (_T("Latitude: %s\n"), l_pGeoLocation->GetLatitude ());
			(void) _tprintf (_T("Longitude: %s\n"), l_pGeoLocation->GetLongitude ());
			(void) _tprintf (_T("Url: %s\n"), l_pGeoLocation->GetUrl ());
		}

		(void) _tprintf (_T("\n"));
	}

	CoUninitialize ();

	return 0;
}
