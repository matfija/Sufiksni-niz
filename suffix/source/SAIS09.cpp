// Biblioteka za algoritam SA-IS
#include "SAIS09.hpp"

// Pamćenje prosleđene niske
SAIS09::SAIS09(const char *const s)
    : SuffixArray(s) { napraviSufiksniNiz(); }

// Dohvatanje indikatora iz LS niza
static inline bool dohvati(unsigned char* t, int i) {
    return t[i / 8] & (1 << (i % 8));
}

// Postavljanje indikatora u LS niz
static inline void postavi(unsigned char* t, int i, int indikator) {
    t[(i) / 8] = indikator ?
                static_cast<unsigned char>((1 << (i % 8)) | t[i / 8]) :
                ((~(1 << (i % 8))) & t[i / 8]);
}

// Dohvatanje karaktera ili ranga iz niske
static inline int rang(const char *const T, int i, int cs) {
    return cs == sizeof(int) ?
           (reinterpret_cast<const int *>(T)[i]) :
           (reinterpret_cast<const char *>(T)[i]);
}

// Provera da li je karakter ili rang LSM
static inline bool LMS(unsigned char* t, int i) {
    return (i > 0 && dohvati(t, i) && !dohvati(t, i - 1));
}

// Pronalaženje početka ili kraja kofe
static void razvrstavanje(const char *const T, int *r, int n, int K, int cs, bool kraj) {
    // Pražnjenje svih kofa
    std::fill_n(r, K + 1, 0);

    // Prebrojavanje pojavljivanja
    for (int i = 0; i < n; i++)
        r[rang(T, i, cs)]++;

    // Sumiranje po prefiksima
    for (int i = 0, zbir = 0; i <= K; i++) {
        zbir += r[i];
        r[i] = kraj ? zbir : zbir - r[i];
    }
}

// Indukovano sortiranje podniza SAl
static void indukujSAl(unsigned char *t, int *SA, const char *const T,
                       int *r, int n, int K, int cs, bool kraj) {
    // Pronalaženje početnih pozicija kofa
    razvrstavanje(T, r, n, K, cs, kraj);

    // Sortiranje podniza razvrstavanjem
    for (int i = 0; i < n; i++) {
        int j = SA[i] - 1;
        if (j >= 0 && !dohvati(t, j))
            SA[r[rang(T, j, cs)]++] = j;
    }
}

// Indukovano sortiranje podniza SAs
static void indukujSAs(unsigned char *t, int *SA, const char *const T,
                       int *r, int n, int K, int cs, bool kraj) {
    // Pronalaženje krajnjih pozicija kofa
    razvrstavanje(T, r, n, K, cs, kraj);

    // Sortiranje podniza razvrstavanjem
    for (int i = n - 1; i >= 0; i--) {
        int j = SA[i] - 1;
        if (j >= 0 && dohvati(t, j))
            SA[--r[rang(T, j, cs)]] = j;
    }
}

