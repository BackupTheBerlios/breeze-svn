//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEFAULT_HPP_INCLUDED)
#define BREEZE_DEFAULT_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace breeze {

    //
    //  Type to be used as a placeholder representing the default template
    //  parameter.
    //
    struct default_;

    template <class T>
    struct is_default
        : boost::mpl::false_
    {
    };

    template <>
    struct is_default<default_>
        : boost::mpl::true_
    {
    };

} // namespace breeze

#endif // include guard
