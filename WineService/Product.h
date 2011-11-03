#ifndef _CProduct_h_
#define _CProduct_h_

class CLabel;
class CGeoLocation;

#include "IEntityMetadata.h"

class AFX_EXT_CLASS CProduct : public IEntityMetadata
{
public:
	CProduct () :
		m_dblPriceMax (0.0),
		m_dblPriceMin (0.0),
		m_dblPriceRetail (0.0)
	{
	}

	CString	GetId			(void) const { return m_strId;			}
	CString	GetName			(void) const { return m_strName;		}
	CString	GetDescription	(void) const { return m_strDescription;	}
	double	GetPriceMin		(void) const { return m_dblPriceMin;	}
	double	GetPriceMax		(void) const { return m_dblPriceMax;	}
	double	GetPriceRetail	(void) const { return m_dblPriceRetail;	}
	CString	GetType			(void) const { return m_strType;		}
	CString	GetUrl			(void) const { return m_strUrl;			}
	CString	GetVintage		(void) const { return m_strVintage;		}
	CString	GetYear			(void) const { return m_strYear;		}

	boost::shared_ptr<CLabel>       GetLabel       (void) const { return m_pLabel;       }
	boost::shared_ptr<CGeoLocation> GetGeoLocation (void) const { return m_pGeoLocation; }

// IEntityMetadata
public:
	virtual void GetPropertyDescriptorTable    (std::vector<CPropertyDescriptor>&    p_PropertyDescriptorTable);
	virtual void GetComplexTypeDescriptorTable (std::vector<CComplexTypeDescriptor>& p_ComplexTypeDescriptorTable);

private:
	CString	m_strId;
    CString	m_strName;
    CString	m_strDescription;
    double	m_dblPriceMax;
    double	m_dblPriceMin;
    double	m_dblPriceRetail;
    CString	m_strType;
    CString	m_strUrl;
    CString	m_strVintage;
    CString	m_strYear;

	boost::shared_ptr<CLabel>		m_pLabel;
	boost::shared_ptr<CGeoLocation>	m_pGeoLocation;
};

#endif
