//
//  The implementation of the Safe Bool Idiom presented herein is originally
//  based on an article by Bjorn Karlsson:
//
//      Bjorn Karlsson (July 31, 2004), The Safe Bool Idiom, The C++ Source
//      http://www.artima.com/cppsource/safebool.html
//
//  Some ideas taken from <boost/spirit/core/safe_bool.hpp> and some others
//  I may have gathered from lurking on boost's mailing lists and now call my
//  own...
//
//  Whatever's left that can be called my code (I'm sure it's mostly
//  cosmetic fixes...) is:
//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_SAFE_BOOL_HPP_INCLUDED)
#define BREEZE_SAFE_BOOL_HPP_INCLUDED

#include <breeze/base/crtp.hpp>
#include <breeze/static_assert.hpp>
#include <breeze/base/detail/safe_bool.hpp>

namespace breeze {

    namespace base {

        namespace safe_bool_base_aux_ns {

            //  To avoid ADL issues base classes are placed in their own
            //  namespaces

            template <class T>
            struct safe_bool;

        } // namespace safe_bool_base_aux_ns

        using safe_bool_base_aux_ns::safe_bool;

    } // namespace base

    class safe_bool_core_access
    {
        template <class T> friend struct base::safe_bool;

        template <class T>
        static bool operator_safe_bool(T const & t)
        {
            return t.operator_safe_bool();
        }
    };

    namespace base { namespace safe_bool_base_aux_ns {

        template <class T>
        struct safe_bool
            : crtp<safe_bool<T>, T>
        {
        protected:
            typedef detail::safe_bool_impl::unspecified_bool_type
                unspecified_bool_type;

            ~safe_bool() {}

        public:
            operator unspecified_bool_type() const
            {
                return
                    safe_bool_core_access::operator_safe_bool(this->derived())
                        ? &detail::safe_bool_impl::this_type_has_no_conversions
                            ::member
                        : 0
                ;
            }

            bool operator!() const
            {
                return !unspecified_bool_type(*this);
            }
        };

        template <class T1, class T2>
        bool operator==(safe_bool<T1> const &, safe_bool<T2> const &)
        {

            BREEZE_STATIC_ASSERT(false, invalid_use_of_operator,
                comparison_between_T1_and_T2_not_supported);

            return false;
        }

        template <class T1, class T2>
        bool operator!=(safe_bool<T1> const &, safe_bool<T2> const &)
        {
            BREEZE_STATIC_ASSERT(false, invalid_use_of_operator,
                comparison_between_T1_and_T2_not_supported);

            return false;
        }

    } // namespace safe_bool_base_aux_ns

}} // namespace breeze::base

#endif // include guard
