#include "mytable.h"
#include<iostream>
#include<fstream>

QUrl MyTable::get_url()
{
    char envVar[16] = "MYCRYPTOCONVERT";
    QString input_file_name(qgetenv(envVar));

    std::ifstream in;
    in.open(input_file_name.toStdString());
    std::string s;
    QString urlNameBegin("https://api.coingecko.com/api/v3/simple/price?ids=");
    QString coinList("");
    while(in>>s)
    {
        s += ",";
        coinList.append(s.c_str());
    }
    in.close();
    QString urlNameEnd("&vs_currencies=usd,eur,gbp");
    QString urlName = urlNameBegin + coinList + urlNameEnd;
    //"https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,litecoin&vs_currencies=usd,eur,gbp"
    qDebug() << "constructed url: "<<urlName <<"\n";
    return QUrl("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,litecoin&vs_currencies=usd,eur,gbp");

}

MyTable::MyTable()
{   
    QUrl url(get_url());
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyTable::downloadFinished);
  //  connect(&qnam, &QNetworkAccessManager::sslErrors, this, &MyTable::sslError);
}

void MyTable::downloadFinished(){
    std::cout << "downloaded!" << std::endl;
    QByteArray bytes = reply->readAll();
    qDebug() << bytes.data();
    QJsonDocument doc = QJsonDocument::fromJson(bytes.data());
    QJsonObject obj = doc.object();
    myModel = new MyModel(obj);
    setModel(myModel);
    resizeColumnsToContents();
    show();
}
