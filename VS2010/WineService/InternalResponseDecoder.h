#ifndef _CInternalResponseDecoder_h_
#define _CInternalResponseDecoder_h_

#include "IResponseDecoder.h"
#include "EntityDecoder.h"

template<class T>
class CInternalResponseDecoder : public IResponseDecoder<T>
{
public:
	virtual void DecodeResponse (const _bstr_t& p_sbstrResponse, typename CEntityCollection<T>::type& p_pEntityCollection);
};

//*****************************************************************************
//* Function Name: DecodeResponse
//*   Description: 
//*****************************************************************************
template<class T>
void CInternalResponseDecoder<T>::DecodeResponse (
	const _bstr_t&							p_sbstrResponse,
	typename CEntityCollection<T>::type&	p_pEntityCollection)
{
	std::vector<_bstr_t> l_EntryProperties;
	std::vector<_bstr_t>::const_iterator it;

	CEntityDecoder::GetEntryProperties (p_sbstrResponse, l_EntryProperties);

	for (it = l_EntryProperties.begin (); it != l_EntryProperties.end (); ++it) {

		const _bstr_t& l_sbstrXML = (*it);

		boost::shared_ptr<T> l_pEntity (new T ());
		IEntityMetadata* l_pEntityMetadata = l_pEntity.get ();

		std::vector<CPropertyDescriptor> l_PropertyDescriptorTable;
		l_pEntityMetadata->GetPropertyDescriptorTable (l_PropertyDescriptorTable);

		std::vector<CComplexTypeDescriptor> l_ComplexTypeDescriptorTable;
		l_pEntityMetadata->GetComplexTypeDescriptorTable (l_ComplexTypeDescriptorTable);

		CEntityDecoder::DecodeEntity (
			l_sbstrXML,
			l_PropertyDescriptorTable,
			l_ComplexTypeDescriptorTable);

		p_pEntityCollection->push_back (l_pEntity);
	}
}

#endif
