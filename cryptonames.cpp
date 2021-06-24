#include "cryptonames.h"

CryptoNames::CryptoNames(QJsonObject info):
    name(info.value("name").toString()),
    id(info.value("id").toString()),
    symbol(info.value("symbol").toString()){}

CryptoNames::CryptoNames(){}
CryptoInfo::CryptoInfo(CryptoNames names, QJsonObject rates):
    CryptoNames(names),
    gbp(rates.value("gbp").toDouble()),
    usd(rates.value("usd").toDouble()),
    eur(rates.value("eur").toDouble()){}

CryptoInfo::CryptoInfo(): gbp(-1), usd(-1),eur(-1){}

