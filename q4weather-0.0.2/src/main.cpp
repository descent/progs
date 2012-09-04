#include <QApplication>

#include "mainwindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow mainwin;

	mainwin.show();
	return app.exec();
}
