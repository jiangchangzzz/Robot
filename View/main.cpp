#include "OccMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OccMainWindow w;
	w.show();
	return a.exec();
}
