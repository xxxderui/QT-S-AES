QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack.cpp \
    choice.cpp \
    figure.cpp \
    figure_2.cpp \
    figure_3.cpp \
    figure_4.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    attack.h \
    choice.h \
    figure.h \
    figure_2.h \
    figure_3.h \
    figure_4.h \
    mainwindow.h

FORMS += \
    attack.ui \
    choice.ui \
    figure.ui \
    figure_2.ui \
    figure_3.ui \
    figure_4.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
