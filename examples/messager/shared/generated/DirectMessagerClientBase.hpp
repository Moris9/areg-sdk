//////////////////////////////////////////////////////////////////////////
// Begin generate shared/generated/DirectMessagerClientBase.hpp file
//////////////////////////////////////////////////////////////////////////
#ifndef  SHARED_GENERATED_DIRECTMESSAGERCLIENTBASE_HPP
#define  SHARED_GENERATED_DIRECTMESSAGERCLIENTBASE_HPP
/************************************************************************
 * (c) copyright    2021
 *                  Create by AREG SDK code generator tool from source DirectMessager.
 * Generated at     23.05.2021  00:18:59 GMT+02:00 
 ************************************************************************/

/************************************************************************
 * \file            shared/generated/DirectMessagerClientBase.hpp
 * \ingroup         DirectMessager Service Interface
 * \brief           This is an automatic generated code of DirectMessager Service Interface Client base class declaration.
 ************************************************************************/

/************************************************************************
 * Include files
 ************************************************************************/
#include "areg/base/GEGlobal.h"
#include "shared/generated/NEDirectMessager.hpp"
#include "areg/component/ClientBase.hpp"
#include "areg/component/IEProxyListener.hpp"
#include "areg/component/NotificationEvent.hpp"

#include "shared/generated/private/DirectMessagerProxy.hpp"

/************************************************************************
 * Dependencies
 ************************************************************************/
class Component;
class DispatcherThread;

//////////////////////////////////////////////////////////////////////////
// DirectMessagerClientBase class declaration.
//////////////////////////////////////////////////////////////////////////
/**
 * \brief       The interface of DirectMessager Service Interface
 *              Client base object. This object should be inherited
 *              and overrides should be implemented.
 *
 *              The service interface of direct connection and messaging used in chat-room.
 **/
class DirectMessagerClientBase  : public    IEProxyListener, private ClientBase
{
//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor. Protected
//////////////////////////////////////////////////////////////////////////
protected:
    /**
     * \brief   Initialize DirectMessager Service Interface client object. 
     *          Specifies used service and owner thread.
     * \param   roleName    The role name assigned to DirectMessager servicing component object.
     * \param   ownerThread The name of component owner thread to dispatch messages.
     *                      If NULL, all messages are dispatched in current component thread.
     **/
    DirectMessagerClientBase( const char* roleName, const char * ownerThread = static_cast<const char *>(NULL) );

    /**
     * \brief   Initialize DirectMessager Service Interface client object.
     *          Specifies used service and owner thread.
     * \param   roleName    The role name assigned to DirectMessager servicing component object.
     * \param   ownerThread The instance of component owner thread to dispatch messages.
     **/
    DirectMessagerClientBase( const char* roleName, DispatcherThread & ownerThread );

    /**
     * \brief   Initialize DirectMessager Service Interface client object.
     *          Specifies used service and owner component.
     * \param   roleName    The role name assigned to DirectMessager servicing component object.
     * \param   owner       The instance of client owner component. The component object should be already initialized.
     * \note    When this constructor is used, it is important that the Component object is already initialized.
     *          and the component thread is set.
     **/
    DirectMessagerClientBase( const char* roleName, Component & owner );

    /**
     * \brief   Destructor.
     **/
    virtual ~DirectMessagerClientBase( void );

//////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Clears all notifications, stops receiving notifications from server
     **/
    void clearAllNotifications( void );

    /**
     * \brief   Returns true if the specified certain notification is already assigned.
     *          Otherwise returns false.
     * \param   msgId   The ID of message to check.
     **/
    bool isNotificationAssigned( NEDirectMessager::eMessageIDs msgId ) const;

