#ifndef AREG_EXAMPLES_13_IPCMIX_CLIENTIPCMIX_LOCALSERVICECOMPONENT_HPP
#define AREG_EXAMPLES_13_IPCMIX_CLIENTIPCMIX_LOCALSERVICECOMPONENT_HPP
/************************************************************************
 * \file        LocalServiceComponent.hpp
 * \ingroup     AREG Asynchronous Event-Driven Communication Framework examples
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       Collection of AREG SDK examples.
 *              This file contains simple implementation of local servicing interface
 *              and clients to output messages.
 ************************************************************************/
/************************************************************************
 * Include files.
 ************************************************************************/

#include "areg/base/GEGlobal.h"
#include "shareipcmix/src/LocalServicingComponent.hpp"
#include "shareipcmix/src/RemoteServiceClient.hpp"
#include "shareipcmix/src/LocalServiceClient.hpp"

//////////////////////////////////////////////////////////////////////////
// LocalServiceComponent class declaration
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   A local service component. It also contains service client object.
 **/
class LocalServiceComponent  : public LocalServicingComponent
{
//////////////////////////////////////////////////////////////////////////
// Statics and constants
//////////////////////////////////////////////////////////////////////////
    static const unsigned int   MAIN_TIMEOUT        /*= 700*/;  //!< Timeout to send request to main remote service
    static const unsigned int   SECOND_TIMEOUT      /*= 500*/;  //!< Timeout to send request to secondary remote service
    static const unsigned int   THIRD_TIMEOUT       /*= 300*/;  //!< Timeout to send request to third remote service
    static const unsigned int   LOCAL_TIMEOUT       /*= 100*/;  //!< Timeout to send request to a local service.

public:

    /**
     * \brief   Called by system to instantiate the component.
     * \param   entry   The entry of registry, which describes the component.
     * \param   owner   The component owning thread.
     * \return  Returns instantiated component to run in the system
     **/
    static Component * CreateComponent( const NERegistry::ComponentEntry & entry, ComponentThread & owner );

    /**
     * \brief   Called by system to delete component and free resources.
     * \param   compObject  The instance of component previously created by CreateComponent method.
     * \param   entry   The entry of registry, which describes the component.
     **/
    static void DeleteComponent( Component & compObject, const NERegistry::ComponentEntry & entry );

//////////////////////////////////////////////////////////////////////////
// Constructor / destructor
//////////////////////////////////////////////////////////////////////////
protected:
    
    /**
     * \brief   Instantiates the component object.
     * \param   entry   The entry of registry, which describes the component.
     * \param   owner   The component owning thread.
     **/
    LocalServiceComponent(const NERegistry::ComponentEntry & entry, ComponentThread & owner);

    /**
     * \brief   Destructor.
     **/
    virtual ~LocalServiceComponent(void);

private:
//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////

    RemoteServiceClient     mMain;      //!< The client of remote main service
    RemoteServiceClient     mSecond;    //!< The client of remote secnodary service
    RemoteServiceClient     mThird;     //!< The client of third remote service
    LocalServiceClient      mLocal;     //!< The client of local service

//////////////////////////////////////////////////////////////////////////
// Hidden calls.
//////////////////////////////////////////////////////////////////////////
    inline LocalServiceComponent & self( void );

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
    LocalServiceComponent( void );
    LocalServiceComponent( const LocalServiceComponent & /*src*/);
    const LocalServiceComponent & operator = ( const LocalServiceComponent & /*src*/ );
};

//////////////////////////////////////////////////////////////////////////
// LocalServiceComponent inline method implementation
//////////////////////////////////////////////////////////////////////////

inline LocalServiceComponent & LocalServiceComponent::self( void )
{
    return (*this);
}

#endif // AREG_EXAMPLES_13_IPCMIX_CLIENTIPCMIX_LOCALSERVICECOMPONENT_HPP

