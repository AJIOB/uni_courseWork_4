#pragma once

#include <QtCore/qglobal.h>

//to use shared heareds & build only static lib
#ifndef BUILD_STATIC
#define BUILD_STATIC
#endif

#ifndef BUILD_STATIC
# if defined(CONTROLLERQT_LIB)
#  define CONTROLLERQT_EXPORT Q_DECL_EXPORT
# else
#  define CONTROLLERQT_EXPORT Q_DECL_IMPORT
# endif
#else
# define CONTROLLERQT_EXPORT
#endif
