#include "gui_tetrix_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
    GUITetrixMainWindow w(25);
	
    w.show();

    return a.exec();
}
