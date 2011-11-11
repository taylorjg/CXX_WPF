#include "stdafx.h"
#include "Label.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//*****************************************************************************
//* Function Name: GetPropertyDescriptorTable
//*   Description: 
//*****************************************************************************
void CLabel::GetPropertyDescriptorTable (
	std::vector<CPropertyDescriptor>& p_PropertyDescriptorTable)
{
	p_PropertyDescriptorTable.clear ();

	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:MediumUrl", &m_strMediumUrl));
	p_PropertyDescriptorTable.push_back (CPropertyDescriptor ("d:LargeUrl",	 &m_strLargeUrl));
}


//*****************************************************************************
//* Function Name: GetLargeUrl
//*   Description: 
//*****************************************************************************
CString CLabel::GetLargeUrl (void) const
{
	if (m_strLargeUrl.IsEmpty ()) {

		// http://cache.wine.com/labels/91856m.jpg => http://cache.wine.com/labels/91856l.jpg

		INT l_iLastSlash = m_strMediumUrl.ReverseFind (_T('/'));
		INT l_iLastDot   = m_strMediumUrl.ReverseFind (_T('.'));

		if (l_iLastSlash >= 0 && l_iLastDot > l_iLastSlash) {
			if (m_strMediumUrl.GetAt (l_iLastDot - 1) == _T('m')) {
				m_strLargeUrl = m_strMediumUrl;
				m_strLargeUrl.SetAt (l_iLastDot - 1, _T('l'));
			}
		}
	}

	return m_strLargeUrl;
}
