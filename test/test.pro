QT += testlib

CONFIG += c++2a

INCLUDEPATH += ../suffix/header

HEADERS += \
        ../suffix/header/SuffixArray.hpp \
        ../suffix/header/NaiveSort.hpp \
        ../suffix/header/PrefixDoubling.hpp \
        ../suffix/header/KaSa03.hpp \
        ../suffix/header/SAIS09.hpp

SOURCES += \
        main.cpp \
        ../suffix/source/SuffixArray.cpp \
        ../suffix/source/NaiveSort.cpp \
        ../suffix/source/PrefixDoubling.cpp \
        ../suffix/source/KaSa03.cpp \
        ../suffix/source/SAIS09.cpp