// Rekurzivno određivanje sufiksnog niza
// SA niske T dužine n nad azbukom reda K
static void SA_IS(const char *const T, int *SA, int n, int K, int cs) {
    // Optimizovani bitovski LS niz
    const auto t = new unsigned char[static_cast<size_t>(n) / 8 + 1];

    // Inicijalizacija LS niza
    postavi(t, n - 2, 0);
    postavi(t, n - 1, 1);

    // Pripremni korak: popunjavanje LS niza
    for (int i = n - 3; i >= 0; i--) {
        postavi(t, i, rang(T, i, cs) < rang(T, i + 1, cs) ||
                      (rang(T, i, cs) == rang(T, i + 1, cs) && dohvati(t ,i + 1)));
    }

    // Pronalaženje krajeva kofa
    auto R = new int[static_cast<size_t>(K) + 1];
    razvrstavanje(T, R, n, K, cs, true);

    // Inicijalizacija niza na specijalne vrednosti
    std::fill_n(SA, n, -1);

    // Približno razvrstavanje LMS sufiksa
    for (int i = 1; i < n; i++) {
        if (LMS(t ,i)) SA[--R[rang(T, i, cs)]] = i;
    }

    // Indukovano sortiranje L i S podnizova
    indukujSAl(t, SA, T, R, n, K, cs, false);
    indukujSAs(t, SA, T, R, n, K, cs, true);

    // Oslobađanje memorije
    delete[] R;

    // Postavljanje sortiranih LMS sufiksa na početak niza
    int n1 = 0;
    for (int i = 0; i < n; i++) {
        if (LMS(t, SA[i])) SA[n1++] = SA[i];
    }

    // Popunjavanje ostatka niza specijalnim vrednostima
    std::fill_n(SA + n1, n - n1, -1);

    // Prvi korak: redukcija problema svođenjem na rangove
    int ime = 0, pret = -1;
    for (int i = 0; i < n1; i++) {
        // Izdvajanje trenutnog indeksa u nizu
        int tren = SA[i];

        // Indikator da li ima razlike
        bool razl = false;
        for (int d = 0; d < n; d++) {
            if (pret == -1 || rang(T, tren + d, cs) != rang(T, pret + d, cs) ||
                              dohvati(t, tren + d) != dohvati(t, pret + d)) {
                razl = true;
                break;
            } else if (d > 0 && (LMS(t, tren + d) || LMS(t, pret + d))) {
                break;
            }
        }

        // Uvećavanje ranga ako ima razlike
        if (razl) {
            ime++;
            pret = tren;
        }

        // Popravljanje trenutne vrednosti deljenjem
        tren = !(tren % 2) ? tren / 2 : (tren - 1) / 2;

        // Dodeljivanje novog ranga trenutnom sufiksu
        SA[n1 + tren] = ime - 1;
    }

    // Popunjavanje preostalih rangova
    for (int i = n - 1, j = n - 1; i >= n1; i--) {
        if (SA[i] >= 0) SA[j--] = SA[i];
    }

    // Drugi korak: rešavanje redukovanog problema
    int *SA1 = SA, *s1 = SA + n - n1;

    // Rekurzivni poziv ukoliko imena nisu jedinstvena
    if (ime < n1) {
        SA_IS(reinterpret_cast<char *>(s1), SA1, n1, ime - 1, sizeof(int));
    } else {
        // U suprotnom direkno pravljenje niza iz rangova
        for (int i = 0; i < n1; i++) {
            SA1[s1[i]] = i;
        }
    }

    // Pronalaženje krajeva kofa
    R = new int[static_cast<size_t>(K) + 1];
    razvrstavanje(T, R, n, K, cs, true);

    // Postavljanje LMS sufiksa na pravo mesto
    for (int i = 1, j = 0; i < n; i++) {
        if (LMS(t, i)) s1[j++] = i;
    }

    // Postavljanje ostalih već izračunatih rangova
    for (int i = 0; i < n1; i++) {
        SA1[i] = s1[SA1[i]];
    }

    // Popunjavanje ostatka niza specijalnim vrednostima
    std::fill_n(SA + n1, n - n1, -1);

    // Treći korak: indukovanje rešenja originalnog problema
    for (int i = n1 - 1; i >= 0; i--) {
        int j = SA[i];
        SA[i] = -1;
        SA[--R[rang(T, j, cs)]] = j;
    }

    // Indukovano sortiranje L i S podnizova
    indukujSAl(t, SA, T, R, n, K, cs, false);
    indukujSAs(t, SA, T, R, n, K, cs, true);

    // Oslobađanje memorije
    delete[] t;
    delete[] R;
}

// Pravljenje sufiksnog niza algoritmom SA-IS
void SAIS09::napraviSufiksniNiz() {
    // Prazna niska kao specijalni slučaj
    if (!n) return;

    // Niska dužine jedan kao specijalni slučaj
    if (n == 1) {
        *niz = 0;
        return;
    }

    // Pomoćni sufiksni niz sa dodatnim mestom
    const auto SA = new int[n + 1];

    // Rekurzivno određivanje sufiksnog niza; razvrstavanje
    // karaktera na 128 mesta odgovara ASCII enkodiranju
    SA_IS(niska, SA, static_cast<int>(n + 1), 128, 1);

    // Prepisivanje sufiksnog niza
    std::copy_n(SA + 1, n, niz);

    // Oslobađanje memorije
    delete[] SA;
}
