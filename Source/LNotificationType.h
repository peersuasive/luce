/************************************************************

 LNotificationType.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_NOTIFICATION_TYPE_H
#define __LUCE_NOTIFICATION_TYPE_H

class LNotificationType {
    static std::map<String, NotificationType> notificationType;

public:
    static const NotificationType get(const String& n) {
        return notificationType[ n ];
    }
};

#endif // __LUCE_NOTIFICATION_TYPE_H
