#include "mymodel.h"

MyModel::MyModel(QJsonObject jsonObject, QObject *parent)
    : QAbstractTableModel(parent)
{
    for(QString &key:jsonObject.keys()){
        QJsonObject obj = jsonObject.value(key).toObject();
        QJsonValue usd = obj.value("usd");
        tableData.push_back(std::array<QString, 4>{
                                key,
                                QString::number(obj.value("usd").toDouble()),
                                QString::number(obj.value("eur").toDouble()),
                                QString::number(obj.value("gbp").toDouble())});
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
