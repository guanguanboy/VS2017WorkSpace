#include "QTHttpDownloadDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTHttpDownloadDemo w;
	w.show();
	return a.exec();
}
