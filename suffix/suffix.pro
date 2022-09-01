CONFIG += c++2a

INCLUDEPATH += header

HEADERS += \
        header/SuffixArray.hpp \
        header/NaiveSort.hpp \
        header/PrefixDoubling.hpp

SOURCES += \
        main.cpp \
        source/SuffixArray.cpp \
        source/NaiveSort.cpp \
        source/PrefixDoubling.cpp
