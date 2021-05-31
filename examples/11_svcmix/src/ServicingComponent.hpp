#ifndef AREG_EXAMPLES_11_SVCMIX_SERVICINGCOMPONENT_HPP
#define AREG_EXAMPLES_11_SVCMIX_SERVICINGCOMPONENT_HPP
/************************************************************************
 * \file        ServicingComponent.hpp
 * \ingroup     AREG Asynchronous Event-Driven Communication Framework examples
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       Collection of AREG SDK examples.
 *              This file contains simple implementation of servicing component
 *              to output message and shutdown.
 ************************************************************************/
/************************************************************************
 * Include files.
 ************************************************************************/

#include "areg/base/GEGlobal.h"
#include "areg/component/Component.hpp"
#include "gen/HelloWorldStub.hpp"

//////////////////////////////////////////////////////////////////////////
// ServicingComponent class declaration
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   A demo of simple servicing component with requests, response, broadcasts and attributes.
 *          The service outputs Hello Worlds message until reaches maximum number.
 *          It demonstrates the various ways to use:
 *              a. Request with connected response;
 *              b. Request without response;
 *              c. Broadcasts with and without parameters;
 *              d. Attribute with automatic and manual update notification
 *          As well, it demonstrates use of start / shutdown of service, and manual invalidating of attribute.
 **/
class ServicingComponent    : public    Component
                            , protected HelloWorldStub
{
//////////////////////////////////////////////////////////////////////////
// Constructor / destructor
//////////////////////////////////////////////////////////////////////////
protected:
    
    /**
     * \brief   Instantiates the component object.
     * \param   entry   The entry of registry, which describes the component.
     * \param   owner   The component owning thread.
     **/
    ServicingComponent(const NERegistry::ComponentEntry & entry, ComponentThread & owner);

    /**
     * \brief   Destructor.
     **/
    virtual ~ServicingComponent(void);

//////////////////////////////////////////////////////////////////////////
// HelloWorld Interface Requests
//////////////////////////////////////////////////////////////////////////
protected:

    /**
     * \brief   Request call.
     *          Request to print hello world
     * \param   roleName    The role name of client component that requested to print hello world
     * \param   addMessage  Additional message to output. Can be empty.
     *          Has default value: ""
     * \see     responseHelloWorld
     **/
    virtual void requestHelloWorld( const String & roleName, const String & addMessage = "" );

    /**
     * \brief   Request call.
     *          Sent by client to notify the shutdown. This removes client from the list. This request has no response.
     * \param   clientID    The ID of client that requests to shutdown. The ID is given by service when first time client requests to output message.
     * \param   roleName    Service client component role name
     * \note    Has no response
     **/
    virtual void requestClientShutdown( unsigned int clientID, const String & roleName );

/************************************************************************/
// StubBase overrides. Triggered by Component on startup.
/************************************************************************/

    /**
     * \brief   This function is triggered by Component when starts up.
     *          Overwrite this method and set appropriate request and
     *          attribute update notification event listeners here
     * \param   holder  The holder component of service interface of Stub,
     *                  which started up.
     **/
    virtual void startupServiceInterface( Component & holder );

    /**
     * \brief   This function is triggered by Component when shuts down.
     *          Overwrite this method to remove listeners and stub cleanup
     * \param   holder  The holder component of service interface of Stub,
     *                  which shuts down.
     **/
    virtual void shutdownServiceIntrface ( Component & holder );

//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////
private:
    unsigned int    mGnerateID; //!< The client ID generator

    const bool      mIsMain;    //!< Flag, indicating whether it is a main shutdown control component or not.

//////////////////////////////////////////////////////////////////////////
// Hidden calls
//////////////////////////////////////////////////////////////////////////
private:
    inline ServicingComponent & self( void );

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
    ServicingComponent( void );
    ServicingComponent( const ServicingComponent & /*src*/);
    const ServicingComponent & operator = ( const ServicingComponent & /*src*/ );
};

//////////////////////////////////////////////////////////////////////////
// ServicingComponent inline methods
//////////////////////////////////////////////////////////////////////////
inline ServicingComponent & ServicingComponent::self( void )
{   return (*this);     }


#endif // AREG_EXAMPLES_11_SVCMIX_SERVICINGCOMPONENT_HPP
