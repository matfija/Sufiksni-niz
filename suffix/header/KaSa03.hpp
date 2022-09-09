#ifndef KASA03_H
#define KASA03_H

// Biblioteka za sufiksni niz
#include "SuffixArray.hpp"

// Kerkejnen-Sandersov DC3 algoritam
class KaSa03 : public SuffixArray {
public:
    // Konstruktor niza na osnovu niske
    KaSa03(const char *const, size_t = 1);

private:
    // Virtuelna funkcija za konstrukciju niza
    virtual void napraviSufiksniNiz() final;
};

#endif // KASA03_H
