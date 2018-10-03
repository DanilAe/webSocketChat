#include "websocket.h"

webSocket::webSocket(const QUrl url, QObject *parent) : QObject(parent)
{
	webSock = new QWebSocket();
	connect(webSock, SIGNAL(connected()), this, SLOT(onConnected()));
	connect(webSock, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
	webSock->open(url);
	m_url = url;
}

void webSocket::onConnected()
{
	qDebug() << "Connected!";
	Isconnected = true;
	emit this->connected();
	connect(webSock, SIGNAL(textMessageReceived(QString)), this, SLOT(onReadyRead(QString)));
}

void webSocket::onDisconnected()
{
	qDebug() << "Disconnected!";
	Isconnected = false;
	emit this->disconnected();
}

void webSocket::loginIn(QString userName)
{
	QJsonDocument doc;
	QJsonObject root;
	root.insert("type", "login");
	root.insert("username", userName);
	doc.setObject(root);
	webSock->sendTextMessage(doc.toJson(QJsonDocument::Compact));
	this->m_usrName = userName;
}

void webSocket::sendMessage(QString message)
{
	QJsonDocument doc;
	QJsonObject root;
	root.insert("type", "message");
	root.insert("message", message);
	doc.setObject(root);
	webSock->sendTextMessage(doc.toJson(QJsonDocument::Compact));
}

void webSocket::onReadyRead(QString data)
{
	QJsonDocument doc = QJsonDocument::fromJson(QByteArray().append(data));
	if(doc.object().value("type") == "login")
		emit this->onLogined(doc.object().value("login_result").toBool());
	else if(doc.object().value("type") == "messages")
		emit this->onNewMessage(doc);
}



