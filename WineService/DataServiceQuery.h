#ifndef _CDataServiceQuery_h_
#define _CDataServiceQuery_h_

#include "IUrlInvoker.h"
#include "IResponseDecoder.h"

#include <vector>

template<class T>
class AFX_EXT_CLASS CDataServiceQuery
{
public:
	CDataServiceQuery (
		IUrlInvoker*			p_pUrlInvoker,
		IResponseDecoder<T>*	p_pResponseDecoder,
		const CString&			p_strUrl,
		const CString&			p_strEntityName);

	CDataServiceQuery<T>& AddQueryOption (const CString& p_strName, const CString& p_strValue);

	CEntityCollection<T>::type Execute (void);

private:

	boost::scoped_ptr<IUrlInvoker>			m_pUrlInvoker;
	boost::scoped_ptr<IResponseDecoder<T> >	m_pResponseDecoder;

	CString			m_strUrl;
	CString			m_strEntityName;
	CStringArray	m_straNames;
	CStringArray	m_straValues;
};

//*****************************************************************************
//* Function Name: Constructor
//*   Description: 
//*****************************************************************************
template<class T>
CDataServiceQuery<T>::CDataServiceQuery (
	IUrlInvoker*			p_pUrlInvoker,
	IResponseDecoder<T>*	p_pResponseDecoder,
	const CString&			p_strUrl,
	const CString&			p_strEntityName) :
		m_pUrlInvoker		(p_pUrlInvoker),
		m_pResponseDecoder	(p_pResponseDecoder),
		m_strUrl			(p_strUrl),
		m_strEntityName		(p_strEntityName)
{
}


//*****************************************************************************
//* Function Name: AddQueryOption
//*   Description: 
//*****************************************************************************
template<class T>
CDataServiceQuery<T>& CDataServiceQuery<T>::AddQueryOption (const CString& p_strName, const CString& p_strValue)
{
	m_straNames.Add (p_strName);
	m_straValues.Add (p_strValue);

	return *this;
}


//*****************************************************************************
//* Function Name: Execute
//*   Description: 
//*****************************************************************************
template<class T>
CEntityCollection<T>::type CDataServiceQuery<T>::Execute (void)
{
	CEntityCollection<T>::type l_pEntityCollection (new std::vector<boost::shared_ptr<T> > ());

	try {
		// e.g. http://wine.cloudapp.net/Products()?apikey=2fd879a5765785c043cc992b550d2bda&$filter=(Id eq '91856')
		CString l_strUrl = m_strUrl;

		INT l_cchUrl = l_strUrl.GetLength ();
		if (l_cchUrl > 0 && l_strUrl[l_cchUrl - 1] != _T('/')) {
			l_strUrl += _T("/");
		}

		l_strUrl += m_strEntityName;
		l_strUrl += _T("()");

		for (INT l_iIndex = 0; l_iIndex < m_straNames.GetSize (); l_iIndex++) {
			l_strUrl += (l_iIndex == 0) ? _T("?") : _T("&");
			l_strUrl += m_straNames.GetAt (l_iIndex);
			l_strUrl += _T("=");
			l_strUrl += m_straValues.GetAt (l_iIndex);
		}

		_bstr_t l_sbstrResponse = m_pUrlInvoker->InvokeUrl (L"GET", _bstr_t (l_strUrl));
		m_pResponseDecoder->DecodeResponse (l_sbstrResponse, l_pEntityCollection);
	}
	catch (const _com_error& _ce) {
		(void) _ftprintf (stderr, _T("HRESULT: 0x%08X\n"), _ce.Error ());
	}

	return l_pEntityCollection;
}

#endif
