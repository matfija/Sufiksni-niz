TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += header

HEADERS += \
        header/SuffixArray.hpp

SOURCES += \
        main.cpp \
        source/SuffixArray.cpp
