#pragma once

#include <QtGlobal>

#if defined(EASYMOTION_LIBRARY)
#  define EASYMOTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EASYMOTIONSHARED_EXPORT Q_DECL_IMPORT
#endif