    /**
     * \brief   Returns true if client object has got connection with servicing component
     **/
    bool isConnected( void ) const;

//////////////////////////////////////////////////////////////////////////
// Start Service Interface operations / attributes and overrides declaration
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// DirectMessager Interface Attributes
//////////////////////////////////////////////////////////////////////////
public:
/************************************************************************
 * Attribute ChatParticipants functions
 ************************************************************************/
    /**
     * \brief   Returns true if value of ChatParticipants attribute is valid.
     *          If Update Notification is disabled, this method will return false.
     **/
    bool isChatParticipantsValid( void ) const;
    /**
     * \brief   Returns the value of ChatParticipants attribute.
     *          To get valid value, the Update Notification should be enabled. 
     *          Attribute ChatParticipants description: 
     *          The list of char-room participants
     * \param   state   On returns, contains the validation flag of attribute data. 
     *                  Check validation flag before use attribute value.
     * \see     isChatParticipantsValid, notifyChatParticipantsUpdate, onChatParticipantsUpdate
     **/
    const NEDirectMessager::ListParticipants & getChatParticipants( NEService::eDataStateType & state ) const;
    /**
     * \brief   Call to enable or disable receiving notifications on ChatParticipants attribute update.
     *          Once notification is enabled and the data is updated, 
     *          the getChatParticipants method will return valid data 
     *          Attribute ChatParticipants description:
     *          The list of char-room participants
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     * \see     isChatParticipantsValid, getChatParticipants, onChatParticipantsUpdate
     **/
    void notifyOnChatParticipantsUpdate( bool notify = true );
    /**
     * \brief   Triggered, when ChatParticipants attribute is updated. The function contains
     *          attribute value and validation flag. When notification is enabled,
     *          the method should be overwritten in derived class.
     *          Attributes ChatParticipants description: 
     *          The list of char-room participants
     * \param   ChatParticipants    The value of ChatParticipants attribute.
     * \param   state               The data validation flag.
     **/
    virtual void onChatParticipantsUpdate( const NEDirectMessager::ListParticipants & ChatParticipants, NEService::eDataStateType state );


//////////////////////////////////////////////////////////////////////////
// DirectMessager Interface Requests / Responses / Broadcasts
//////////////////////////////////////////////////////////////////////////
public:

/************************************************************************
 * Request ChatJoin
 ************************************************************************/
    /**
     * \brief   Request call.
     *          Request to join chat. The participant should be in the list of connections
     * \param   participant The participant to join chat. The participant should be in the connection list.
     * \param   timeConnect The timestamp when the request was sent.
     * \return  The sequence count number of call
     * \see     responseChatJoin
     **/
    unsigned int requestChatJoin( const NEDirectMessager::sParticipant & participant, const DateTime & timeConnect );
    /**
     * \brief   Overwrite to handle error of ChatJoin request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestChatJoinFailed( NEService::eResultType FailureReason );
    
/************************************************************************
 * Request MessageSend
 ************************************************************************/
    /**
     * \brief   Request call.
     *          Request to send a message, has no response
     * \param   sender      The participant structure of message sender
     * \param   msgText     The text message to send
     * \param   timeSent    The timestamp when the message is requested to send.
     * \see     Has no response
     **/
    inline void requestMessageSend( const NEDirectMessager::sParticipant & sender, const String & msgText, const DateTime & timeSent );
    /**
     * \brief   Overwrite to handle error of MessageSend request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestMessageSendFailed( NEService::eResultType FailureReason );
    
/************************************************************************
 * Request MessageType
 ************************************************************************/
    /**
     * \brief   Request call.
     *          The request to send message while typing a text. Has no response.
     * \param   participant The structure of participant while sending message during typing.
     * \param   msgText     The text message while typing.
     * \see     Has no response
     **/
    inline void requestMessageType( const NEDirectMessager::sParticipant & participant, const String & msgText );
    /**
     * \brief   Overwrite to handle error of MessageType request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestMessageTypeFailed( NEService::eResultType FailureReason );
    
/************************************************************************
 * Request ChatLeave
 ************************************************************************/
    /**
     * \brief   Request call.
     *          The request to leave chat-room. Has no response.
     * \param   participant The structure of chat-room participant.
     * \param   timeLeave   Timestamp when it was requested to leave chat-room.
     * \see     Has no response
     **/
    inline void requestChatLeave( const NEDirectMessager::sParticipant & participant, const DateTime & timeLeave );
    /**
     * \brief   Overwrite to handle error of ChatLeave request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestChatLeaveFailed( NEService::eResultType FailureReason );
    
/************************************************************************
 * Response ChatJoin
 ************************************************************************/
    /**
     * \brief   Response callback.
     *          Response to join chat
     *          Overwrite, if need to handle Response call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   succeed         Flag, indicating whether connection is accepted or not.
     * \param   listParticipant The list of participants.
     * \param   timeConnect     Timestamp when it was requested to join chat
     * \param   timeConnected   Timestamp when the request to join was accepted and new participants was registered.
     * \see     requestChatJoin
     **/
    virtual void responseChatJoin( bool succeed, const NEDirectMessager::ListParticipants & listParticipant, const DateTime & timeConnect, const DateTime & timeConnected );
    /**
     * \brief   Call to enable or disable receiving notifications on ChatJoin response call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void notifyOnResponseChatJoin( bool notify = true );

/************************************************************************
 * Broadcast MessageSent
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Informs all connected servicing clients that the message is sent.
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   sender      The structure of participant, who sent the message.
     * \param   msgText     The message, which was sent.
     * \param   timeSent    The timestamp when the message was sent.
     **/
    virtual void broadcastMessageSent( const NEDirectMessager::sParticipant & sender, const String & msgText, const DateTime & timeSent );
    /**
     * \brief   Call to enable or disable receiving notifications on MessageSent broadcast call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void notifyOnBroadcastMessageSent( bool notify = true );

/************************************************************************
 * Broadcast MessageTyped
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Informs all connected servicing client that the text was typed.
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   participant The structure of participant, who initiated message during typing.
     * \param   msgText     The text message while typing.
     **/
    virtual void broadcastMessageTyped( const NEDirectMessager::sParticipant & participant, const String & msgText );
    /**
     * \brief   Call to enable or disable receiving notifications on MessageTyped broadcast call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void notifyOnBroadcastMessageTyped( bool notify = true );

/************************************************************************
 * Broadcast ParticipantJoined
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Informs new participant joined chat-room
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   participant The structure of participant, joined chat-room.
     * \param   timeJoined  Timestamp when participant joined the chat-room
     **/
    virtual void broadcastParticipantJoined( const NEDirectMessager::sParticipant & participant, const DateTime & timeJoined );
    /**
     * \brief   Call to enable or disable receiving notifications on ParticipantJoined broadcast call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void notifyOnBroadcastParticipantJoined( bool notify = true );

/************************************************************************
 * Broadcast ParticipantLeft
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Informs that a participant left chat-room.
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   participant The structure of participant, who left the chat-room.
     * \param   timeLeft    The timestamp when the participant left chat-room.
     **/
    virtual void broadcastParticipantLeft( const NEDirectMessager::sParticipant & participant, const DateTime & timeLeft );
    /**
     * \brief   Call to enable or disable receiving notifications on ParticipantLeft broadcast call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void notifyOnBroadcastParticipantLeft( bool notify = true );

/************************************************************************
 * Broadcast ChatClosed
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Informs all service connected clients that the chat-room is closed. Message will be impossible.
     *          Overwrite, if need to handle Broadcast call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     **/
    virtual void broadcastChatClosed( void );
    /**
     * \brief   Call to enable or disable receiving notifications on ChatClosed broadcast call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void notifyOnBroadcastChatClosed( bool notify = true );

//////////////////////////////////////////////////////////////////////////
// End Service Interface operations / attributes and overrides declaration
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////////
protected:
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

protected:
/************************************************************************/
// DirectMessagerClientBase Error Handling overrides
/************************************************************************/

