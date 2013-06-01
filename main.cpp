#include <QApplication>
#include "viewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Viewer viewer;
    viewer.setGeometry(200, 200, 600, 700);
    viewer.show();
    viewer.setWindowTitle("Buddhabrot");
    viewer.start();

    return a.exec();
}
