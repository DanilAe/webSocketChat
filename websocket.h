#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QWebSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class webSocket : public QObject
{
		Q_OBJECT
		QWebSocket* webSock;
		QUrl m_url;
		QString m_usrName;
		bool Isconnected;
	public:

		explicit webSocket(const QUrl url, QObject *parent = nullptr);

		void loginIn(QString userName);

		bool logined()
		{
			return !m_usrName.isEmpty();
		}

		bool isConnected()
		{
			return Isconnected;
		}

		QString getUsrName()
		{
			return m_usrName;
		}

	signals:

		void onLogined(bool);

		void onNewMessage(QJsonDocument);

		void connected();

		void disconnected();

	private slots:

		void onReadyRead(QString);

		void onConnected();

		void onDisconnected();

	public slots:

		void sendMessage(QString message);

		void getConnect()
		{
			if(!isConnected())
				webSock->open(m_url);
		}

};

#endif // WEBSOCKET_H
