TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -g -Wall --coverage -O0
LIBS += -lgcov
QT += testlib

INCLUDEPATH += ../suffix/header

HEADERS += \
        ../suffix/header/SuffixArray.hpp \
        ../suffix/header/NaiveSort.hpp \
        ../suffix/header/PrefixDoubling.hpp

SOURCES += \
        main.cpp \
        ../suffix/source/SuffixArray.cpp \
        ../suffix/source/NaiveSort.cpp \
        ../suffix/source/PrefixDoubling.cpp
