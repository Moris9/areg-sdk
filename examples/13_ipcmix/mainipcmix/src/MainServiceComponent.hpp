#ifndef AREG_EXAMPLES_13_IPCMIX_MAINIPCMIX_MAINSERVICECOMPONENT_HPP
#define AREG_EXAMPLES_13_IPCMIX_MAINIPCMIX_MAINSERVICECOMPONENT_HPP
/************************************************************************
 * \file        MainServiceComponent.hpp
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
#include "shareipcmix/src/MainServicingComponent.hpp"
#include "shareipcmix/src/LocalServiceClient.hpp"

//////////////////////////////////////////////////////////////////////////
// MainServiceComponent class declaration
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   Main remote service component. It differs from the other remote
 *          servicing components that can trigger system shutdown when
 *          the maximum number of output messages reached.
 **/
class MainServiceComponent  : public MainServicingComponent
{
//////////////////////////////////////////////////////////////////////////
// Statics and constants.
//////////////////////////////////////////////////////////////////////////
    static const unsigned  int     LOCAL_TIMEOUT        /*= 789*/;  //!< Timeout to output message in local service.

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
    MainServiceComponent(const NERegistry::ComponentEntry & entry, ComponentThread & owner);

    /**
     * \brief   Destructor.
     **/
    virtual ~MainServiceComponent(void);

private:
//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////
    LocalServiceClient  mLocal; //! Client of local service

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
    inline MainServiceComponent & self( void );

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
    MainServiceComponent( void );
    MainServiceComponent( const MainServiceComponent & /*src*/);
    const MainServiceComponent & operator = ( const MainServiceComponent & /*src*/ );
};

//////////////////////////////////////////////////////////////////////////
// MainServiceComponent inline method implementation
//////////////////////////////////////////////////////////////////////////
inline MainServiceComponent & MainServiceComponent::self( void )
{
    return (*this);
}

#endif // AREG_EXAMPLES_13_IPCMIX_MAINIPCMIX_MAINSERVICECOMPONENT_HPP
