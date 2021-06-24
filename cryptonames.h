#ifndef CRYPTONAMES_H
#define CRYPTONAMES_H

#include <QJsonObject>
#include <QString>


/*!
 * \brief The CryptoNames class is a passive data structure that contains the name, id and symbol of a cryptocurrency
 */
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

/*!
 * \brief The CryptoInfo class is a passive data structure that contains the naming information of a cryptocurrency along with its exchange rates with GBP, EUR and USD
 */
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
