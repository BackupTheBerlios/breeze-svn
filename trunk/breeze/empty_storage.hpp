//
//  Copyright (c) 2004 João Abecasis
//
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_EMPTY_STORAGE_HPP_INCLUDED)
#define BREEZE_EMPTY_STORAGE_HPP_INCLUDED

#include <breeze/default.hpp>
#include <breeze/debug/instrumented.hpp>

#include <boost/assert.hpp>
#include <boost/call_traits.hpp>
#include <boost/utility/base_from_member.hpp>

#include <boost/mpl/apply.hpp>

#include <map>

namespace breeze {

    namespace detail {

        struct empty_storage_default_store
        {
            template <class T0, class T1>
            struct apply
            {
                typedef std::map<T0, T1> type;
            };
        };

    }

    template <
        class T,
        class Dummy = void,
        class LambdaStore = default_
    >
    struct empty_storage
        : breeze::debug::instrumented<empty_storage<T, Dummy, LambdaStore> >
    {
    private:
        typedef typename filter_default<LambdaStore,
            detail::empty_storage_default_store>::type lambda_store_type;

        typedef typename boost::mpl::apply<lambda_store_type, empty_storage
            const *, T>::type store_type;

    public:
        typedef T value_type;

        typedef typename boost::call_traits<value_type>::reference reference;
        typedef typename boost::call_traits<value_type>::const_reference
            const_reference;

        empty_storage()
        {
        }

        empty_storage(const_reference val)
        {
            this->get() = val;
        }

        empty_storage(empty_storage const & other)
        {
            if (other.has_value())
                this->get() = other.get();
        }

        reference get()
        {
            return store_.get()[this];
        }

        const_reference get() const
        {
            return store_.get()[this];
        }

        void reset()
        {
            store_.get().erase(this);
        }

        bool has_value() const
        {
            return store_.get().count(this);
        }

    private:
        friend struct breeze::debug::instrumented<empty_storage>;

        void after_destructor()
        {
            store_.get().erase(this);
        }

        void before_constructor()
        {
            BOOST_ASSERT(!this->has_value());
        }

        struct checked_store_type
            : boost::base_from_member<store_type>
            , breeze::debug::instrumented<checked_store_type>
        {
            typedef boost::base_from_member<store_type> store;

            checked_store_type()
            {
            }

            checked_store_type(store_type const & s)
                : store(s)
            {
            }

            store_type & get()
            {
                return store::member;
            }

            void after_destructor()
            {
                BOOST_ASSERT(this->get().empty()
                    && "Store not empty on destruction.");
            }
        };

        static checked_store_type store_;
    };

    template <class T, class D, class LS>
    typename empty_storage<T, D, LS>::checked_store_type
        empty_storage<T, D, LS>::store_;

} // namespace breeze

#endif // include guard
