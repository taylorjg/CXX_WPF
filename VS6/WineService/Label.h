#ifndef _CLabel_h_
#define _CLabel_h_

#include "IEntityMetadata.h"

class AFX_EXT_CLASS CLabel : public IEntityMetadata
{
public:
	CString GetMediumUrl (void) const { return m_strMediumUrl; }
	CString GetLargeUrl (void) const;

// IEntityMetadata
public:
	virtual void GetPropertyDescriptorTable    (std::vector<CPropertyDescriptor>&    p_PropertyDescriptorTable);
	virtual void GetComplexTypeDescriptorTable (std::vector<CComplexTypeDescriptor>& p_ComplexTypeDescriptorTable) {}

private:
	CString m_strMediumUrl;
	mutable CString m_strLargeUrl;
};

#endif