    /**
     * \brief   Overwrite this method if need to make error handling on invalid response
     * \param   InvalidRespId   The ID of invalid response
     **/
    virtual void invalidResponse( NEDirectMessager::eMessageIDs InvalidRespId );

    /**
     * \brief   Overwrite this method if need to make error handling on invalid request
     * \param   InvalidReqId    The ID of invalid request
     **/
    virtual void invalidRequest( NEDirectMessager::eMessageIDs InvalidReqId );
    
    /**
     * \brief   By default, the function calls appropriate request failure function.
     *          Overwrite this method if need to make error handling on request failed.
     * \param   msgId           The ID of either response of request message, which failed. Normally ID of request.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void requestFailed( NEDirectMessager::eMessageIDs FailureMsgId, NEService::eResultType FailureReason );

//////////////////////////////////////////////////////////////////////////
// Attributes
//////////////////////////////////////////////////////////////////////////
protected:

    /**
     * \brief   Returns the current sequence number
     **/
    unsigned int getCurrentSequenceNr( void ) const;

    /**
     * \brief   Call to recreate Proxy for the client. This call will remove and unregister all existing notifications
     *          and the client will not receive pending update or response notifications. 
     *          The client first will receive disconnect message, then again connect.
     *          Reset update notifications manually in connect if need.          
     *          This function call can be used when the client instance should be registered and run in new thread.
     *
     * \return  Returns true if Proxy was created with success.
     **/
     bool recreateProxy( void );

     /**
      * \brief  Returns pointer to client dispatcher thread where the messages are dispatched.
      *         The function can return NULL if Proxy was not instantiated yet.
      **/
     DispatcherThread * getDispatcherThread( void );

//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////
private:
    /**
     * \brief   Connection flag. If true, the client object is connected to server
     **/
    bool                mIsConnected;
    /**
     * \brief   The counter of sequence number
     **/
    unsigned int        mCurrSequenceNr;
    /**
     * \brief   Pointer of Proxy object providing communication
     **/
    DirectMessagerProxy *   mProxy;

//////////////////////////////////////////////////////////////////////////
// Hidden methods
//////////////////////////////////////////////////////////////////////////
private:
/************************************************************************/
// IENotificationEventConsumer overrides
/************************************************************************/

