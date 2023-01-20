#include "food.h"

Food::Food():
    FOName(""),
    FOTipe(""),
    FOTime(""),
    FOSite(""),
    FODelivery(""),
    FOParking(""),
    FOGrup(""),
    FOMark(0)
{

}

Food::~Food()
{

}

Food::Food(const QString FName,
           const QString FTipe,
           const QString FTime,
           const QString FSite,
           const QString FDelivery,
           const QString FParking,
           const QString FGrup,
           const float FMark):
    FOName(FName),
    FOTipe(FTipe),
    FOTime(FTime),
    FOSite(FSite),
    FODelivery(FParking),
    FOParking(FDelivery),
    FOGrup(FGrup),
    FOMark(FMark)


{

}

const QString &Food::getFOName() const
{
    return FOName;
}

void Food::setFOName(const QString &newFOName)
{
    FOName = newFOName;
}

const QString &Food::getFOTipe() const
{
    return FOTipe;
}

void Food::setFOTipe(const QString &newFOTipe)
{
    FOTipe = newFOTipe;
}

const QString &Food::getFOTime() const
{
    return FOTime;
}

void Food::setFOTime(const QString &newFOTime)
{
    FOTime = newFOTime;
}

const QString &Food::getFOSite() const
{
    return FOSite;
}

void Food::setFOSite(const QString &newFOSite)
{
    FOSite = newFOSite;
}

const QString &Food::getFODelivery() const
{
    return FODelivery;
}

void Food::setFODelivery(const QString &newFODelivery)
{
    FODelivery = newFODelivery;
}

const QString &Food::getFOParking() const
{
    return FOParking;
}

void Food::setFOParking(const QString &newFOParking)
{
    FOParking = newFOParking;
}

const QString &Food::getFOGrup() const
{
    return FOGrup;
}

void Food::setFOGrup(const QString &newFOGrup)
{
    FOGrup = newFOGrup;
}

float Food::getFOMark() const
{
    return FOMark;
}

void Food::setFOMark(float newFOMark)
{
    FOMark = newFOMark;
}

