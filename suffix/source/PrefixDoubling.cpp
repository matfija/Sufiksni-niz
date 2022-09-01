// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Biblioteka za numeričke algoritme
#include <numeric>

// Biblioteka za poznate algoritme
#include <algorithm>

// Pamćenje prosleđene niske
PrefixDoubling::PrefixDoubling(const char *const s)
    : SuffixArray(s) { }

// Pravljenje sufiksnog niza dupliranjem prefiksa
void PrefixDoubling::napraviSufiksniNiz() {
    // Popunjavanje sufiksnog niza indeksima
    std::iota(niz, niz+n, size_t());

    // Obrtanje niza zarad kasnije stabilnost
    std::reverse(niz, niz+n);

    // Stabilno sortiranje indeksa po prvom karakteru
    std::stable_sort(niz, niz+n, [this](size_t i, size_t j) {
        return niska[i] < niska[j];
    });

    // Klase ekvivalencije (rangovi) sufiksa
    std::vector<size_t> rangovi(n);

    // Za početak se karakteri mogu shvatiti kao rangovi
    std::copy_n(niska, n, std::begin(rangovi));

    // Prolazak kroz sve duplikacije prefiksa
    for (size_t k = 1; k < n; k *= 2) {
        // Klase sufiksa duzine do 2k
        std::vector<size_t> klase = rangovi;

        // Određivanje novih klasa na osnovu prethodnih
        for (size_t i = 0; i < n; i++) {
            rangovi[niz[i]] = i > 0 && klase[niz[i-1]] == klase[niz[i]] && niz[i - 1] + k < n &&
                              klase[niz[i-1] + k/2] == klase[niz[i] + k/2] ? rangovi[niz[i-1]] : i;
        }

        // Inicijalizacija brojača za drugi deo sortiranja
        std::vector<size_t> brojač(n);
        std::iota(std::begin(brojač), std::end(brojač), size_t());

        // Kopiranje tekućeg stanja niza za drugi deo sortiranja
        std::vector<size_t> kopija(n);
        std::copy_n(niz, n, std::begin(kopija));

        // Pronalaženje neuređenih sufiksa veće dužine
        for (size_t i = 0; i < n; i++) {
            if (kopija[i] >= k) {
                const auto s2 = static_cast<size_t>(
                    static_cast<int>(kopija[i]) - static_cast<int>(k)
                );

                // Soritanje otkrivenih sufiksa
                niz[brojač[rangovi[s2]]++] = s2;
           }
       }
    }
}
