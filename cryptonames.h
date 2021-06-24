#ifndef CRYPTONAMES_H
#define CRYPTONAMES_H

#include <QJsonObject>
#include <QString>



class CryptoNames
{
public:
    CryptoNames(QJsonObject jsonCryptoName);
    //CryptoNames(CryptoNames &copy);
    CryptoNames();
    QString name;
    QString id;
    QString symbol;
};

class CryptoInfo : public CryptoNames
{
public:
    double gbp;
    double usd;
    double eur;
    CryptoInfo(CryptoNames names, QJsonObject rates);
    CryptoInfo();
};

#endif // CRYPTONAMES_H
