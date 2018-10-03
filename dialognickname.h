#ifndef DIALOGNICKNAME_H
#define DIALOGNICKNAME_H

#include <QDialog>

namespace Ui {
	class DIalogNickName;
}

class DIalogNickName : public QDialog
{
		Q_OBJECT

	public:
		explicit DIalogNickName(QWidget *parent = 0);
		~DIalogNickName();

	private slots:

	private:
		Ui::DIalogNickName *ui;
};

#endif // DIALOGNICKNAME_H
