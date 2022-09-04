// Biblioteka za algoritam SA-IS
#include "SAIS09.hpp"

// Pamćenje prosleđene niske
SAIS09::SAIS09(const char *const s)
    : SuffixArray(s) { napraviSufiksniNiz(); }

// Dohvatanje indikatora iz LS niza
static inline unsigned char dohvati(unsigned char* t, int i) {
    return t[i / 8] & (1 << (i % 8)) ? 1 : 0;
}

// Postavljanje indikatora u LS niz
static inline void postavi(unsigned char* t, int i, int indikator) {
    t[(i) / 8] = indikator ?
                static_cast<unsigned char>((1 << (i % 8)) | t[i / 8]) :
                ((~(1 << (i % 8))) & t[i / 8]);
}

// Dojvatanje karaktera ili ranga iz niske
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

    // Popunjavanje LS niza jednom prolaskom zdesna nalevo
    for (int i = n - 3; i >= 0; i--)
        postavi(t, i, (rang(T, i, cs) < rang(T, i + 1, cs) ||
                      (rang(T, i, cs) == rang(T, i + 1, cs) && dohvati(t ,i + 1) == 1)) ? 1 : 0);

    // Oslobađanje memorije
    delete[] t;
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
