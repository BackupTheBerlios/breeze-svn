//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_STATIC_ASSERT_HPP_INCLUDED)
#define BREEZE_STATIC_ASSERT_HPP_INCLUDED

#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))

    // Borland 5.5.1 doesn't check access on sizeof expressions so we cannot use
    // sizeof a private member to trigger an error. Instead we use sizeof on an 
    // incomplete type which gives us two errors. 

#   define BREEZE_STATIC_ASSERT(expr, title, message)                           \
                                                                                \
    struct BOOST_PP_CAT(error_on_line_, __LINE__)                               \
    {                                                                           \
        struct title                                                            \
        {                                                                       \
            struct message;                                                     \
        };                                                                      \
                                                                                \
        static long check(::breeze::detail::assertion_success);                 \
        static title::message check(::breeze::assertion_failure);               \
    };                                                                          \
                                                                                \
    enum                                                                        \
    {                                                                           \
        BOOST_PP_CAT(assertion_result_for_line_, __LINE__) =                    \
            sizeof(BOOST_PP_CAT(error_on_line_, __LINE__)                       \
                ::check(::breeze::detail::static_assert< (expr) >())            \
            )                                                                   \
    }

#else

#   define BREEZE_STATIC_ASSERT(expr, title, message)                           \
                                                                                \
    struct BOOST_PP_CAT(error_on_line_, __LINE__)                               \
    {                                                                           \
        struct title                                                            \
        {                                                                       \
            static long message(::breeze::detail::assertion_success)            \
            {                                                                   \
                return 0;                                                       \
            }                                                                   \
                                                                                \
        private:                                                                \
            static long message(::breeze::assertion_failure)                    \
            {                                                                   \
                return 0;                                                       \
            }                                                                   \
        };                                                                      \
    };                                                                          \
                                                                                \
    enum                                                                        \
    {                                                                           \
        BOOST_PP_CAT(assertion_result_for_line_, __LINE__) =                    \
            sizeof(BOOST_PP_CAT(error_on_line_, __LINE__)                       \
                ::title::message(                                               \
                    ::breeze::detail::static_assert< (expr) >()))               \
    }

#endif

//  FIXME: Joel de Guzman reported an ICE on VC7.1 while using
//  BREEZE_STATIC_ASSERT. The suggested fix however broke the use of the
//  facility inside templates. I'll just have to look into it once again.
namespace breeze {

    // Having this outside the detail namespace improves readability of error
    // message just a tiny bit
    struct assertion_failure {};

    namespace detail {

        struct assertion_success {};

        template <bool Value>
        struct static_assert
            : assertion_failure
        {
        };

        template <>
        struct static_assert<true>
            : assertion_success
        {
        };

    } // namespace detail

} // namespace breeze

#endif // include guard
