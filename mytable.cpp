#include "mytable.h"

MyTable::MyTable()
{
    QUrl url("https://142.250.187.110");
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MyTable::downloadFinished);
    connect(&qnam, &QNetworkAccessManager::sslErrors, this, &MyTable::sslError);
}

void MyTable::downloadFinished(){
    std::cout << "downloaded!" << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);

    MyModel myModel(doc.object());
    setModel(&myModel);
    resizeColumnsToContents();
}

void MyTable::sslError(){
    std::cout << "errored!\n" <<reply->errorString().toStdString() << std::endl;
    reply->dumpObjectInfo();
    reply->dumpObjectTree();
}
