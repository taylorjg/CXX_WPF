#include "stdafx.h"
#include "EntityDecoder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//*****************************************************************************
//* Function Name: GetEntryProperties
//*   Description: 
//*****************************************************************************
void CEntityDecoder::GetEntryProperties (
	const _bstr_t&			p_sbstrResponse,
	std::vector<_bstr_t>&	p_EntryProperties)
{
	p_EntryProperties.clear ();

	try {
		MSXML2::IXMLDOMDocumentPtr l_spResponseDocument;
		HRESULT l_hr = l_spResponseDocument.CreateInstance (__uuidof (MSXML2::DOMDocument));
		if (FAILED (l_hr)) _com_issue_error (l_hr);

		if (l_spResponseDocument->loadXML (p_sbstrResponse) == VARIANT_TRUE) {

			MSXML2::IXMLDOMNodeListPtr l_spNodeList = l_spResponseDocument->selectNodes (L"//entry/m:properties");

			for (INT l_iNodeIndex = 0; l_iNodeIndex < l_spNodeList->length; l_iNodeIndex++) {
				MSXML2::IXMLDOMNodePtr l_spNode = l_spNodeList->item[l_iNodeIndex];
				_bstr_t l_sbstrEntryProperties = l_spNode->xml;
				p_EntryProperties.push_back (l_sbstrEntryProperties);
			}
		}
	}
	catch (const _com_error& _ce) {
		(void) _ftprintf (stderr, _T("HRESULT: 0x%08X\n"), _ce.Error ());
	}
}


//*****************************************************************************
//* Function Name: DecodeEntity
//*   Description: 
//*****************************************************************************
void CEntityDecoder::DecodeEntity (
	const _bstr_t&								p_sbstrXML,
	const std::vector<CPropertyDescriptor>&		p_PropertyDescriptorTable,
	const std::vector<CComplexTypeDescriptor>&	p_ComplexTypeDescriptorTable)
{
	try {
		MSXML2::IXMLDOMDocumentPtr l_spDocument;
		HRESULT l_hr = l_spDocument.CreateInstance (__uuidof (MSXML2::DOMDocument));
		if (FAILED (l_hr)) _com_issue_error (l_hr);

		l_spDocument->loadXML (p_sbstrXML);

		MSXML2::IXMLDOMElementPtr l_spDocumentElement = l_spDocument->documentElement;

		std::vector<CPropertyDescriptor>::const_iterator it1;

		for (	it1  = p_PropertyDescriptorTable.begin ();
				it1 != p_PropertyDescriptorTable.end ();
				++it1)
		{

			const CPropertyDescriptor& l_PropertyDescriptor = (*it1);
			const type_info& l_tiPropertyType = l_PropertyDescriptor.GetPropertyType ();

			MSXML2::IXMLDOMElementPtr l_spElement =
				l_spDocumentElement->selectSingleNode (l_PropertyDescriptor.GetXPath ());

			if (l_spElement) {

				_variant_t l_svarValue (l_spElement->text);

				if (l_tiPropertyType == typeid (CString)) {
					_bstr_t l_sbstrValue = l_svarValue;
					CString l_strValue = static_cast<LPCTSTR>(l_sbstrValue);
					l_PropertyDescriptor.SetPropertyValue (l_strValue);
				}
				else if (l_tiPropertyType == typeid (double)) {
					l_PropertyDescriptor.SetPropertyValue (static_cast<double>(l_svarValue));
				}
				else if (l_tiPropertyType == typeid (long)) {
					l_PropertyDescriptor.SetPropertyValue (static_cast<long>(l_svarValue));
				}
				else if (l_tiPropertyType == typeid (bool)) {
					l_PropertyDescriptor.SetPropertyValue (static_cast<bool>(l_svarValue));
				}
				else {
					// Unsupported data type.
					_ASSERTE (FALSE);
				}
			}
		}

		std::vector<CComplexTypeDescriptor>::const_iterator it2;

		for (	it2  = p_ComplexTypeDescriptorTable.begin ();
				it2 != p_ComplexTypeDescriptorTable.end ();
				++it2)
		{
			const CComplexTypeDescriptor& l_ComplexTypeDescriptor = (*it2);

			MSXML2::IXMLDOMElementPtr l_spElement =
				l_spDocumentElement->selectSingleNode (l_ComplexTypeDescriptor.GetXPath ());

			if (l_spElement) {

				IEntityMetadata* l_pComplexType = InstantiateComplexType (l_ComplexTypeDescriptor);

				if (l_pComplexType) {

					std::vector<CPropertyDescriptor>	l_PropertyDescriptorTable;
					std::vector<CComplexTypeDescriptor>	l_ComplexTypeDescriptorTable;

					l_pComplexType->GetPropertyDescriptorTable (l_PropertyDescriptorTable);
					l_pComplexType->GetComplexTypeDescriptorTable (l_ComplexTypeDescriptorTable);

					DecodeEntity (
						l_spElement->xml, 
						l_PropertyDescriptorTable,
						l_ComplexTypeDescriptorTable);
				}
			}
		}
	}
	catch (const _com_error& _ce) {
		(void) _ftprintf (stderr, _T("HRESULT: 0x%08X\n"), _ce.Error ());
	}
}


//*****************************************************************************
//* Function Name: InstantiateComplexType
//*   Description: 
//*****************************************************************************
IEntityMetadata* CEntityDecoder::InstantiateComplexType (
	const CComplexTypeDescriptor& p_ComplexTypeDescriptor)
{
	IEntityMetadata* l_pEntityMetadata = NULL;

	const type_info& l_tiComplexTypeType = p_ComplexTypeDescriptor.GetComplexTypeType ();

	if (l_tiComplexTypeType == typeid (CLabel)) {
		CLabel* l_pLabel = new CLabel;
		p_ComplexTypeDescriptor.SetComplexType (l_pLabel);
		l_pEntityMetadata = l_pLabel;
	}
	else if (l_tiComplexTypeType == typeid (CGeoLocation)) {
		CGeoLocation* l_pGeoLocation = new CGeoLocation;
		p_ComplexTypeDescriptor.SetComplexType (l_pGeoLocation);
		l_pEntityMetadata = l_pGeoLocation;
	}
	else {
		// Unsupported data type.
		_ASSERTE (FALSE);
	}

	return l_pEntityMetadata;
}
