QT += testlib

CONFIG += c++2a

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
