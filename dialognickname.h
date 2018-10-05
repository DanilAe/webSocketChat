#ifndef DIALOGNICKNAME_H
#define DIALOGNICKNAME_H

#include <QDialog>
#include <QEventLoop>

namespace Ui {
	class DIalogNickName;
}

class DIalogNickName : public QDialog
{
		Q_OBJECT

	public:
		explicit DIalogNickName(QWidget *parent = 0);
		~DIalogNickName();

		QString getNickName();

	private:
		Ui::DIalogNickName *ui;
};

#endif // DIALOGNICKNAME_H
