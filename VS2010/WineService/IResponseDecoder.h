#ifndef _IResponseDecoder_h_
#define _IResponseDecoder_h_

template<class T>
class IResponseDecoder
{
public:
	virtual void DecodeResponse (const _bstr_t& p_sbstrResponse, typename CEntityCollection<T>::type& p_pEntityCollection) = 0;
};

#endif
