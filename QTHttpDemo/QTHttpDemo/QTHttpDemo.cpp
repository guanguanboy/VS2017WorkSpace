#include "QTHttpDemo.h"
#include <QTextCodec>

QTHttpDemo::QTHttpDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	manager = new QNetworkAccessManager(this);

	connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));

	manager->get(QNetworkRequest(QUrl("https://cn.bing.com/")));
}

void QTHttpDemo::replyFinished(QNetworkReply *reply)
{
	QTextCodec *codec = QTextCodec::codecForName("utf8");
	QString all = codec->toUnicode(reply->readAll());
	ui.textBrowser->setText(all);
	reply->deleteLater();
}