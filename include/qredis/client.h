#ifndef QREDIS_CLIENT_H
#define QREDIS_CLIENT_H

#include <QObject>

#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT Client : public QObject
    {
        Q_OBJECT
        
        public:
            
            Client();
            virtual ~Client();
    };
}

#endif // QREDIS_CLIENT_H