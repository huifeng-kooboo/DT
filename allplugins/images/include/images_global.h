#ifndef Images_GLOBAL_H
#define Images_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(Images_LIBRARY)
#  define Images_EXPORT Q_DECL_EXPORT
#else
#  define Images_EXPORT Q_DECL_IMPORT
#endif

#endif // Images_GLOBAL_H
