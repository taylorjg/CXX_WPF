#ifndef _WineService_h_
#define _WineService_h_

#include "apikey.h"

#include <comdef.h>

#define BOOST_DISABLE_ASSERTS
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_array.hpp>
#include <boost/any.hpp>

/*
 * References:
 *
 * Using boost::shared_ptr in a library's public interface
 * http://stackoverflow.com/questions/335330/using-boostshared-ptr-in-a-librarys-public-interface
 *
 * Template typedefs - What's your work around?
 * http://stackoverflow.com/questions/26151/template-typedefs-whats-your-work-around
 *
 * Guru of the Week (GotW)
 * GotW #79: Template Typedef
 * http://www.gotw.ca/gotw/079.htm
 */

#include <vector>

template<class T>
struct CEntityCollection
{
	typedef boost::shared_ptr<std::vector<boost::shared_ptr<T> > > type;
	typedef std::vector<boost::shared_ptr<T> >::iterator iterator;
	typedef std::vector<boost::shared_ptr<T> >::const_iterator const_iterator;
};

#include "DataServiceQuery.h"
#include "Product.h"
#include "Label.h"
#include "GeoLocation.h"

typedef boost::shared_ptr<CDataServiceQuery<CProduct> > ProductDataServiceQueryPtr;

#include "WineServiceContext.h"

#define STR(x) #x
#define STR2(x) STR(x)
#define TODO(description) message(__FILE__ "(" STR2(__LINE__) ") : TODO - " ##description)

#endif
