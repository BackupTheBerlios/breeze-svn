//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_INSTRUMENTED_HPP_INCLUDED)
#define BREEZE_DEBUG_INSTRUMENTED_HPP_INCLUDED

#include <breeze/base/crtp.hpp>

namespace breeze { namespace debug {

    //
    //  struct instrumented<Derived>
    //
    //      void before_constructor()
    //
    //          called on construction, before constructors of derived classes
    //          and their data members are called.
    //
    //      void after_destructor()
    //
    //          called on destruction, after destructors of derived classes and
    //          their data members have been called.
    //
    //      When multiple inheritance comes into play, explicit using directives
    //      should be added for hooks that are not overridden in the derived
    //      class:
    //
    //          using instrumented<Derived>::after_destructor;
    //          using instrumented<Derived>::before_constructor;
    //
    template <class Derived = void>
    struct instrumented
        : breeze::base::crtp<instrumented<Derived>, Derived>
    {
        instrumented()
        {
            this->derived().before_constructor();
        }

        instrumented(instrumented const &)
        {
            this->derived().before_constructor();
        }

        ~instrumented()
        {
            this->derived().after_destructor();
        }

    protected:
        friend struct breeze::base::crtp<instrumented, Derived>;

        static void before_constructor() {}
        static void after_destructor() {}
    };

}} // namespace breeze::debug

#endif // include guard
