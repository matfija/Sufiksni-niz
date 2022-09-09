// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za numeričke algoritme
#include <numeric>

// Biblioteka za poznate algoritme
#include <algorithm>

// Biblioteka za rad sa vremenom
#include <chrono>

// Pamćenje prosleđene niske
NaiveSort::NaiveSort(const char *const s, size_t k)
    : SuffixArray(s) {
    // Ponavljanje algoritma po želji
    for (size_t i = 0; i < k; i++) {
        // Merenje vremena na početku rada algoritma
        const auto start = std::chrono::high_resolution_clock::now();

        // Izvršavanje algoritma
        napraviSufiksniNiz();

        // Merenje vremena na kraju rada algoritma
        const auto end = std::chrono::high_resolution_clock::now();

        // Dodavanje rezultata na u vektor vremena
        vreme.push_back(static_cast<size_t>((end - start).count()));
    }

    // Određivanje statistika vremena
    statistike();
}

// Pravljenje sufiksnog niza naivnim sortiranjem
void NaiveSort::napraviSufiksniNiz() {
    // Popunjavanje sufiksnog niza indeksima
    std::iota(niz, niz + n, size_t());

    // Sortiranje indeksa prema sufiksima
    std::sort(niz, niz + n, [this](size_t i, size_t j) {
        return strcmp(niska + i, niska + j) < 0;
    });
}
