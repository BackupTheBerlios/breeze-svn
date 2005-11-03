//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DEBUG_TRACK_INSTANCES_HPP_INCLUDED)
#define BREEZE_DEBUG_TRACK_INSTANCES_HPP_INCLUDED

#include <breeze/empty_storage.hpp>
#include <breeze/debug/unique_identifier.hpp>

namespace breeze { namespace debug {

    template <class Tag = void>
    struct track_instances
    //  FIXME: Should we provide a way to iterate over all object instances?
        : unique_identifier<track_instances<Tag> >
        , empty_storage<typename unique_identifier<track_instances<Tag>
            >::identifier_type, track_instances<Tag> >
        , instrumented<track_instances<Tag> >
    {
        void verify() const
        {
            //  NOTE: in release mode nothing is verified here.
            BOOST_ASSERT(this->identifier() == this->get()
                && "Identifier doesn't match.");
        }

    private:
        friend struct instrumented<track_instances>;

        using unique_identifier<track_instances>::identifier;
        using empty_storage<typename unique_identifier<track_instances
            >::identifier_type, track_instances>::get;

        void before_constructor()
        {
            this->get() = this->identifier();

            //  Verify registration.
            this->verify();
        }

        void after_destructor()
        {
            //  Verify instance is registered before destructor of empty_storage
            //  is called.
            this->verify();
        }
    };

}} // namespace breeze::debug

#endif // include guard
