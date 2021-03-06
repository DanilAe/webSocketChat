#include "helpers.h"

QDateTime Helpers::getDateTimeS(int timeStamp)
{
	QDateTime dateTime;
	dateTime.setTime_t(timeStamp);
	return dateTime;
}

QString Helpers::getActionHtml(QString dateTime, QString usrName, QString msgText)
{
	QString html = QObject::tr("<div><font size=\"3\">%0: %1</font><br><font size=\"1\" color=\"gray\">%2</font></div>")
			.arg(usrName, msgText, dateTime);
	return html;
}
