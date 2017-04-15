#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CONTROLLERQT_LIB)
#  define CONTROLLERQT_EXPORT Q_DECL_EXPORT
# else
#  define CONTROLLERQT_EXPORT Q_DECL_IMPORT
# endif
#else
# define CONTROLLERQT_EXPORT
#endif
