#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MESSAGEPROCESSLIB_LIB)
#  define MESSAGEPROCESSLIB_EXPORT Q_DECL_EXPORT
# else
#  define MESSAGEPROCESSLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define MESSAGEPROCESSLIB_EXPORT
#endif
