//
//  Copyright (c) 2004 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_COUNT_INSTANCES_HPP_INCLUDED)
#define BREEZE_DEBUG_COUNT_INSTANCES_HPP_INCLUDED

#include <breeze/debug/counter.hpp>
#include <breeze/debug/instrumented.hpp>

#include <boost/assert.hpp>

#include <cstddef>

namespace breeze { namespace debug {

    template <typename Tag = void>
    struct count_instances
        : instrumented<count_instances<Tag> >
    {
        static long live_count()
        {
            return live_count_.get();
        }

    private:
        friend struct instrumented<count_instances>;

        static void before_constructor()
        {
            live_count_.increment();
        }

        static void after_destructor()
        {
            live_count_.decrement();
        }

        struct live_counter_type
            : counter<count_instances>
            , instrumented<live_counter_type>
        {
            void after_destructor()
            {
                BOOST_ASSERT(*this == 0 &&
                "live_count is not zero on destruction of instance counter.");
            }
        };

        static live_counter_type live_count_;
    };

    template <typename D>
    typename count_instances<D>::live_counter_type
        count_instances<D>::live_count_;

}} // namespace breeze::debug

#endif // include guard
