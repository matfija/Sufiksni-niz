#ifndef NAIVESORT_H
#define NAIVESORT_H

// Biblioteka za sufiksni niz
#include "SuffixArray.hpp"

// Sufiksni niz naivnim sortiranjem
class NaiveSort : public SuffixArray {
public:
    // Konstruktor niza na osnovu niske
    NaiveSort(const char *const);

    // Virtuelna funkcija za konstrukciju niza
    virtual void napraviSufiksniNiz() final;
};

#endif // NAIVESORT_H
