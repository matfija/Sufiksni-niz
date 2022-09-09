// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Biblioteka za numeričke algoritme
#include <numeric>

// Biblioteka za poznate algoritme
#include <algorithm>

// Biblioteka za rad sa vremenom
#include <chrono>

// Pamćenje prosleđene niske
PrefixDoubling::PrefixDoubling(const char *const s, size_t k)
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
    for (size_t k = 1; k < n; k <<= 1) {
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
