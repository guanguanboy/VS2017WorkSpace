#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTHttpDownloadDemo.h"
#include <QtNetwork>

class QTHttpDownloadDemo : public QMainWindow
{
	Q_OBJECT

public:
	QTHttpDownloadDemo(QWidget *parent = Q_NULLPTR);
	void startRequest(QUrl url); //��������

private slots:
	void on_pushButton_clicked();
	void httpFinished(); //������غ�Ĵ���
	void httpReadyRead(); //���յ�����ʱ�Ĵ���
	void updateDataReadProgress(qint64, qint64); //���½�����
private:
	Ui::QTHttpDownloadDemoClass ui;

	QNetworkAccessManager *manager;

	QNetworkReply *reply;
	QUrl url; //�洢�����ַ
	QFile *file; //�ļ�ָ��

};
