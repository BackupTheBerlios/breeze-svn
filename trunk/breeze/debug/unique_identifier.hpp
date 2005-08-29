//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_UNIQUE_IDENTIFIER_HPP_INCLUDED)
#define BREEZE_DEBUG_UNIQUE_IDENTIFIER_HPP_INCLUDED

#include <boost/assert.hpp>

#include <cstddef>

namespace breeze { namespace debug {

    template <typename Tag = void>
    struct unique_identifier
    //  FIXME: What operations do we guarantee on identifier_type? What about on
    //      unique_identifier itself?
    //
    //      Either identifier_type or unique_identifier should have operator==
    //      and operator!=, perhaps operator< and/or std::less could also be
    //      provided.
    {
        //  FIXME: identifier_type should be dependent on platform and avoid
        //      repeating IDs totally or as much as possible, without incurring
        //      in too much of a runtime penalty in terms of performance.
        typedef std::size_t identifier_type;

        identifier_type identifier() const
        {
            return id_.value;
        }

    private:
        struct id_holder
        {
            id_holder()
                : value(generate_id())
            {
            }

            id_holder(id_holder const &)
                : value(generate_id())
            {
            }

            identifier_type value;
        } id_;

        static identifier_type generate_id()
        {
            //  FIXME: I should be made thread_safe!
            //  FIXME: If strict ordering is not necessary we can get an extra
            //      clock cycle by not initializing last_id_
            static identifier_type last_id_ = 0;

            //  FIXME: This is completely thread unsafe!!!
            ++last_id_;

            //  Have we exceeded our capacity?
            BOOST_ASSERT(last_id_ != 0);

            return last_id_;
        }
    };

}} // namespace breeze::debug

#endif // include guard
