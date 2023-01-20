#ifndef TABELMODEL_H
#define TABELMODEL_H




#include "food.h"
#include <QMimeData>
#include <QAbstractTableModel>
#include <QList>

class TabelModel : public QAbstractTableModel
{
    Q_OBJECT
    QList<Food> VentList;
    const int NumberOfColumns;
/**
  * @brief TabelModel Класс интерфейса для работы с данными в программе
  *
  * Класс описывает интерфейс
*/

public:
    explicit TabelModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, const QModelIndex &parent);
    void insertValue(const Food &value);

    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
     bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QString firstMimeType = "text/plain";
    QString secondMimeType = "application/x-qabstractitemmodeldatalist";
    QString quotes = "\"";
    QString columnDelimiter = ";";
    QString rowDelimiter = "\n";
};


#endif // TABELMODEL_H
