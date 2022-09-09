// Biblioteka za sufiksni niz
#include "SuffixArray.hpp"

// Biblioteka za rad sa iteratorima
#include <iterator>

// Biblioteka za pseudoslučajnost
#include <random>

// Biblioteka za rad sa izlaznim tokom
#include <sstream>

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

// Funkcija za dohvatanje vremena
const std::vector<size_t> &SuffixArray::getVreme() const {
    return vreme;
}

// Funkcija za dohvatanje sredine
size_t SuffixArray::getMean() const {
    return mean;
}

// Funkcija za dohvatanje odstupanja
size_t SuffixArray::getStd() const {
    return std;
}

// Funkcija za statistike vremena
void SuffixArray::statistike() {
    // Sumiranje svih vremena
    size_t zbir = std::accumulate(std::cbegin(vreme), std::cend(vreme), size_t());

    // Srednja vrednost vremena
    mean = zbir / std::size(vreme);

    // Inicijalizacija vektora razlika
    std::vector<size_t> diff(std::size(vreme));

    // Popunjavanje vektora razlika
    std::transform(std::cbegin(vreme),
                   std::cend(vreme),
                   std::begin(diff),
                   [this](size_t x) { return x - mean; });

    // Kvadrirana suma centiranih vremena
    size_t square = std::inner_product(std::cbegin(diff),
                                       std::cend(diff),
                                       std::begin(diff),
                                       size_t());

    // Standardno odstupanje vremena
    std = static_cast<size_t>(std::sqrt(square / std::size(vreme)));
}

// Funkcija za ilustrovanje niza
const std::string ilustrujNiz(const size_t *const niz, size_t n) {
    // Posebna obrada praznog niza
    if (!n) return "[]";

    // Izlazni stringovni tok
    std::ostringstream out;

    // Ispis otvorene zagrade niza na izlazni tok
    out << '[';

    // Ispis elemenatana niza razdvojenih razmakom
    std::copy(niz, niz + n - 1, std::ostream_iterator<size_t>(out, ", "));

    // Ispis poslednjeg elementa i zatvaranje zagrade
    out << niz[n - 1] << ']';

    // Pretvaranje toka u nisku
    return out.str();
}

// Funkcija za ilustrovanje vektora
const std::string ilustrujNiz(const std::vector<size_t> niz) {
    return ilustrujNiz(std::data(niz), std::size(niz));
}

// Funkcija za ispis niske i niza
std::ostream &operator<<(std::ostream &out, const SuffixArray &sa) {
    // Ispis niske na izlazni tok
    out << sa.getNiska() << std::endl;

    // Ilustrovanje niza
    return out << ilustrujNiz(sa.getNiz(), sa.getN());
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
