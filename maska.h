#ifndef MASKA_H
#define MASKA_H

#include <QStyledItemDelegate>
#include <QRegularExpression>
#include <QLineEdit>

class maska : public QStyledItemDelegate
{
    /**
 * @brief Класс Макси
 *
 *  Описывает работу маски, которая используется в 3-ем столбце
 */
public:
    explicit maska(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MASKA_H
