#ifndef QREDIS_EXPORT_H
#define QREDIS_EXPORT_H

#include <QtCore/qglobal.h>

#if defined(qredis_EXPORTS)
    #define QREDIS_EXPORT Q_DECL_EXPORT
#else
    #define QREDIS_EXPORT Q_DECL_IMPORT
#endif

#endif // QREDIS_EXPORT_H
