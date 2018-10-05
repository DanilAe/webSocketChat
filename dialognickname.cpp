#include "dialognickname.h"
#include "ui_dialognickname.h"

DIalogNickName::DIalogNickName(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DIalogNickName)
{
	ui->setupUi(this);
	this->setModal(true);
}

DIalogNickName::~DIalogNickName()
{
	delete ui;
}

QString DIalogNickName::getNickName()
{
	this->show();
	QEventLoop lp;
	connect(ui->buttonBox, SIGNAL(accepted()), &lp, SLOT(quit()));
	connect(ui->buttonBox, SIGNAL(rejected()), parent(), SLOT(close()));
	lp.exec();
	return ui->lineEdit->text();
}
