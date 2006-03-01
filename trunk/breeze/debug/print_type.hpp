//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_PRINT_TYPE_HPP_INCLUDED)
#define BREEZE_DEBUG_PRINT_TYPE_HPP_INCLUDED

namespace breeze { namespace debug {

    //  Print a typename in a compiler error message
    template <class type>
    inline void print()
    {
        class _ { _() {} };
        _ printer;
    }

}}

#endif // include guard
