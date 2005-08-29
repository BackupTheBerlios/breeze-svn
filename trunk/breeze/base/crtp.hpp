//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_BASE_CRTP_HPP_INCLUDED)
#define BREEZE_BASE_CRTP_HPP_INCLUDED

#include <breeze/static_assert.hpp>

#include <boost/type_traits/is_base_and_derived.hpp>

namespace breeze { namespace base {

    namespace crtp_base_aux_ns {

        // To avoid ADL issues base classes are placed in their own namespaces

        template <
            class Deriving,
            class Derived
                = typename Deriving::crtp_derived_template_parameter_
        >
        struct crtp
        {
        protected:
            typedef Derived derived_type;
            typedef Derived crtp_derived_template_parameter_;

            ~crtp()
            {

                BREEZE_STATIC_ASSERT(
                    (boost::is_base_and_derived<crtp, Deriving>::value),
                    invalid_template_parameter,
                    Deriving_must_inherit_from_crtp
                );

                BREEZE_STATIC_ASSERT(
                    (boost::is_base_and_derived<crtp, Derived>::value),
                    invalid_template_parameter,
                    Derived_must_inherit_from_crtp
                );

            }

            derived_type & derived()
            {
                return *static_cast<derived_type *>(this);
            }

            derived_type const & derived() const
            {
                return *static_cast<derived_type const *>(this);
            }
        };

        template <typename Deriving>
        struct crtp<Deriving, void>
        {
        protected:
            typedef Deriving derived_type;
            typedef void crtp_derived_template_parameter_;

            ~crtp()
            {

                BREEZE_STATIC_ASSERT(
                    (boost::is_base_and_derived<crtp, Deriving>::value),
                    invalid_template_parameter,
                    Deriving_must_inherit_from_crtp
                );

            }

            derived_type & derived()
            {
                return *static_cast<derived_type *>(this);
            }

            derived_type const & derived() const
            {
                return *static_cast<derived_type const *>(this);
            }
        };

    }

    using crtp_base_aux_ns::crtp;

}} // namespace breeze::base

#endif // include guard
