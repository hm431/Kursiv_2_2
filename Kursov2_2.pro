QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    checkboxdelegate.cpp \
    food.cpp \
    main.cpp \
    mainwindow.cpp \
    maska.cpp \
    mproxy.cpp \
    tabelmodel.cpp

HEADERS += \
    about.h \
    checkboxdelegate.h \
    food.h \
    mainwindow.h \
    maska.h \
    mproxy.h \
    tabelmodel.h

FORMS += \
    about.ui \
    mainwindow.ui

TRANSLATIONS += tr/Kursov2_2_ru_RU.ts \
                    tr/Kursov2_2_en_US.ts \
                        tr/Kursov2_2_de_DE.ts



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
