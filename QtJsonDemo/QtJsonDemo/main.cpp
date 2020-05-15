#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>

#if 0
int main(int argc, char *argv[]) {
	// �Զ�д��ʽ����Ŀ¼�µ�1.json�ļ��������ļ�����������Զ�����
	QFile file(QDir::homePath() + "/1.json");
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}
	// ʹ��QJsonObject��������ֵ�ԡ�
	QJsonObject jsonObject;
	jsonObject.insert("name", "tom");
	jsonObject.insert("age", "18");
	jsonObject.insert("time", QDateTime::currentDateTime().toString());

	// ʹ��QJsonDocument���ø�json����
	QJsonDocument jsonDoc;
	jsonDoc.setObject(jsonObject);

	// ��json���ı���ʽд���ļ����ر��ļ���
	file.write(jsonDoc.toJson());
	file.close();

	qDebug() << "Write to file";
	return 0;
}
#endif


//����ע�⵽JSON�е�ֵ�������ַ��������顢�������ֵȣ�����������Խ��ʹ��һ�¡�
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QThread>

int main(int argc, char *argv[]) {
	// �Զ�д��ʽ����Ŀ¼�µ�1.json�ļ��������ļ�����������Զ�����
	QFile file(QDir::currentPath() + "/1.json");
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}

	// ����ļ��е�ԭ������
	file.resize(0);

	// ʹ��QJsonArray���ֵ����д���ļ�
	QJsonArray jsonArray;

	for (int i = 0; i < 3; i++) {
		QJsonObject jsonObject;
		jsonObject.insert("name", QString::number(i + 1));
		jsonObject.insert("age", i + 18);
		jsonObject.insert("time", QDateTime::currentDateTime().toString());
		jsonArray.append(jsonObject);
		QThread::sleep(2);
	}

	QJsonObject jsonObject;
	jsonObject.insert("number", jsonArray.size());
	jsonArray.append(jsonObject);

	QJsonDocument jsonDoc;
	jsonDoc.setArray(jsonArray);

	file.write(jsonDoc.toJson());
	file.close();

	qDebug() << "Write to file";
	return 0;
}