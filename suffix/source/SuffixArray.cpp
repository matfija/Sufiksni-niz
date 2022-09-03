// Biblioteka za sufiksni niz
#include "SuffixArray.hpp"

// Biblioteka za rad sa iteratorima
#include <iterator>

// Biblioteka za pseudoslučajnost
#include <random>

// Pamćenje prosleđene niske
SuffixArray::SuffixArray(const char * const s)
    : n(strlen(s)), niska(s), niz(new size_t[n]) { }

// Virtuelni destruktor oslobađa memoriju
SuffixArray::~SuffixArray() {
    delete[] niz;
}

// Funkcija za dohvatanje dužine
size_t SuffixArray::getN() const {
    return n;
}

// Funkcija za dohvatanje niske
const char *SuffixArray::getNiska() const {
    return niska;
}

// Funkcija za dohvatanje niza
const size_t *SuffixArray::getNiz() const {
    return niz;
}

// Funkcija za dohvatanje vektora
const std::vector<size_t> SuffixArray::getV() const {
    return std::vector<size_t>(niz, niz + n);
}

// Funkcija za dohvatanje karaktera
char SuffixArray::getNiska(size_t i) const {
    return niska[i];
}

// Funkcija za dohvatanje indeksa
size_t SuffixArray::getNiz(size_t i) const {
    return niz[i];
}

// Funkcija za ispis niske i niza
std::ostream& operator<<(std::ostream& out, const SuffixArray& sa) {
    // Ispis niske na izlazni tok
    out << sa.getNiska() << std::endl;

    // Dohvatanje dužine niza
    const auto n = sa.getN();

    // Posebna obrada praznog niza
    if (!n) return out << "[]";

    // Dohvatanje sufiksnog niza
    const auto niz = sa.getNiz();

    // Ispis otvorene zagrade niza na izlazni tok
    out << '[';

    // Ispis elemenatana niza razdvojenih razmakom
    std::copy(niz, niz + n - 1, std::ostream_iterator<size_t>(out, " "));

    // Ispis poslednjeg elementa i zatvaranje zagrade
    return out << niz[n - 1] << ']';
}

// Funkcija za generisanje pseudoslučajne niske
const char *randnis(size_t n, char min, char max) {
    // Marsenov generator pseudoslučajnih brojeva
    std::mt19937 rng(0);

    // Inicijalno prazna niska (niz karaktera)
    const auto niska = new char[n + 1];

    // Generisanje velikog broja karaktera
    for (size_t i = 0; i < n; i++) {
        niska[i] = std::uniform_int_distribution<char>(min, max)(rng);
    }

    // Vraćanje generisane niske
    return niska;
}
