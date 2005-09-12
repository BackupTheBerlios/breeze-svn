//
//  Copyright (c) 2004 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_ALLOCATOR_COUNTING_ALLOCATOR_HPP_INCLUDED)
#define BREEZE_ALLOCATOR_COUNTING_ALLOCATOR_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <memory>

namespace breeze { namespace allocator {

    template <class T, class BaseAllocator = std::allocator<T> >
    struct counting_allocator
        : protected BaseAllocator
    {
        typedef BaseAllocator                               allocator_type;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::value_type         value_type;

    private:
        typedef counting_allocator<T, BaseAllocator> identity;
        typedef BaseAllocator base_class;

        template <class U, class UBA>
        struct check_base_allocator
            : boost::is_same<typename allocator_type::template rebind<U>::other,
                UBA>
        {
        };

    public:
        template <class U>
        struct rebind
        {
            typedef counting_allocator<U, typename allocator_type
                ::template rebind<U>::other> other;
        };

        counting_allocator() // does not throw
            : counter_(0)
        {
        }

        counting_allocator(identity const & that) // does not throw
            : base_class(that)
            , counter_(0)
        {
        }

        counting_allocator(allocator_type const & that) // does not throw
            : base_class(that)
            , counter_(0)
        {
        }

        template <class U, class UBA>
        counting_allocator(
            counting_allocator<U, UBA> const & that,
            typename boost::enable_if<check_base_allocator<U, UBA>
                >::type * = 0
        ) // does not throw
            : base_class(that)
            , counter_(0)
        {
        }

        ~counting_allocator() // does not throw
        {
            BOOST_ASSERT(counter_ == 0);
        }

        using base_class::address;
        using base_class::allocate;
        using base_class::deallocate;
        using base_class::max_size;

        void construct(pointer p, const T& t)
        {
            base_class::construct(p, t);
            ++(counter_);
        }

        void destroy(pointer p)
        {
            --(counter_);
            base_class::destroy(p);
        }

        allocator_type const & base() const
        {
            return *this;
        }

        size_type count() const
        {
            return counter_;
        }

        //  Assignment operators
        //  NOTE: counter is not transfered on assignment
        identity & operator=(identity const & that)
        {
            if (this != &that)
            {
                BOOST_ASSERT((base_class) *this == (base_class) that);
                (base_class) *this = that;
            }

            return *this;
        }

        template <class U, class UBA>
        typename boost::enable_if<check_base_allocator<U, UBA>, identity&>::type
        operator=(counting_allocator<U, UBA> const & that)
        {
            BOOST_ASSERT((base_class) *this == (base_class) that);
            (base_class) *this = that;

            return *this;
        }

    private:
        template <class U, class UBA>
        friend typename boost::enable_if<check_base_allocator<U, UBA>, bool
            >::type operator==(identity const & lhs, counting_allocator<U, UBA>
                const & rhs);

        size_type counter_;
    };

    template <class T, class U, class TBA, class UBA>
    inline typename boost::enable_if<typename counting_allocator<T, TBA>
        ::template check_base_allocator<U, UBA>, bool>::type
    operator==(counting_allocator<T, TBA> const & lhs,
        counting_allocator<U, UBA> const & rhs) // does not throw
    {
        // allocation/deallocation must go through original allocator to
        // maintain counts.
        return false;
    }

    template <class T, class U, class TBA, class UBA>
    inline typename boost::enable_if<typename counting_allocator<T, TBA>
        ::template check_base_allocator<U, UBA>, bool>::type
    operator!=(const counting_allocator<T, TBA>&lhs,
        const counting_allocator<U, UBA>&rhs) // does not throw
    {
        return !(lhs == rhs);
    }

}} // namespace breeze::allocator

#endif // include guard
