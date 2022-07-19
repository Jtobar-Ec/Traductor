#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator T;
    QStringList langs;
    langs << "Español" << "Coreano" << "Filandes";

    const QString lang= QInputDialog::getItem(NULL,
                                        "Language",
                                        "Select a language",
                                        langs);
    if (lang == "Coreano"){
        T.load(":/coreano.qm");
    }else if (lang == "Filandes"){
        T.load(":/filandes.qm");
    }
    if (lang != "Español"){
        a.installTranslator(&T);
    }
    a.setStyle("fusion");
    Principal w;
    w.show();
    return a.exec();

}
