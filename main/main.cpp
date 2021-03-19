#include "MainWindow.h"
#include <QApplication>

int main( int argc, char * argv[] )
{
    QApplication appl( argc, argv );

    CMainWindow w;
    w.show();

    return appl.exec();
}


