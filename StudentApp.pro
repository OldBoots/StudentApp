QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    closedialog.cpp \
    createdialog.cpp \
    main.cpp \
    dialog.cpp \
    trainingformdialog.cpp

HEADERS += \
    closedialog.h \
    createdialog.h \
    dialog.h \
    trainingformdialog.h

FORMS += \
    closedialog.ui \
    createdialog.ui \
    dialog.ui \
    trainingformdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    html.html

RESOURCES += \
    src.qrc
