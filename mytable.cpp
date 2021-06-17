#include "mytable.h"
#include<iostream>
#include<fstream>

QUrl MyTable::getUrl()
{
    QString input_file_name(qgetenv("MYCRYPTOCONVERT"));

    std::ifstream in;
    in.open(input_file_name.toStdString());
    std::string s;
    QString urlNameBegin("https://api.coingecko.com/api/v3/simple/price?vs_currencies=usd,eur,gbp&ids=");

}

MyTable::MyTable(QSet<QString> nameSet): nameSet(nameSet)
{   
    QUrl url("https://api.coingecko.com/api/v3/coins/list");
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyTable::symbolsDownloadFinished);
  //  connect(&qnam, &QNetworkAccessManager::sslErrors, this, &MyTable::sslError);
}

void MyTable::symbolsDownloadFinished()
{
    std::cout << "symbols!" << std::endl;
    QByteArray bytes = reply->readAll();
    qDebug() << bytes.data();
    QJsonDocument doc = QJsonDocument::fromJson(bytes.data());
    QJsonArray arr = doc.array();

    QString url("https://api.coingecko.com/api/v3/simple/price?vs_currencies=usd,eur,gbp&ids=");

    for(const QJsonValueRef &value: arr){
        QJsonObject obj = value.toObject();
        if(nameSet.contains(obj.value("symbol").toString()) || nameSet.contains(obj.value("name").toString())){
            url.append(obj.value("id").toString());
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
    qDebug() << bytes.data();
    QJsonDocument doc = QJsonDocument::fromJson(bytes.data());
    QJsonObject obj = doc.object();
    myModel = new MyModel(obj);
    setModel(myModel);
    resizeColumnsToContents();
    show();
}
