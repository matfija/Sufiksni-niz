#ifndef SAIS09_H
#define SAIS09_H

// Biblioteka za sufiksni niz
#include "SuffixArray.hpp"

// Algoritam SA-IS konstrukcije niza
class SAIS09 : public SuffixArray {
public:
    // Konstruktor niza na osnovu niske
    SAIS09(const char *const);

    // Virtuelna funkcija za konstrukciju niza
    virtual void napraviSufiksniNiz() final;
};

#endif // SAIS09_H
