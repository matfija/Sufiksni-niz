// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Biblioteka za Kerkejnen-Sandersa
#include "KaSa03.hpp"

// Biblioteka za algoritam SA-IS
#include "SAIS09.hpp"

// Banana kao jednostavan primer
static const char *const banana = "banana";

// Glavna funkcija programa
int main() {
    // Naivno sortiranje banane
    NaiveSort ns(banana);
    std::cout << ns << std::endl;

    // Dupliranje prefiksa banane
    PrefixDoubling pd(banana);
    std::cout << pd << std::endl;

    // Kerkejnen-Sanders banane
    KaSa03 ks(banana);
    std::cout << ks << std::endl;

    // Algoritam SA-IS banane
    SAIS09 si(banana);
    std::cout << si << std::endl;

    // Uspešan prekid rada programa
    exit(EXIT_SUCCESS);
}
