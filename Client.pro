TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    tcp_client.cpp

HEADERS += \
    tcp_client.h

QMAKE_CXXFLAGS += -std=c++0x -O0 -Wall -Wextra
LIBS += -lpthread
LIBS += -lwsock32
LIBS += -lws2_32
#LIBS += wsock32.lib