    /**
     * \brief   Is processing notification event calls.
     * \param   eventElem   Notification Event object to process
     **/
    virtual void processNotificationEvent( NotificationEvent & eventElem );
    
private:
    /**
     * \brief   Enables / Disables notification flags on appropriate message call.
     * \param   msgId   The ID of message to enable / disable notification
     * \param   notify  If true, the notification is enabled. 
     *                  If false, the notification is disabled.
     * \param   always  Flag, indicating whether should notify always or not.
     *                  if 'notify' parameter is true and the notification is already
     *                  assigned, then if parameter 'always' is true, it will trigger
     *                  notification immediately after call. 
     **/
    void notifyOn( NEDirectMessager::eMessageIDs msgId, bool notify, bool always = false );
    /**
     * \brief   Returns reference of DirectMessagerClientBase object
     **/
    DirectMessagerClientBase & self( void );

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
private:
    DirectMessagerClientBase( void );
    DirectMessagerClientBase( const DirectMessagerClientBase & /* src */ );
    const DirectMessagerClientBase & operator = ( const DirectMessagerClientBase & /* src */ );
};

//////////////////////////////////////////////////////////////////////////
// DirectMessagerClientBase class inline functions implementation
//////////////////////////////////////////////////////////////////////////

inline DirectMessagerClientBase & DirectMessagerClientBase::self( void )
{
    return (*this);
}

inline unsigned int DirectMessagerClientBase::getCurrentSequenceNr( void ) const
{
    return mCurrSequenceNr;
}

inline bool DirectMessagerClientBase::isConnected( void ) const
{
    return mIsConnected;
}

inline bool DirectMessagerClientBase::isNotificationAssigned( NEDirectMessager::eMessageIDs msgId ) const
{
    return mProxy->hasNotificationListener(static_cast<unsigned int>(msgId));
}

/************************************************************************
 * Attribute inline functions
 ************************************************************************/

inline bool DirectMessagerClientBase::isChatParticipantsValid( void ) const
{
   return mProxy->isChatParticipantsValid( );
}
inline const NEDirectMessager::ListParticipants & DirectMessagerClientBase::getChatParticipants( NEService::eDataStateType & state ) const
{
    return mProxy->getChatParticipants( state );
}

inline void DirectMessagerClientBase::notifyOnChatParticipantsUpdate( bool notify /* = true */ )
{
    notifyOn( NEDirectMessager::MSG_ID_ChatParticipants, notify, false );
}

/************************************************************************
 * Request calls
 ************************************************************************/

inline unsigned int DirectMessagerClientBase::requestChatJoin( const NEDirectMessager::sParticipant & participant, const DateTime & timeConnect )
{
    return mProxy->requestChatJoin( static_cast<IENotificationEventConsumer &>(self()), participant, timeConnect );
}

inline void DirectMessagerClientBase::requestMessageSend( const NEDirectMessager::sParticipant & sender, const String & msgText, const DateTime & timeSent )
{
    mProxy->requestMessageSend( sender, msgText, timeSent );
}

inline void DirectMessagerClientBase::requestMessageType( const NEDirectMessager::sParticipant & participant, const String & msgText )
{
    mProxy->requestMessageType( participant, msgText );
}

inline void DirectMessagerClientBase::requestChatLeave( const NEDirectMessager::sParticipant & participant, const DateTime & timeLeave )
{
    mProxy->requestChatLeave( participant, timeLeave );
}

/************************************************************************
 * Response notifications
 ************************************************************************/

inline void DirectMessagerClientBase::notifyOnResponseChatJoin( bool notify /* = true */ )
{
    notifyOn(NEDirectMessager::MSG_ID_responseChatJoin, notify, false);
}

/************************************************************************
 * Broadcast notifications
 ************************************************************************/

inline void DirectMessagerClientBase::notifyOnBroadcastMessageSent( bool notify /* = true */ )
{
    notifyOn(NEDirectMessager::MSG_ID_broadcastMessageSent, notify, false);
}

inline void DirectMessagerClientBase::notifyOnBroadcastMessageTyped( bool notify /* = true */ )
{
    notifyOn(NEDirectMessager::MSG_ID_broadcastMessageTyped, notify, false);
}

inline void DirectMessagerClientBase::notifyOnBroadcastParticipantJoined( bool notify /* = true */ )
{
    notifyOn(NEDirectMessager::MSG_ID_broadcastParticipantJoined, notify, false);
}

inline void DirectMessagerClientBase::notifyOnBroadcastParticipantLeft( bool notify /* = true */ )
{
    notifyOn(NEDirectMessager::MSG_ID_broadcastParticipantLeft, notify, false);
}

inline void DirectMessagerClientBase::notifyOnBroadcastChatClosed( bool notify /* = true */ )
{
    notifyOn(NEDirectMessager::MSG_ID_broadcastChatClosed, notify, false);
}

#endif   // SHARED_GENERATED_DIRECTMESSAGERCLIENTBASE_HPP

//////////////////////////////////////////////////////////////////////////
// End generate shared/generated/DirectMessagerClientBase.hpp file
//////////////////////////////////////////////////////////////////////////
