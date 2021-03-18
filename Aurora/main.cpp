#include "CQuadroPrincipal.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Kevin");
    QCoreApplication::setOrganizationDomain("Kevin.com");
    QCoreApplication::setApplicationName("KEVENGINE");

    QApplication a(argc, argv);
    QFile styleSheet(":/arquivos/estilos/StyleSheet.qss");

    if (styleSheet.open(QFile::ReadOnly))
    {
        a.setStyleSheet(styleSheet.readAll());
    }

    CQuadroPrincipal w = new CQuadroPrincipal(nullptr);
    w.PosCarregamento();
    w.showMaximized();
    return a.exec();
}
