#ifndef _CInternalUrlInvoker_h_
#define _CInternalUrlInvoker_h_

#include "IUrlInvoker.h"

class CInternalUrlInvoker : public IUrlInvoker
{
public:
	virtual _bstr_t InvokeUrl (const _bstr_t& p_sbstrMethod, const _bstr_t& p_sbstrUrl);
};

#endif
