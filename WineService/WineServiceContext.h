#ifndef _CWineServiceContext_h_
#define _CWineServiceContext_h_

class AFX_EXT_CLASS CWineServiceContext
{
public:
	CWineServiceContext (const CString& p_strUrl);
	virtual ~CWineServiceContext ();

	ProductDataServiceQueryPtr GetProducts (void);

private:
	CString m_strUrl;
};

#endif
