//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_COUNTER_HPP_INCLUDED)
#define BREEZE_DEBUG_COUNTER_HPP_INCLUDED

#include <breeze/debug/unused_variable.hpp>

#include <boost/detail/atomic_count.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>

#include <cstddef>

namespace breeze { namespace debug {

    //
    //  Tag template parameter is meant to appear in assertions generated in
    //  debug builds. Accordingly, it should be set to a type that relates to
    //  the client code of this class.
    //
    template <class Tag = void>
    struct counter
    {
        counter()
            : counter_(0)
        {
        }

        operator boost::int32_t () const
        {
            return counter_;
        }

        boost::int32_t get() const
        {
            return counter_;
        }

        //
        //  NOTE: A race condition exists with the debug assertions in both
        //  increment and decrement, below. The race condition could allow
        //  over and underflows to go undetected, even in a debug build. This
        //  would only be true for a given sequence of events. Now, how likely
        //  is that?... :-p
        //

        void increment()
        {
            struct check_value
            {
                check_value (boost::int32_t count)
                {
                    BOOST_ASSERT((boost::int32_t)(count + 1) > count
                        && "Counter overflow.");
                    unused_variable(count);
                }
            };

            check_value check(counter_);    // RACE!
            ++counter_;                     // (see NOTE above)
        }

        bool decrement()
        {
            struct check_value
            {
                check_value(boost::int32_t count)
                {
                    BOOST_ASSERT(count > 0 && "Counter underflow.");
                    BOOST_ASSERT((boost::int32_t)(count - 1) < count
                        && "Counter underflow.");
                    unused_variable(count);
                }
            };

            check_value check(counter_);    // RACE!
            return --counter_;              // (see NOTE above)
        }

    private:
        boost::detail::atomic_count counter_;
    };

}} // namespace breeze::debug

#endif // include guard
