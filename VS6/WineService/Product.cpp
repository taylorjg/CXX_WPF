#include "stdafx.h"
#include "Product.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//*****************************************************************************
//* Function Name: GetPropertyDescriptorTable
//*   Description: 
//*****************************************************************************
void CProduct::GetPropertyDescriptorTable (
	std::vector<CPropertyDescriptor>& p_PropertyDescriptorTable)
{
	p_PropertyDescriptorTable.clear ();

	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Id",					&m_strId));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Name",					&m_strName));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Description",			&m_strDescription));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Url",					&m_strUrl));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:PriceMin",				&m_dblPriceMin));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:PriceMax",				&m_dblPriceMax));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:PriceRetail",			&m_dblPriceRetail));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Type",					&m_strType));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Year",					&m_strYear));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Vintage",				&m_strVintage));
}


//*****************************************************************************
//* Function Name: GetComplexTypeDescriptorTable
//*   Description: 
//*****************************************************************************
void CProduct::GetComplexTypeDescriptorTable (
	std::vector<CComplexTypeDescriptor>& p_ComplexTypeDescriptorTable)
{
	p_ComplexTypeDescriptorTable.clear ();

	p_ComplexTypeDescriptorTable.push_back (CComplexTypeDescriptor ("d:Label",       &m_pLabel));
	p_ComplexTypeDescriptorTable.push_back (CComplexTypeDescriptor ("d:GeoLocation", &m_pGeoLocation));
}
