#include "stdafx.h"
#include "InternalUrlInvoker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//*****************************************************************************
//* Function Name: InvokeUrl
//*   Description: 
//*****************************************************************************
_bstr_t CInternalUrlInvoker::InvokeUrl (
	const _bstr_t& p_sbstrMethod,
	const _bstr_t& p_sbstrUrl)
{
	_bstr_t l_sbstrResponse;

	try {
		MSXML2::IServerXMLHTTPRequestPtr l_spXMLHTTPRequest;
		HRESULT l_hr = l_spXMLHTTPRequest.CreateInstance (__uuidof (MSXML2::ServerXMLHTTP));
		if (FAILED (l_hr)) _com_issue_error (l_hr);

		l_spXMLHTTPRequest->open (p_sbstrMethod, p_sbstrUrl, false /* varAsync */);
		l_spXMLHTTPRequest->send ();

		long l_lStatus = l_spXMLHTTPRequest->status;
		_bstr_t l_sbstrStatusText = l_spXMLHTTPRequest->statusText;

		l_sbstrResponse = l_spXMLHTTPRequest->responseText;
	}
	catch (const _com_error& _ce) {
		(void) _ftprintf (stderr, _T("HRESULT: 0x%08X\n"), _ce.Error ());
	}

	return l_sbstrResponse;
}
