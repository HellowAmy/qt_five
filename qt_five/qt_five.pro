QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chess_ai.cpp \
    chess_board.cpp \
    chess_five.cpp \
    chess_hand.cpp \
    chess_net.cpp \
    chess_play.cpp \
    chess_rules.cpp \
    chess_view.cpp \
    chess_wid.cpp \
    line_edit.cpp \
    main.cpp \
    push_button.cpp \
    tcp_conncet_string.cpp \
    widget.cpp

HEADERS += \
    chess_ai.h \
    chess_board.h \
    chess_five.h \
    chess_hand.h \
    chess_net.h \
    chess_play.h \
    chess_rules.h \
    chess_view.h \
    chess_wid.h \
    line_edit.h \
    push_button.h \
    tcp_conncet_string.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    map.qrc
