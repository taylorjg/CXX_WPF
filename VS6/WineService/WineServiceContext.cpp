#include "stdafx.h"
#include "WineServiceContext.h"
#include "DataServiceQuery.h"
#include "InternalUrlInvoker.h"
#include "InternalResponseDecoder.h"
#include "Product.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//*****************************************************************************
//* Function Name: Constructor
//*   Description: 
//*****************************************************************************
CWineServiceContext::CWineServiceContext (const CString& p_strUrl) :
	m_strUrl (p_strUrl)
{
}


//*****************************************************************************
//* Function Name: GetProducts
//*   Description: 
//*****************************************************************************
ProductDataServiceQueryPtr CWineServiceContext::GetProducts (void)
{
	ProductDataServiceQueryPtr l_pDataServiceQuery (
		new CDataServiceQuery<CProduct> (
			new CInternalUrlInvoker (),
			new CInternalResponseDecoder<CProduct> (),
			m_strUrl,
			_T("Products")));

	return l_pDataServiceQuery;
}
