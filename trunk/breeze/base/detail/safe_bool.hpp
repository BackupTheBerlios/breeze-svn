//
//  Copyright (c) 2004 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DETAIL_SAFE_BOOL_HPP_INCLUDED)
#define BREEZE_DETAIL_SAFE_BOOL_HPP_INCLUDED

namespace breeze { namespace base { namespace detail {

    struct safe_bool_impl
    {
        struct this_type_has_no_conversions
        {
            typedef this_type_has_no_conversions *
                (this_type_has_no_conversions::*unspecified_bool_type)();

            this_type_has_no_conversions * member() { return 0; }
        };

        typedef this_type_has_no_conversions::unspecified_bool_type
            unspecified_bool_type;
    };

}}} // namespace breeze::base::detail

#endif // include guard
