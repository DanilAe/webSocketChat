#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QDateTime>

#include "websocket.h"
#include "helpers.h"
#include "dialognickname.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

		webSocket* webSock;
		DIalogNickName* dialog;

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:

		void on_buttonOk_clicked();

		void onNewMessage(QJsonDocument);

		void onLogined(bool);

		void onConnected();

		void onDisconnected();

	private:
		Ui::MainWindow *ui;

		QString boolToQString(bool b)
		{
			return b ? "true" : "false";
		}
};

#endif // MAINWINDOW_H
