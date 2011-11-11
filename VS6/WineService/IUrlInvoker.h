#ifndef _IUrlInvoker_h_
#define _IUrlInvoker_h_

class IUrlInvoker
{
public:
	virtual _bstr_t InvokeUrl (const _bstr_t& p_sbstrMethod, const _bstr_t& p_sbstrUrl) = 0;
};

#endif
