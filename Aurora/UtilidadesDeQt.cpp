#include "UtilidadesDeQt.h"

#include <QStandardPaths>

QString UtilidadesDeQt::ObterPastaAppData()
{
	return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}
