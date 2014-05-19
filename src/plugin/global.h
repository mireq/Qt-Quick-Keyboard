#ifndef GLOBAL_H_CTI1IPAP
#define GLOBAL_H_CTI1IPAP

#include <QtCore/QtGlobal>

#if defined(QUICKKEYBOARD_LIBRARY)
#  define QUICKKEYBOARD_EXPORT Q_DECL_EXPORT
#else
#  define QUICKKEYBOARD_EXPORT Q_DECL_IMPORT
#endif

#endif /* end of include guard: GLOBAL_H_CTI1IPAP */

