// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Biblioteka za numeričke algoritme
#include <numeric>

// Biblioteka za poznate algoritme
#include <algorithm>

// Pamćenje prosleđene niske
PrefixDoubling::PrefixDoubling(const char *const s)
    : SuffixArray(s) { napraviSufiksniNiz(); }

// Pravljenje sufiksnog niza dupliranjem prefiksa
void PrefixDoubling::napraviSufiksniNiz() {
    // Popunjavanje sufiksnog niza indeksima
    std::iota(niz, niz + n, size_t());

    // Obrtanje niza zarad kasnije stabilnost
    std::reverse(niz, niz + n);

    // Stabilno sortiranje indeksa po prvom karakteru
    std::stable_sort(niz, niz + n, [this](size_t i, size_t j) {
        return niska[i] < niska[j];
    });

    // Klase ekvivalencije (rangovi) sufiksa
    const auto rangovi = new size_t[n];
    std::copy_n(niska, n, rangovi);

    // Prolazak kroz sve duplikacije prefiksa
    for (size_t k = 1; k < n; k *= 2) {
        // Klase sufiksa duzine do 2k
        const auto klase = new size_t[n];
        std::copy_n(rangovi, n, klase);

        // Određivanje novih klasa na osnovu prethodnih
        for (size_t i = 0; i < n; i++) {
            rangovi[niz[i]] = i > 0 && klase[niz[i - 1]] == klase[niz[i]] && niz[i - 1] + k < n &&
                              klase[niz[i - 1] + k/2] == klase[niz[i] + k/2] ? rangovi[niz[i - 1]] : i;
        }

        // Inicijalizacija brojača za drugi deo sortiranja
        const auto broj = new size_t[n];
        std::iota(broj, broj + n, size_t());

        // Kopiranje tekućeg stanja niza za drugi deo sortiranja
        const auto kopija = new size_t[n];
        std::copy_n(niz, n, kopija);

        // Pronalaženje neuređenih sufiksa veće dužine
        for (size_t i = 0; i < n; i++) {
            if (kopija[i] >= k) {
                const auto suff = static_cast<size_t>(
                    static_cast<int>(kopija[i]) - static_cast<int>(k)
                );

                // Razvrstavanje otkrivenih sufiksa
                niz[broj[rangovi[suff]]++] = suff;
           }
        }

        // Oslobađanje memorije
        delete[] klase;
        delete[] broj;
        delete[] kopija;
    }

    // Oslobađanje memorije
    delete[] rangovi;
}
