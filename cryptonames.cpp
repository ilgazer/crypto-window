#include "cryptonames.h"


/*!
 * \brief CryptoNames::CryptoNames creates a CryptoNames object by parsing the name information from Coingecko
 * \param info
 */
CryptoNames::CryptoNames(QJsonObject info):
    name(info.value("name").toString()),
    id(info.value("id").toString()),
    symbol(info.value("symbol").toString()){}

/*!
 * \brief CryptoInfo::CryptoInfo default constructor that returns a dummy object.
 */
CryptoNames::CryptoNames(){}

/*!
 * \brief CryptoInfo::CryptoInfo creates a CryptoInfo object by combining the name information from \class CryptoNames and the exchange rate information from Coingecko
 */
CryptoInfo::CryptoInfo(CryptoNames names, QJsonObject rates):
    CryptoNames(names),
    gbp(rates.value("gbp").toDouble()),
    usd(rates.value("usd").toDouble()),
    eur(rates.value("eur").toDouble()){}

/*!
 * \brief CryptoInfo::CryptoInfo default constructor that returns a dummy object.
 */
CryptoInfo::CryptoInfo(): gbp(-1), usd(-1),eur(-1){}

