TEMPLATE = app

CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

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
