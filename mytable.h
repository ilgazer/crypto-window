#ifndef MYTABLE_H
#define MYTABLE_H

#include "mymodel.h"

#include <QTableView>
#include <QObject>
#include <QTableView>
#include <QJsonDocument>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <iostream>

class MyTable : public QTableView
{
    Q_OBJECT
private:
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    MyModel *myModel;
private slots:
    void downloadFinished();
public:
    MyTable();
    QUrl get_url();
};

#endif // MYTABLE_H
