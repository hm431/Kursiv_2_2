#include "checkboxdelegate.h"

#include <QCheckBox>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>


CheckBoxDelegate::CheckBoxDelegate(QWidget *parent):
    QStyledItemDelegate(parent)
{

}


QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{

    Q_UNUSED(option);
    Q_UNUSED(index);


    QCheckBox *editor = new QCheckBox(parent);

    return editor;
}


void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    bool value = index.model()->data(index, Qt::DisplayRole).toBool();

    QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);

    checkBox->setChecked(value);
}


void CheckBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{

    model->setData(index,
                   qobject_cast<QCheckBox *>(editor)->isChecked());
}


void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);

    QStyleOptionButton newEditorOption;


    QRect rectIndicator =
            QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                  &newEditorOption);


    newEditorOption.rect = option.rect;


    int cellWidth = option.rect.width();


    int cellCenter = cellWidth / 2;


    int CheckIndicatorWidth = rectIndicator.width();


    int centerOfCheckIndicator = CheckIndicatorWidth / 2;


    int cellX  = option.rect.x();


    int cellCenterInTable = cellX + cellCenter;


    int beginIndicator = cellCenterInTable - centerOfCheckIndicator;


    newEditorOption.rect.setLeft(beginIndicator);


    editor->setGeometry(newEditorOption.rect);
}


void CheckBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{

    QStyleOptionButton newEditorOption;
    QRect rectIndicator =
            QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                  &newEditorOption);
    newEditorOption.rect = option.rect;
    newEditorOption.rect.setLeft(option.rect.x() +
                                 option.rect.width()/2 -
                                 rectIndicator.width()/2);


    if (index.data().toBool())

        newEditorOption.state |= QStyle::State_On;


    else

        newEditorOption.state |= QStyle::State_Off;



    if (option.state & QStyle::State_Selected)

        painter->fillRect(option.rect, option.palette.highlight());


    QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                       &newEditorOption,
                                       painter);
}


bool CheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    Q_UNUSED(option);

    if (event->type() == QEvent::MouseButtonRelease)
    {

        if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton)

            model->setData(index, !index.data().toBool());


        return true;
    }


    return false;
}
