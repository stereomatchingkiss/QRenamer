#include "MainWindow.hpp"
#include <QApplication>
#include <QMessageBox>
#include <QString>

#include <stdexcept>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try{
        MainWindow w;
        w.show();

        return a.exec();
    }catch(std::exception const &ex){
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr(ex.what()));

        return -1;
    }
}
