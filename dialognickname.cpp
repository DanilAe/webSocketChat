#include "dialognickname.h"
#include "ui_dialognickname.h"

DIalogNickName::DIalogNickName(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DIalogNickName)
{
	ui->setupUi(this);
}

DIalogNickName::~DIalogNickName()
{
	delete ui;
}
