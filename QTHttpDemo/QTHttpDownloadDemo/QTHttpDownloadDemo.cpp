#include "QTHttpDownloadDemo.h"

QTHttpDownloadDemo::QTHttpDownloadDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	manager = new QNetworkAccessManager(this);
	ui.progressBar->hide();
}

void QTHttpDownloadDemo::startRequest(QUrl url)
{
	reply = manager->get(QNetworkRequest(url));

	connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));

	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateDataReadProgress(qint64, qint64)));

	connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void QTHttpDownloadDemo::httpFinished()
{
	//��������غ��������ؽ�������Ȼ��ɾ��reply��file����
	ui.progressBar->hide();
	file->flush();
	file->close();
	reply->deleteLater();
	reply = 0;
	delete file;
	file = 0;
}

void QTHttpDownloadDemo::httpReadyRead()
{
	//�ж��Ƿ񴴽����ļ�������ǣ����ȡ���ص��������ݣ�Ȼ��д���ļ���
	if (file)
	{
		file->write(reply->readAll());
	}
}

void QTHttpDownloadDemo::updateDataReadProgress(qint64 totalBytes, qint64 bytesRead)
{
	ui.progressBar->setMaximum(totalBytes);

	ui.progressBar->setValue(bytesRead);
}

void QTHttpDownloadDemo::on_pushButton_clicked()
{
	url = ui.lineEdit->text();
	QFileInfo info(url.path());
	QString fileName(info.fileName());
	if (fileName.isEmpty())
	{
		fileName = "index.html";
	}

	file = new QFile(fileName);

	if (!file->open(QIODevice::WriteOnly))
	{
		qDebug() << "file open error";
		delete file;
		file = 0;
		return;
	}

	startRequest(url);
	ui.progressBar->setValue(0);
	ui.progressBar->show();
}