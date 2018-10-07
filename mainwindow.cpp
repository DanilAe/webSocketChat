#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	dialog = new DIalogNickName(this);

	webSock = new webSocket(QUrl("ws://62.109.21.96/ws/"), this);
	connect(webSock, SIGNAL(onLogined(bool)), this, SLOT(onLogined(bool)));
	connect(webSock, SIGNAL(onNewMessage(QJsonDocument)), this, SLOT(onNewMessage(QJsonDocument)));
	connect(webSock, SIGNAL(connected()), this, SLOT(onConnected()));
	connect(webSock, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

	this->setWindowIcon(QIcon(":/Ico.png"));
	this->setGeometry(QApplication::desktop()->width() / 2 - this->width() / 2 , QApplication::desktop()->height() / 2 - this->height() / 2, 0, 0);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onConnected()
{
	ui->statusBar->showMessage("Connected!", 20000);
	QString name;
	DIalogNickName* dialog = new DIalogNickName(this);
	name = dialog->getNickName();
	webSock->loginIn(name);
}

void MainWindow::onDisconnected()
{
	ui->statusBar->showMessage("Connecting...");
	QMessageBox::critical(this, "Warning!", "A web socket is not connected");
}

void MainWindow::on_buttonOk_clicked()
{
	if(ui->textEdit->toPlainText().isEmpty())
		return;
	if(webSock->isConnected())
	{
		webSock->sendMessage(ui->textEdit->toPlainText().trimmed());
		ui->textEdit->setPlainText("");
	}
	else
	{
		QMessageBox::critical(this, "Fault", "A web socket is not connected");
	}
}

void MainWindow::onNewMessage(QJsonDocument doc)
{
	QJsonArray arr = doc.object().value("body").toObject().value("messages").toArray();
	for(int i = 0; i < arr.count(); i++)
	{
		QJsonObject obj = arr.at(i).toObject();
		QString userName = obj.value("username").toString();
		QString messageText = obj.value("message").toString();
		int timeStamp = obj.value("dateTime").toInt();
		ui->listMessages->append(Helpers::getActionHtml(Helpers::getDateTimeS(timeStamp), userName, messageText));
	}
}

void MainWindow::onLogined(bool b)
{
	if(b)
	{
		ui->buttonOk->setEnabled(true);
	}
	else
	{
		QMessageBox::critical(this, "Fault", "Error during registration, try another nickname.");
		QString name;
		name = dialog->getNickName();
		webSock->loginIn(name);
	}
}
