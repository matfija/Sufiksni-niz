// Biblioteka za Kerkejnen-Sandersa
#include "KaSa03.hpp"

// Pamćenje prosleđene niske
KaSa03::KaSa03(const char *const s)
    : SuffixArray(s) { napraviSufiksniNiz(); }

// Leksikografsko uređenje parova
#define ur2(a1, a2, b1, b2) \
    ((a1) < (b1) || ((a1) == (b1) && (a2) <= (b2)))

// Leksikografsko uređenje trojki
#define ur3(a1, a2, a3, b1, b2, b3) \
    ((a1) < (b1) || ((a1) == (b1) && ur2((a2), (a3), (b2), (b3))))

// Dohvatanje indeksa u koraku spajanja
#define indeks() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)

// Sortiranje razvrstavanjem a[0..n-1]
// u b[0..n-1] prema kofi r reda K
static inline void razvrstavanje(size_t *a, size_t *b, size_t *r, size_t n, size_t K) {
    // Brojački niz za potrebe razvrstavanja
    const auto broj = new size_t[K + 1]{0};

    // Prebrojavanje pojavljivanja
    for (size_t i = 0; i < n; i++) {
        broj[r[a[i]]]++;
    }

    // Sumiranje po prefiksima
    for (size_t i = 0, zbir = 0; i <= K; i++) {
        size_t br = broj[i];
        broj[i] = zbir;
        zbir += br;
    }

    // Sortiranje razvrstavanjem
    for (size_t i = 0; i < n; i++) {
        b[broj[r[a[i]]]++] = a[i];
    }

    // Oslobađanje memorije
    delete[] broj;
}

// Rekurzivno određivanje sufiksnog niza
// SA niske T dužine n nad azbukom reda K
static void DC3(size_t *T, size_t *SA, size_t n, size_t K) {
    // Dužine podnizova sa odgovarajućim ostacima
    const auto n0 = (n + 2) / 3;
    const auto n1 = (n + 1) / 3;
    const auto n2 = n / 3;
    const auto n02 = n0 + n2;

    // Kofa za sortiranje razvrstavanjem
    const auto R = new size_t[n02 + 3];
    R[n02] = R[n02 + 1] = R[n02 + 2] = '\0';

    // Pripremni korak: upisivanje nenultih ostataka
    for (size_t i = 0, j = 0; i < n + (n0 - n1); i++) {
        if (i % 3) R[j++] = i;
    }

    // Sufiksni niz nenultih ostataka
    const auto SA12 = new size_t[n02 + 3];
    SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = '\0';

    // Prvi korak: sortiranje razvrstavanjem nenultih
    razvrstavanje(R, SA12, T + 2, n02, K);
    razvrstavanje(SA12, R, T + 1, n02, K);
    razvrstavanje(R, SA12, T, n02, K);

    // Inicijalizacija leksikografskih imena
    auto c0 = static_cast<size_t>(-1);
    auto c1 = c0, c2 = c0, ime = 0ul;

    // Upisivanje leksikografskih imena trojki
    for (size_t i = 0; i < n02; i++) {
        // Uvećavanje imena (ranga) po potrebi
        if (T[SA12[i]] != c0 || T[SA12[i] + 1] != c1 || T[SA12[i] + 2] != c2) {
            ime++;
            c0 = T[SA12[i]];
            c1 = T[SA12[i] + 1];
            c2 = T[SA12[i] + 2];
        }

        // Upisivanje imena sa ostatkom jedan
        if (SA12[i] % 3 == 1) {
            R[SA12[i] / 3] = ime;
        // Upisivanje imena sa ostatkom dva
        } else {
            R[SA12[i] / 3 + n0] = ime;
        }
    }

    // Rekurzivni poziv ukoliko imena nisu jedinstvena
    if (ime < n02) {
        DC3(R, SA12, n02, ime);

        // Pohranjivanje jedinstvenih rangova nakon rekurzije
        for (size_t i = 0; i < n02; i++) {
            R[SA12[i]] = i + 1;
        }
    } else {
        // U suprotnom direkno pravljenje niza iz rangova
        for (size_t i = 0; i < n02; i++) {
            SA12[R[i] - 1] = i;
        }
    }

    // Kofa za zazvrstavanje nultih ostataka
    const auto R0 = new size_t[n0];

    // Priprema rangova nultih ostataka
    for (size_t i = 0, j = 0; i < n02; i++) {
        if (SA12[i] < n0) R0[j++] = 3 * SA12[i];
    }

    // Sufiksni niz nultih ostataka
    const auto SA0 = new size_t[n0];

    // Drugi korak: sortiranje razvrstavanjem nultih
    razvrstavanje(R0, SA0, T, n0, K);

    // Oslobađanje memorije
    delete[] R0;

    // Treći korak: spajanje nultih i nenultih ostataka
    for (size_t p = 0, t = n0 - n1, k = 0; k < n; k++) {
        // Dohvatanje tekućih indeksa
        const auto i = indeks();
        const auto j = SA0[p];

        // Ukoliko je sufiks iz SA12 manji
        if (SA12[t] < n0 ? ur2(T[i], R[SA12[t] + n0], T[j], R[j / 3]) :
            ur3(T[i], T[i + 1], R[SA12[t] - n0 + 1], T[j], T[j + 1], R[j / 3 + n0])) {

            // Upisivanje sufiksa u niz
            SA[k] = i;

            // Uvećavanje brojača obrađenih
            t++;

            // Prepisivanje SA0 ako su obrađeni svi iz SA12
            if (t == n02) {
                for (k++; p < n0; p++, k++) {
                    SA[k] = SA0[p];
                }
            }
        // Ukoliko je sufiks iz SA0 manji
        } else {
            // Upisivanje sufiksa u niz
            SA[k] = j;

            // Uvećavanje brojača obrađenih
            p++;

            // Prepisivanje SA12 ako su obrađeni svi iz SA0
            if (p == n0) {
                for (k++; t < n02; t++, k++) {
                    SA[k] = indeks();
                }
            }
        }
    }

    // Oslobađanje memorije
    delete[] R;
    delete[] SA12;
    delete[] SA0;
}

// Pravljenje sufiksnog niza Kerkejnen-Sandersom
void KaSa03::napraviSufiksniNiz() {
    // Prazna niska kao specijalni slučaj
    if (!n) return;

    // Niska dužine jedan kao specijalni slučaj
    if (n == 1) {
        *niz = 0;
        return;
    }

    // Svođenje niske na niz brojeva
    const auto T = new size_t[n + 3];
    std::copy_n(niska, n, T);

    // Popunjavanje dodatna tri prazna mesta
    T[n] = T[n + 1] = T[n + 2] = '\0';

    // Rekurzivno određivanje sufiksnog niza; razvrstavanje
    // karaktera na 128 mesta odgovara ASCII enkodiranju
    DC3(T, niz, n, 128);

    // Oslobađanje memorije
    delete[] T;
}
