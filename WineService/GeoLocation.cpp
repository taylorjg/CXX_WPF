#include "stdafx.h"
#include "GeoLocation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//*****************************************************************************
//* Function Name: GetPropertyDescriptorTable
//*   Description: 
//*****************************************************************************
void CGeoLocation::GetPropertyDescriptorTable (
	std::vector<CPropertyDescriptor>& p_PropertyDescriptorTable)
{
	p_PropertyDescriptorTable.clear ();

	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Latitude",  &m_strLatitude));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Longitude", &m_strLongitude));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:Url",		 &m_strUrl));
}
