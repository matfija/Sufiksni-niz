// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za numeričke algoritme
#include <numeric>

// Biblioteka za poznate algoritme
#include <algorithm>

// Pamćenje prosleđene niske
NaiveSort::NaiveSort(const char *const s)
    : SuffixArray(s) { napraviSufiksniNiz(); }

// Pravljenje sufiksnog niza naivnim sortiranjem
void NaiveSort::napraviSufiksniNiz() {
    // Popunjavanje sufiksnog niza indeksima
    std::iota(niz, niz+n, size_t());

    // Sortiranje indeksa prema sufiksima
    std::sort(niz, niz+n, [this](size_t i, size_t j) {
        return strcmp(niska+i, niska+j) < 0;
    });
}
