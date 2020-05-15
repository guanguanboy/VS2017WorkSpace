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
	// 以读写方式打开主目录下的1.json文件，若该文件不存在则会自动创建
	QFile file(QDir::homePath() + "/1.json");
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}
	// 使用QJsonObject对象插入键值对。
	QJsonObject jsonObject;
	jsonObject.insert("name", "tom");
	jsonObject.insert("age", "18");
	jsonObject.insert("time", QDateTime::currentDateTime().toString());

	// 使用QJsonDocument设置该json对象
	QJsonDocument jsonDoc;
	jsonDoc.setObject(jsonObject);

	// 将json以文本形式写入文件并关闭文件。
	file.write(jsonDoc.toJson());
	file.close();

	qDebug() << "Write to file";
	return 0;
}
#endif


//我们注意到JSON中的值可以是字符串、数组、对象、数字等，因此我们试试结合使用一下。
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
	// 以读写方式打开主目录下的1.json文件，若该文件不存在则会自动创建
	QFile file(QDir::currentPath() + "/1.json");
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}

	// 清空文件中的原有内容
	file.resize(0);

	// 使用QJsonArray添加值，并写入文件
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