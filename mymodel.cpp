#include "mymodel.h"

/*!
 * \brief MyModel::MyModel populates the table fields using the data in the list of \class CryptoInfo objects
 * \param currencies is the list of \class CryptoInfo objects that correspond to the target cryptocurrencies
 * \param parent
 */
MyModel::MyModel(QVector<CryptoInfo> currencies, QObject *parent)
    : QAbstractTableModel(parent)
{
    for(CryptoInfo &currency:currencies){
        tableData.push_back(std::array<QString, 4>{
                                currency.name,
                                QString::number(currency.usd),
                                QString::number(currency.eur),
                                QString::number(currency.gbp)
                            });
    }
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return tableData.size();
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

/*!
 * \brief MyModel::headerData defines the headers of the table. The first header is empty, and the next headers are "USD", "EUR" and "GBP".
 */
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return CURRENCY_TYPES[section];
    }
    return QVariant();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
       return tableData[index.row()][index.column()];
    return QVariant();
}
