// Biblioteka za algoritam SA-IS
#include "SAIS09.hpp"

// Pamćenje prosleđene niske
SAIS09::SAIS09(const char *const s)
    : SuffixArray(s) { napraviSufiksniNiz(); }

// Rekurzivno određivanje sufiksnog niza
// SA niske T dužine n nad azbukom reda K
static void SAIS(size_t *s, size_t *SA, size_t n, size_t K) { }

// Pravljenje sufiksnog niza algoritmom SA-IS
void SAIS09::napraviSufiksniNiz() {
    // Prazna niska kao specijalni slučaj
    if (!n) return;

    // Niska dužine jedan kao specijalni slučaj
    if (n == 1) {
        *niz = 0;
        return;
    }

    // Svođenje niske na niz brojeva
    const auto T = new size_t[n];
    std::copy_n(niska, n, T);

    // Pomoćni sufiksni niz sa dodatnim mestom
    const auto SA = new size_t[n + 1];

    // Rekurzivno određivanje sufiksnog niza; razvrstavanje
    // karaktera na 128 mesta odgovara ASCII enkodiranju
    SAIS(T, SA, n + 1, 128);

    // Olobađanje memorije
    delete[] T;

    // Prepisivanje sufiksnog niza
    std::copy_n(SA + 1, n, niz);

    // Olobađanje memorije
    delete[] SA;
}
