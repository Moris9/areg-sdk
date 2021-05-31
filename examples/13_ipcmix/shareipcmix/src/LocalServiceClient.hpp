#ifndef AREG_EXAMPLES_13_IPCMIX_SHAREIPCMIX_LOCALSERVICECLIENT_HPP
#define AREG_EXAMPLES_13_IPCMIX_SHAREIPCMIX_LOCALSERVICECLIENT_HPP
/************************************************************************
 * \file        shareipcmix/src/LocalServiceClient.hpp
 * \ingroup     AREG Asynchronous Event-Driven Communication Framework examples
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       Collection of AREG SDK examples.
 *              This file contains simple implementation of service client to
 *              request message output
 ************************************************************************/
/************************************************************************
 * Include files.
 ************************************************************************/

#include "areg/base/GEGlobal.h"
#include "areg/component/Component.hpp"
#include "areg/component/IETimerConsumer.hpp"
#include "shareipcmix/src/LocalHelloWorldClientBase.hpp"

#include "areg/component/Timer.hpp"

//////////////////////////////////////////////////////////////////////////
// ServicingComponent class declaration
//////////////////////////////////////////////////////////////////////////
class LocalServiceClient    : protected LocalHelloWorldClientBase
                            , private   IETimerConsumer
{
//////////////////////////////////////////////////////////////////////////
// Constructor / destructor
//////////////////////////////////////////////////////////////////////////
public:
    
    /**
     * \brief   Instantiates the component object.
     * \param   entry   The entry of registry, which describes the component.
     * \param   owner   The component owning thread.
     * \param   timeout The timeout in milliseconds to trigger the request to output message
     **/
    LocalServiceClient( const String & roleName, Component & owner, unsigned int timeout );
    
    /**
     * \brief   Destructor
     **/
    virtual ~LocalServiceClient(void);

protected:

    /**
     * \brief   Triggered, when ConnectedClients attribute is updated. The function contains
     *          attribute value and validation flag. When notification is enabled,
     *          the method should be overwritten in derived class.
     *          Attributes ConnectedClients description: 
     *          The list of connected clients. Updated each time when new client requests to output Hello World message.
     * \param   ConnectedClients    The value of ConnectedClients attribute.
     * \param   state               The data validation flag.
     **/
    virtual void onConnectedClientsUpdate( const NELocalHelloWorld::ConnectionList & ConnectedClients, NEService::eDataStateType state );

        /**
     * \brief   Triggered, when RemainOutput attribute is updated. The function contains
     *          attribute value and validation flag. When notification is enabled,
     *          the method should be overwritten in derived class.
     *          Attributes RemainOutput description: 
     *          Remaining number of outputs to print Hello World.
     * \param   RemainOutput    The value of RemainOutput attribute.
     * \param   state           The data validation flag.
     **/
    virtual void onRemainOutputUpdate( short RemainOutput, NEService::eDataStateType state );

    /**
     * \brief   Response callback.
     *          The response to hello world request.
     *          Overwrite, if need to handle Response call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   clientInfo  The client information set by servicing component. If empty or invalid ID, the message output failed.
     * \see     requestHelloWorld
     **/
    virtual void responseHelloWorld( const NELocalHelloWorld::sConnectedClient & clientInfo );

    /**
     * \brief   Server broadcast.
     *          Broadcast to notify all clients about connection
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   clientList  DESCRIPTION MISSED
     **/
    virtual void broadcastHelloClients( const NELocalHelloWorld::ConnectionList & clientList );

    /**
     * \brief   Server broadcast.
     *          DESCRIPTION MISSED
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     **/
    virtual void broadcastServiceUnavailable( void );

    /**
     * \brief   Overwrite to handle error of HelloWorld request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestHelloWorldFailed( NEService::eResultType FailureReason );

    /**
     * \brief   Overwrite to handle error of ClientShutdown request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestClientShutdownFailed( NEService::eResultType FailureReason );
    
/************************************************************************/
// IEProxyListener Overrides
/************************************************************************/
    /**
     * \brief   Triggered by Proxy, when gets service connected event.
     *          Make client initializations in this function. No request
     *          will be processed until this function is not called for
     *          client object. Also set listeners here if client is interested
     *          to receive update notifications.
     * \param   isConnected     The flag, indicating whether service is connected
     *                          or disconnected. Make cleanups and stop sending
     *                          requests or assigning for notification if
     *                          this flag is false. No event to Stub target will
     *                          be sent, until no service connected event is
     *                          received.
     * \param   proxy           The Service Interface Proxy object, which is
     *                          notifying service connection.
     * \return  Return true if this service connect notification was relevant to client object,
     *          i.e. if passed Proxy address is equal to the Proxy object that client has.
     *          If Proxy objects are not equal, it should return false;
     **/
    virtual bool serviceConnected( bool isConnected, ProxyBase & proxy );

/************************************************************************/
// IETimerConsumer interface overrides.
/************************************************************************/

    /**
     * \brief   Triggered when Timer is expired. 
     *          The passed Timer parameter is indicating object, which has been expired.
     *          Overwrite method to receive messages.
     * \param   timer   The timer object that is expired.
     **/
    virtual void processTimer( Timer & timer );

//////////////////////////////////////////////////////////////////////////
// hidden methods
//////////////////////////////////////////////////////////////////////////
private:
    inline LocalServiceClient & self( void );

    inline String timerName( Component & owner ) const;

//////////////////////////////////////////////////////////////////////////
// member variables
//////////////////////////////////////////////////////////////////////////
    const unsigned int  mMsTimeout; //!< The timeout in milliseconds to set for timer
    Timer               mTimer;     //!< The timer to trigger to send request to output message
    unsigned int        mID;        //!< The ID given by service.

//////////////////////////////////////////////////////////////////////////
// forbidden calls
//////////////////////////////////////////////////////////////////////////
private:
    LocalServiceClient( void );
    LocalServiceClient( const LocalServiceClient & /*src*/ );
    const LocalServiceClient & operator = ( const LocalServiceClient & /*src*/ );
};

inline LocalServiceClient & LocalServiceClient::self( void )
{
    return (*this);
}

#endif // AREG_EXAMPLES_13_IPCMIX_SHAREIPCMIX_LOCALSERVICECLIENT_HPP
