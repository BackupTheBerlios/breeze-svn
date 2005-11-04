//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_BOOL_TYPE_HPP_INCLUDED)
#define BREEZE_BOOL_TYPE_HPP_INCLUDED

#include <breeze/base/safe_bool.hpp>

namespace breeze {

    struct bool_type
        : breeze::base::safe_bool<bool_type>
    {
        bool_type()
        {
        }

        bool_type(bool value)
            : value_(value)
        {
        }

        bool_type & operator=(bool value)
        {
            value_ = value;
            return *this;
        }

    private:
        friend class breeze::safe_bool_core_access;

        bool operator_safe_bool() const
        {
            return value_;
        }

        bool value_;
    };

    bool operator==(bool_type const & lhs, bool_type const & rhs)
    {
        return (bool) lhs == (bool) rhs;
    }

    bool operator!=(bool_type const & lhs, bool_type const & rhs)
    {
        return !(lhs == rhs);
    }

} // namespace breeze

#endif // include guard
