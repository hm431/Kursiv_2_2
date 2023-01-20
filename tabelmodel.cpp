#include "tabelmodel.h"

#include <QDebug>
#include <QBrush>




TabelModel::TabelModel(QObject *parent):
    QAbstractTableModel(parent),
    NumberOfColumns(8)
{

}

int TabelModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return VentList.count();
}

int TabelModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return NumberOfColumns;
}


QVariant TabelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        const Food &VentD = VentList[index.row()];

        switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (index.column() == 0)
                return VentD.getFOName();
            if (index.column() == 1)
                return VentD.getFOTipe();
            if (index.column() == 2)
                return VentD.getFOTime();
            if (index.column() == 3)
                return VentD.getFOSite();
            if (index.column() == 4)
                return VentD.getFODelivery();
            if (index.column() == 5)
                return VentD.getFOParking();
            if (index.column() == 6)
                return VentD.getFOGrup();
            if (index.column() == 7)
                return VentD.getFOMark();
            break;
        default:
            return QVariant();
        }
        return QVariant();
}

QVariant TabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Tipe");
            case 2:
                return tr("Time");
            case 3:
                return tr("Site");
            case 4:
                return tr("Delivery");
            case 5:
                return tr("Parking");
            case 6:
                return tr("Grup");
            case 7:
                return tr("Mark");

            }
        }
    return QVariant();
}

Qt::ItemFlags TabelModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable| Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled;
        else
            return Qt::NoItemFlags;
}

bool TabelModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int row = 0; row < count; ++row) {
        VentList.insert(row, Food());
    }

    endInsertRows();
    return true;
}

void TabelModel::insertValue(const Food &value)
{
    VentList.append(value);
    emit layoutChanged();
}

QMimeData *TabelModel::mimeData(const QModelIndexList &indexes) const
{
    if(indexes.isEmpty())
        return nullptr;
    if(!indexes.at(0).isValid())
        return nullptr;

    if (firstMimeType == "text/plain" && secondMimeType == "application/x-qabstractitemmodeldatalist")
    {
        QString result;

        int topSelectionRange = indexes.at(0).row();
        int leftSelectionRange = indexes.at(0).column();
        int rowCountSelectionRange = 0;
        int columnCountSelectionRange = 0;
        for (int i = 0; i < indexes.count(); ++i) {
            // item отсутствует?
            if (!indexes.at(i).isValid())
                return nullptr;

            int c = indexes.at(i).column() - leftSelectionRange;
            int r = indexes.at(i).row() - topSelectionRange;

            if (c > 0 && (c < columnCountSelectionRange || indexes.at(i).row() == topSelectionRange))
                result += columnDelimiter;
            if (r > 0 && indexes.at(i).column() == leftSelectionRange)
                result += rowDelimiter;
            result += quotes +
                    indexes.at(i).data(Qt::DisplayRole).toString() +
                    quotes;

            if (indexes.at(i).row() == topSelectionRange)
                columnCountSelectionRange++;
            if (indexes.at(i).column() == leftSelectionRange)
                rowCountSelectionRange++;
        }

        result += rowDelimiter;

        // создаем mimeData, которая будет использоваться для drop
        QMimeData *mimeData = new QMimeData;
        // создаем mimeDataForLocal для записи типа и mimeData для внутренних переносов
        QMimeData *mimeDataForLocal = QAbstractTableModel::mimeData(indexes);
        // записываем типы с данными для drop в mimeData
        mimeData->setData(secondMimeType, mimeDataForLocal->data(secondMimeType));
        mimeData->setData(firstMimeType, result.toUtf8());
        return mimeData;
    }

    return nullptr;
}

bool TabelModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(data == nullptr)
        return false;



    QByteArray dataforsecond = data->data(secondMimeType);
    QMimeData *forsecond = new  QMimeData;
    forsecond->setData(secondMimeType, dataforsecond);
//    forsecond->setText(dataforsecond);

    if(data->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        return QAbstractTableModel::dropMimeData(forsecond, action, row, column, parent);
    }

    if (data->hasFormat("text/plain"))
    {
        QStringList strings;
        strings = data->text().split(rowDelimiter);

        for (int rowSelected = 0; rowSelected < strings.count(); ++rowSelected)
        {
            if ((row + rowSelected) >= rowCount(parent))
                insertRow(rowCount(parent));
            QStringList tokens = strings[rowSelected].split(columnDelimiter);
            for (int columnSelected = 0; columnSelected < tokens.count(); columnSelected++)
            {
                QString token = tokens[columnSelected];
                token.remove(quotes);
                if (token.isEmpty())
                    continue;
                QAbstractItemModel *item = new TabelModel;
                item->setData(parent, token, Qt::EditRole);
                QMap<int, QVariant> k;
                setItemData(item->data(parent, Qt::DisplayRole).toModelIndex(), k);
                delete item;
            }
        }
        return true;
}

}
bool TabelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::EditRole || role == Qt::DisplayRole) {
        auto data = VentList.at(index.row());

        switch (index.column()) {
        case 0:
        {
            data.setFOName(value.toString());
            break;
        }
        case 1:
        {
            data.setFOTipe(value.toString());
            break;
        }
        case 2:
        {
            data.setFOTime(value.toString());
            break;
        }
        case 3:
        {
            data.setFOSite(value.toString());
            break;
        }
        case 4:
        {
            data.setFODelivery(value.toString());
            break;
        }
        case 5:
        {
            data.setFOParking(value.toString());
            break;
        }
        case 6:
        {
            data.setFOGrup(value.toString());
            break;
        }
        case 7:
        {
            data.setFOMark(value.toFloat());
            break;
        }
        }
        VentList.replace(index.row(), data);
        return true;
    }

    return false;
}
bool TabelModel::removeRows(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
        beginRemoveRows(QModelIndex(), row-1, row-1);

        VentList.removeAt(row-1);

        endRemoveRows();
        return true;
}
