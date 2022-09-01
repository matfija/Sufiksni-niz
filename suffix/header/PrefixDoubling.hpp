#ifndef PREFIXDOUBLING_H
#define PREFIXDOUBLING_H

// Biblioteka za sufiksni niz
#include "SuffixArray.hpp"

// Sufiksni niz dupliranjem prefiksa
class PrefixDoubling : public SuffixArray {
public:
    // Konstruktor niza na osnovu niske
    PrefixDoubling(const char *const);

    // Virtuelna funkcija za konstrukciju niza
    virtual void napraviSufiksniNiz() final;
};

#endif // PREFIXDOUBLING_H
