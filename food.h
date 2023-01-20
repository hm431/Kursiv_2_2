#ifndef FOOD_H
#define FOOD_H

#include <QString>

class Food
{
/**
 * @brief Еда
 *
 * Данный класс описывает работу с данными, которые были получены из файла
 */
public:
    Food();
    ~Food();
    Food(const QString FName,
         const QString FTipe,
         const QString FTime,
         const QString FSite,
         const QString FDelivery,
         const QString FParking,
         const QString FGrup,
         const float FMark);






    const QString &getFOName() const;
    void setFOName(const QString &newFOName);
    const QString &getFOTipe() const;
    void setFOTipe(const QString &newFOTipe);
    const QString &getFOTime() const;
    void setFOTime(const QString &newFOTime);
    const QString &getFOSite() const;
    void setFOSite(const QString &newFOSite);
    const QString &getFODelivery() const;
    void setFODelivery(const QString &newFODelivery);
    const QString &getFOParking() const;
    void setFOParking(const QString &newFOParking);
    const QString &getFOGrup() const;
    void setFOGrup(const QString &newFOGrup);
    float getFOMark() const;
    void setFOMark(float newFOMark);

private:
             QString FOName;
             QString FOTipe;
             QString FOTime;
             QString FOSite;
             QString FODelivery;
             QString FOParking;
             QString FOGrup;
             float FOMark;
};

#endif // FOOD_H
