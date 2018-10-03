#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	webSock = new webSocket(QUrl("ws://62.109.21.96/ws/"), this);
	this->setWindowIcon(QIcon(":/Ico.png"));
	connect(webSock, SIGNAL(onLogined(bool)), this, SLOT(onLogined(bool)));
	connect(webSock, SIGNAL(onNewMessage(QJsonDocument)), this, SLOT(onNewMessage(QJsonDocument)));
	connect(webSock, SIGNAL(connected()), this, SLOT(onConnected()));
	connect(webSock, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onConnected()
{
	ui->statusBar->showMessage("Connected!", 20000);
}

void MainWindow::onDisconnected()
{
	ui->statusBar->showMessage("Connecting...");
}

void MainWindow::on_buttonOk_clicked()
{
	if(ui->textEdit->toPlainText().isEmpty())
		return;
	if(webSock->isConnected())
	{
		if(webSock->logined())
		{
			webSock->sendMessage(ui->textEdit->toPlainText().trimmed());
		}
		else
			webSock->loginIn(ui->textEdit->toPlainText().trimmed());
		ui->textEdit->setPlainText("");
	}
	else
	{
		QMessageBox::critical(this, "Fault", "A web socket is not connected");
	}
}

void MainWindow::onNewMessage(QJsonDocument doc)
{
	QJsonArray arr = doc.object().value("messages").toArray();
	for(int i = 0; i < arr.count(); i++)
	{
		QJsonObject obj;
		obj = arr.at(i).toObject().value("value").toObject();
		QString userName = obj.value("username").toString();
		QString messageText = obj.value("message").toString();
		QString text = userName + ": " + messageText.trimmed();
		ui->listMessages->append(text);
	}
}

void MainWindow::onLogined(bool b)
{
	if(b)
	{
		ui->textEdit->setPlaceholderText("Write a message");
	}
	else
		QMessageBox::critical(this, "Fault", "Error during registration, try another nickname.");
}
