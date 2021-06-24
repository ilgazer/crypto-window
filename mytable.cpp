#include "mytable.h"
#include<iostream>
#include<fstream>

MyTable::MyTable(QSet<QString> nameSet): nameSet(nameSet)
{   
    setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
    QUrl url("https://api.coingecko.com/api/v3/coins/list");
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyTable::symbolsDownloadFinished);
}

void MyTable::symbolsDownloadFinished()
{
    std::cout << "symbols!" << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes.data());
    QJsonArray arr = doc.array();

    QString url("https://api.coingecko.com/api/v3/simple/price?vs_currencies=usd,eur,gbp&ids=");

    for(const QJsonValueRef &value: arr){
        CryptoNames obj(value.toObject());
        if(nameSet.contains(obj.symbol) || nameSet.contains(obj.name) || nameSet.contains(obj.id)){
            cryptoMap.insert(obj.id, obj);
            url.append(obj.id);
            url.append(",");
        }
    }
    reply = qnam.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, &MyTable::tableDownloadFinished);
}

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

