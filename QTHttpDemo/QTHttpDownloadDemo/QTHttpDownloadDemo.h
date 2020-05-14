#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTHttpDownloadDemo.h"
#include <QtNetwork>

class QTHttpDownloadDemo : public QMainWindow
{
	Q_OBJECT

public:
	QTHttpDownloadDemo(QWidget *parent = Q_NULLPTR);
	void startRequest(QUrl url); //请求链接

private slots:
	void on_pushButton_clicked();
	void httpFinished(); //完成下载后的处理
	void httpReadyRead(); //接收到数据时的处理
	void updateDataReadProgress(qint64, qint64); //更新进度条
private:
	Ui::QTHttpDownloadDemoClass ui;

	QNetworkAccessManager *manager;

	QNetworkReply *reply;
	QUrl url; //存储网络地址
	QFile *file; //文件指针

};
