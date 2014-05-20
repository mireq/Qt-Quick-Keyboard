#include "InputContextPlugin.h"
#include "InputContextEmbedded.h"

QPlatformInputContext *InputContextPlugin::create(const QString &system, const QStringList &paramList)
{
	Q_UNUSED(paramList);

	if (system.compare(system, QStringLiteral("quickkeyboard"), Qt::CaseInsensitive) == 0) {
		return new InputContextEmbedded;
	}
	return 0;
}
