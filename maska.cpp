#include "maska.h"

maska::maska(QObject *perent) : QStyledItemDelegate(perent)
{

}

QWidget *maska::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column()==2)
    {
        QLineEdit * lineEdit = new QLineEdit(parent);
        lineEdit->setInputMask("c_00:00_до_00:00");
        return lineEdit;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);


}


