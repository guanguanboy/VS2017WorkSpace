#include "QTHttpDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTHttpDemo w;
	w.show();
	return a.exec();
}
