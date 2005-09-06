//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_CRTP_TESTS_HPP_INCLUDED)
#define BREEZE_CRTP_TESTS_HPP_INCLUDED

#include <breeze/base/crtp.hpp>

#include <iostream>

namespace breeze { namespace test {

    template <typename Derived = void>
    struct base_class
        : breeze::base::crtp<base_class<Derived>, Derived>
    {
        void call_function()
        {
            this->derived().function();
        }

        void call_function() const
        {
            this->derived().function();
        }

    protected:
        void function()
        {
            std::cout << "In base_class::function()." << std::endl;
        }

        void function() const
        {
            std::cout << "In base_class::function() const." << std::endl;
        }
    };

    struct good_derived_class
        : base_class<good_derived_class>
    {
    protected:
        friend class base_class<good_derived_class>;

        void function()
        {
            std::cout << "In good_derived_class::function()." << std::endl;
        }

        void function() const
        {
            std::cout << "In good_derived_class::function() const."
                << std::endl;
        }
    };

    struct not_derived_class
    {
    protected:
        friend class base_class<not_derived_class>;

        void function()
        {
            std::cout << "In not_derived_class::function()." << std::endl;
        }

        void function() const
        {
            std::cout << "In not_derived_class::function() const." << std::endl;
        }
    };

    struct bad_derived_class
        : base_class<not_derived_class>
    {
    protected:
        friend class base_class<not_derived_class>;

        void function()
        {
            std::cout << "In bad_derived_class::function()." << std::endl;
        }

        void function() const
        {
            std::cout << "In bad_derived_class::function() const." << std::endl;
        }
    };

}} // namespace breeze::test

#endif // include guard
