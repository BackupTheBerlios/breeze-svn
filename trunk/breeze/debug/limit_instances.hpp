//
//  Copyright (c) 2004 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_LIMIT_INSTANCES_HPP_INCLUDED)
#define BREEZE_DEBUG_LIMIT_INSTANCES_HPP_INCLUDED

#include <breeze/base/crtp.hpp>

#include <breeze/debug/instrumented.hpp>
#include <breeze/debug/count_instances.hpp>

#include <boost/assert.hpp>

namespace breeze { namespace debug {

    template <long MaxInstances, class Derived = void>
    struct limit_instances
        : breeze::base::crtp<limit_instances<MaxInstances, Derived>, Derived>
        , instrumented<limit_instances<MaxInstances, Derived> >
        , count_instances<limit_instances<MaxInstances, Derived> >
    {
    private:
        friend struct breeze::base::crtp<limit_instances, Derived>;
        friend struct instrumented<limit_instances>;

        using breeze::base::crtp<limit_instances, Derived>::derived;
        using instrumented<limit_instances>::after_destructor;
        using count_instances<limit_instances>::live_count;

        void before_constructor() const
        {
            // Before live_count is updated on count_instances construction
            if (this->live_count() >= MaxInstances)
                this->derived().max_instances_exceeded();
        }

        static void max_instances_exceeded()
        {
            BOOST_ASSERT(!"Attempt to exceed maximum number of instances!");
        }
    };

}} // namespace breeze::debug

#endif // include guard
