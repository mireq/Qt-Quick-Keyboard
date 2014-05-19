#include "InputContextPlugin.h"
#include "InputContext.h"

#include <QDebug>

QPlatformInputContext *InputContextPlugin::create(const QString &system, const QStringList &paramList)
{
	Q_UNUSED(paramList);

	qDebug() << "AAAAAA" << system;

	if (system.compare(system, QStringLiteral("quickkeyboard"), Qt::CaseInsensitive) == 0) {
		return new InputContext;
	}
	return 0;
}
