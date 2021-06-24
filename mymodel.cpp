#include "mymodel.h"

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
