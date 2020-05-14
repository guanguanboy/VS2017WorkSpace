#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTHttpDemo.h"
#include <QtNetwork>

class QTHttpDemo : public QMainWindow
{
	Q_OBJECT

public:
	QTHttpDemo(QWidget *parent = Q_NULLPTR);

private slots:
	void replyFinished(QNetworkReply *);

private:
	Ui::QTHttpDemoClass ui;

	QNetworkAccessManager *manager;

};
