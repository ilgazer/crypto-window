#ifndef MYTABLE_H
#define MYTABLE_H

#include "mymodel.h"

#include <QTableView>
#include <QObject>
#include <QTableView>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <iostream>

class MyTable : public QTableView
{
    Q_OBJECT
private:
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    MyModel *myModel;
    QSet<QString> nameSet;
private slots:
    void tableDownloadFinished();
    void symbolsDownloadFinished();
public:
    MyTable(QSet<QString> nameSet);
    QUrl getUrl();
};

#endif // MYTABLE_H
