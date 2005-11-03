//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_UNUSED_VARIABLE_HPP_INCLUDED)
#define BREEZE_DEBUG_UNUSED_VARIABLE_HPP_INCLUDED

namespace breeze { namespace debug {

    //  Supress unused variable warnings
    template <class T>
    inline void unused_variable(T const &)
    {
    }

}} // namespace breeze::debug

#endif // include guard
