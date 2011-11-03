#ifndef _CEntityDecoder_h_
#define _CEntityDecoder_h_

#include "IEntityMetadata.h"

class CEntityDecoder
{
public:

	static void GetEntryProperties (
		const _bstr_t&			p_sbstrResponse,
		std::vector<_bstr_t>&	p_EntryProperties);

	static void DecodeEntity (
		const _bstr_t&								p_sbstrXML,
		const std::vector<CPropertyDescriptor>&		p_PropertyDescriptorTable,
		const std::vector<CComplexTypeDescriptor>&	p_ComplexTypeDescriptorTable);

	static IEntityMetadata* InstantiateComplexType (
		const CComplexTypeDescriptor& p_ComplexTypeDescriptor);
};

#endif
