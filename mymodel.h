#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>
#include "cryptonames.h"

/*!
 * \brief The MyModel class defines the way cryptocurrency exchange rate data will be displayed on screen. It further contains the names of the headers.
 */
class MyModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    const QString CURRENCY_TYPES[4]{"", "USD", "EUR", "GBP"};
    QVector<std::array<QString, 4>> tableData;
public:
    MyModel(const QVector<CryptoInfo> currencies, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif
