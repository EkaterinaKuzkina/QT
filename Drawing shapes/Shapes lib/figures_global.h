#ifndef FIGURES_GLOBAL_H
#define FIGURES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FIGURES_LIBRARY)
#  define FIGURESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FIGURESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FIGURES_GLOBAL_H
