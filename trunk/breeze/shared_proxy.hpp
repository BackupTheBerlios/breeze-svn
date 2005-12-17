//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_SHARED_PROXY_HPP_INCLUDED)
#define BREEZE_SHARED_PROXY_HPP_INCLUDED

#include <breeze/default.hpp>

#include <boost/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/detail/atomic_count.hpp>
#include <boost/checked_delete.hpp>
#include <boost/assert.hpp>

namespace breeze {

    template <class T, class Deleter = default_>
    struct shared_proxy
    {
        typedef T value_type;
        typedef typename filter_default<Deleter,
            boost::checked_deleter<shared_proxy const> >::type deleter_type;

    private:
        typedef boost::detail::atomic_count counter_type;
        typedef boost::compressed_pair<value_type, deleter_type> data_type;

        counter_type ref_count_;
        data_type data_;

    public:
        typedef typename boost::add_pointer<T>::type pointer;
        typedef typename boost::add_pointer<typename boost::add_const<T>::type
            >::type const_pointer;
        typedef typename data_type::first_reference reference;
        typedef typename data_type::first_const_reference const_reference;

        typedef typename data_type::second_reference deleter_reference;
        typedef typename data_type::second_const_reference deleter_const_reference;

        shared_proxy()
            : ref_count_(0)
            , data_()
        {
        }

        shared_proxy(shared_proxy const & that)
            : ref_count_(0)
            , data_(that.data_)
        {
        }

        template <class U>
        shared_proxy(U const & u)
            : ref_count_(0)
            , data_(u, deleter_type())
        {
        }

        template <class U, class V>
        shared_proxy(U const & u, V const & v)
            : ref_count_(0)
            , data_(u, v)
        {
        }

        ~shared_proxy()
        {
            BOOST_ASSERT(0 == ref_count_
                && "Destroying shared_proxy with non-zero use count.");
        }

        template <class U>
        shared_proxy & operator=(U const & u)
        {
            this->data_.first() = u;
            return *this;
        }

        reference operator*()
        {
            return data_.first();
        }

        const_reference operator*() const
        {
            return data_.first();
        }

        pointer operator->()
        {
            return boost::addressof(data_.first());
        }

        const_pointer operator->() const
        {
            return boost::addressof(data_.first());
        }

        reference get()
        {
            return data_.first();
        }

        const_reference get() const
        {
            return data_.first();
        }

        bool unique() const
        {
            return ref_count_ == 1;
        }

        long use_count() const
        {
            return ref_count_;
        }

        void increment_use_count()
        {
            ++ref_count_;
        }

        void decrement_use_count()
        {
            if (0 == --ref_count_)
            {
                data_.second()(this);
            }
        }

        deleter_reference get_deleter()
        {
            return data_.second();
        }

        deleter_const_reference get_deleter() const
        {
            return data_.second();
        }
    };

} // namespace breeze

#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace breeze {
#else // defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace boost {
#endif

    template <class T>
    inline void intrusive_ptr_add_ref(breeze::shared_proxy<T> * sp)
    {
        sp->increment_use_count();
    }

    template <class T>
    inline void intrusive_ptr_release(breeze::shared_proxy<T> * sp)
    {
        sp->decrement_use_count();
    }

} // namespace boost or breeze

#endif // include guard
