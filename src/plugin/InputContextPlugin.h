#ifndef INPUTCONTEXTPLUGIN_H_NWSQGKER
#define INPUTCONTEXTPLUGIN_H_NWSQGKER

#include <qpa/qplatforminputcontextplugin_p.h>
#include "global.h"

class QUICKKEYBOARD_EXPORT InputContextPlugin: public QPlatformInputContextPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "kbd.json")
public:
	QPlatformInputContext *create(const QString &system, const QStringList &paramList);
}; /* -----  end of class InputContextPlugin  ----- */

#endif /* end of include guard: INPUTCONTEXTPLUGIN_H_NWSQGKER */

