#include "mymodel.h"

/*!
 * \brief MyModel::MyModel populates the table fields using the data in the list of \class CryptoInfo objects
 * \param currencies is the list of \class CryptoInfo objects that correspond to the target cryptocurrencies
 * \param parent
 */
MyModel::MyModel(const QVector<CryptoInfo> tableData, QObject *parent):QAbstractTableModel(parent), tableData(tableData){}

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
    if (role == Qt::DisplayRole){
        CryptoInfo currency= tableData[index.row()];
        switch(index.column()){
        case 0:
            return currency.name;
        case 1:
            return QString::number(currency.usd);
        case 2:
            return QString::number(currency.eur);
        case 3:
            return QString::number(currency.gbp);
        }
    }
    return QVariant();
}
