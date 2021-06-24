#ifndef MYTABLE_H
#define MYTABLE_H

#include "mymodel.h"
#include "cryptonames.h"

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

/*!
 * \brief The MyTable is the GUI that retrieves and displays the exchange rate information of the target cryptocurrencies.
 */
class MyTable : public QTableView
{
    Q_OBJECT
private:
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    MyModel *myModel;
    QSet<QString> targetSet;
    QMap<QString, CryptoNames> cryptoMap;
private slots:
    void tableDownloadFinished();
    void symbolsDownloadFinished();
public:
    MyTable(QSet<QString> targetSet);
};

#endif // MYTABLE_H
