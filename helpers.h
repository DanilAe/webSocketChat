#ifndef HELPERS_H
#define HELPERS_H

#include <QObject>
#include <QDateTime>

class Helpers
{
	public:

		static QDateTime getDateTimeS(int timeStamp);

		static QString getActionHtml(QString dateTime, QString usrName, QString msgText);

		static QString getActionHtml(QDateTime dateTime, QString usrName, QString msgText)
		{
			return getActionHtml(dateTime.toString(Qt::SystemLocaleShortDate), usrName, msgText);
		}
};

#endif // HELPERS_H
