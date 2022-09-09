#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

// Biblioteka za rad sa C niskama
#include <cstring>

// Biblioteka za rad sa vektorima
#include <vector>

// Biblioteka za formatirani ulaz i izlaz
#include <iostream>

// Apstraktna klasa za sufiksni niz
class SuffixArray {
protected:
    // Konstruktor niza na osnovu niske
    SuffixArray(const char *const);

    // Virtuelni destruktor oslobađa memoriju
    virtual ~SuffixArray();

    // Izbrisani konstruktori kopije
    SuffixArray(const SuffixArray &) = delete;
    SuffixArray& operator=(const SuffixArray &) = delete;

    // Izbrisani konstruktori premeštanja
    SuffixArray(SuffixArray &&) = delete;
    SuffixArray& operator=(SuffixArray &&) = delete;

    // Virtuelna funkcija za konstrukciju niza
    virtual void napraviSufiksniNiz() = 0;

    // Dužina niske i sufiksnog niza
    const size_t n;

    // Učitana niska kao niz karaktera
    const char *const niska;

    // Izračunati sufiksni niz indeksa
    size_t *const niz;

    // Vektor vremena izvršavanja
    std::vector<size_t> vreme;

    // Srednja vrednost vremena
    size_t mean;

    // Odstupanje vremena
    size_t std;

    // Funkcija za statistike vremena
    void statistike();

public:
    // Funkcija za dohvatanje dužine
    size_t getN() const;

    // Funkcija za dohvatanje niske
    const char *getNiska() const;

    // Funkcija za dohvatanje niza
    const size_t *getNiz() const;

    // Funkcija za dohvatanje vektora
    const std::vector<size_t> getV() const;

    // Funkcija za dohvatanje karaktera
    char getNiska(size_t) const;

    // Funkcija za dohvatanje indeksa
    size_t getNiz(size_t) const;

    // Funkcija za dohvatanje vremena
    const std::vector<size_t> &getVreme() const;

    // Funkcija za dohvatanje sredine
    size_t getMean() const;

    // Funkcija za dohvatanje odstupanja
    size_t getStd() const;
};

// Funkcija za ilustrovanje niza
const std::string ilustrujNiz(const size_t *const, size_t);

// Funkcija za ilustrovanje vektora
const std::string ilustrujNiz(const std::vector<size_t>);

// Funkcija za ispis niske i niza
std::ostream &operator<<(std::ostream &, const SuffixArray &);

// Funkcija za generisanje pseudoslučajne niske
const char *randnis(size_t, char, char);

#endif // SUFFIXARRAY_H
