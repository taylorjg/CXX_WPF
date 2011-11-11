#ifndef _CGeoLocation_h_
#define _CGeoLocation_h_

#include "IEntityMetadata.h"

class AFX_EXT_CLASS CGeoLocation : public IEntityMetadata
{
public:
	CString GetLatitude  (void) const { return m_strLatitude;  }
	CString GetLongitude (void) const { return m_strLongitude; }
	CString GetUrl       (void) const { return m_strUrl;       }

// IEntityMetadata
public:
	virtual void GetPropertyDescriptorTable    (std::vector<CPropertyDescriptor>&    p_PropertyDescriptorTable);
	virtual void GetComplexTypeDescriptorTable (std::vector<CComplexTypeDescriptor>& p_ComplexTypeDescriptorTable) {}

private:
	CString m_strLatitude;
	CString m_strLongitude;
	CString m_strUrl;
};

#endif
