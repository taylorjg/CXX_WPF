#ifndef _IEntityMetadata_h_
#define _IEntityMetadata_h_

class CPropertyDescriptor
{
public:
	template<class T> CPropertyDescriptor (LPCTSTR p_lpszXPath, T* p_pPropertyValue) :
		m_lpszXPath (p_lpszXPath),
		m_pPropertyValue (p_pPropertyValue),
		m_ptiPropertyType (&typeid (T))
	{
	}

	LPCTSTR GetXPath (void) const { return m_lpszXPath; }

	const type_info& GetPropertyType (void) const { return *m_ptiPropertyType; }

	template<class T> void SetPropertyValue (const T& p_Value) const
	{
		T* l_pT = boost::any_cast<T*>(m_pPropertyValue);
		*l_pT = p_Value;
	}

private:
	LPCTSTR				m_lpszXPath;
	boost::any			m_pPropertyValue;
	const type_info*	m_ptiPropertyType;
};

class CComplexTypeDescriptor
{
public:
	template<class T> CComplexTypeDescriptor (LPCTSTR p_lpszXPath, boost::shared_ptr<T>* p_ppComplexType) :
		m_lpszXPath (p_lpszXPath),
		m_ppComplexType (p_ppComplexType),
		m_ptiComplexTypeType (&typeid (T))
	{
	}

	LPCTSTR GetXPath (void) const { return m_lpszXPath; }

	const type_info& GetComplexTypeType (void) const { return *m_ptiComplexTypeType; }

	template<class T> void SetComplexType (T* p_pComplexType) const
	{
		boost::shared_ptr<T>* l_ppComplexType = boost::any_cast<boost::shared_ptr<T>*>(m_ppComplexType);
		l_ppComplexType->reset (p_pComplexType);
	}

private:
	LPCTSTR				m_lpszXPath;
	boost::any			m_ppComplexType;
	const type_info*	m_ptiComplexTypeType;
};

class IEntityMetadata
{
public:
	virtual void GetPropertyDescriptorTable    (std::vector<CPropertyDescriptor>&    p_PropertyDescriptorTable) = 0;
	virtual void GetComplexTypeDescriptorTable (std::vector<CComplexTypeDescriptor>& p_ComplexTypeDescriptorTable) = 0;
};

#endif
