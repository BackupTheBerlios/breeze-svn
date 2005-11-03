//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_COUNTER_HPP_INCLUDED)
#define BREEZE_DEBUG_COUNTER_HPP_INCLUDED

#include <boost/detail/atomic_count.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>

#include <cstddef>

namespace breeze { namespace debug {

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

        void increment()
        {
            BOOST_ASSERT((boost::int32_t)(counter_ + 1) > counter_
                && "Counter overflow.");
            ++counter_;
        }

        void decrement()
        {
            BOOST_ASSERT(counter_ - 1 < counter_ && "Counter underflow.");
            BOOST_ASSERT(counter_ > 0 && "Counter underflow.");
            --counter_;
        }

    private:
        boost::detail::atomic_count counter_;
    };

}} // namespace breeze::debug

#endif // include guard
