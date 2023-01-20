#ifndef MPROXY_H
#define MPROXY_H

#include <QSortFilterProxyModel>

class MProxy : public QSortFilterProxyModel
{
    /**
      * @brief Вспомогательный класс
      *
      *
    */
    Q_OBJECT
public:



    MProxy(QObject* perent = nullptr);
};

#endif // MPROXY_H
