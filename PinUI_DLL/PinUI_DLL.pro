QT +=gui
QT +=widgets
Qt +=core

TEMPLATE = lib
DEFINES += PINUI_DLL_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    pinui_dll.cpp

HEADERS += \
    PinUI_DLL_global.h \
    dialog.h \
    pinui_dll.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dialog.ui
