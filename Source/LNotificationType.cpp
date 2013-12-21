/************************************************************

 LNotificationType.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

std::map<String, NotificationType> LNotificationType::notificationType = {
    { "dontSendNotification"  , NotificationType::dontSendNotification },
    { "sendNotification"      , NotificationType::sendNotification },
    { "sendNotificationSync"  , NotificationType::sendNotificationAsync },
    { "sendNotificationAsync" , NotificationType::sendNotificationSync }
};
