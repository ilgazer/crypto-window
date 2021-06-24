#include "mytable.h"
#include<iostream>
#include<fstream>

/*!
 * \brief MyTable::MyTable is the constructor of MyTable
 * \param nameSet the set of cryptocurrenct targets we will be displaying on screen
 */
MyTable::MyTable(QSet<QString> targetSet): targetSet(targetSet)
{   
    setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);

    QUrl url("https://api.coingecko.com/api/v3/coins/list");
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyTable::symbolsDownloadFinished);
}

/*!
 * \brief MyTable::symbolsDownloadFinished finds the name, symbol and id's of the target cryptocurrencies and makes another network request for exchange rates
 *
 * This slot is called when QtNetwork is done with downloading the list of all coins from Coingecko. All the targets in \variable targetSet are compared to the
 * names, ids and symbols ofthe cryptocurrencies supported by coingecko. As the result, \variable cryptoMap is populated with the information of the target
 * cryptocurrencies. Furthermore, another network request is made to retrieve the exchange rates of the target cryptocurrencies.
 */

void MyTable::symbolsDownloadFinished()
{
    std::cout << "symbols!" << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes.data());
    QJsonArray arr = doc.array();

    QString url("https://api.coingecko.com/api/v3/simple/price?vs_currencies=usd,eur,gbp&ids=");

    for(const QJsonValueRef &value: arr){
        CryptoNames obj(value.toObject());
        if(targetSet.contains(obj.symbol) || targetSet.contains(obj.name) || targetSet.contains(obj.id)){
            cryptoMap.insert(obj.id, obj);
            url.append(obj.id);
            url.append(",");
        }
    }
    reply = qnam.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, &MyTable::tableDownloadFinished);
}

/*!
 * \brief MyTable::tableDownloadFinished assembles the information to be displayed about the targets cryptocurrencies and then displays it on screen.
 *
 * This slot is called when QtNetwork is done with downloading the exchange rate information of the target cryptocurrencies vs. Euro, Dollar and the British
 * Pound from Coingecko. Using that data along with the naming information in \variable cryptoMap, a list of \class CryptoInfo objects are created. The
 * \class MyModel is initialied using that info and the MyTable GUI is made visible immediately afterwards.
 */

void MyTable::tableDownloadFinished()
{
    std::cout << "table!" << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes.data());
    QJsonObject obj = doc.object();
    QVector<CryptoInfo> infos;
    for(QString &key : obj.keys()){
        infos.push_back(CryptoInfo(cryptoMap[key], obj.value(key).toObject()));
    }
    myModel = new MyModel(infos);
    setModel(myModel);
    resizeColumnsToContents();
    show();
}

