#include "InputContextPlugin.h"
#include "InputContextEmbedded.h"

QPlatformInputContext *InputContextPlugin::create(const QString &system, const QStringList &paramList)
{
	Q_UNUSED(paramList);

	QByteArray mainFile = qgetenv("QUICKKEYBOARD_MAIN_FILE");
	if (system.compare(system, QStringLiteral("quickkeyboard"), Qt::CaseInsensitive) == 0) {
		return new InputContextEmbedded(QString(mainFile));
	}
	return 0;
}
