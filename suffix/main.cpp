// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Glavna funkcija programa
int main() {
    // Banana kao jednostavan primer
    const char *const banana = "banana";

    // Naivno sortiranje banane
    NaiveSort ns(banana);
    std::cout << ns << std::endl;

    // Dupliranje prefiksa banane
    PrefixDoubling pd(banana);
    std::cout << pd << std::endl;

    // Uspešan prekid rada programa
    exit(EXIT_SUCCESS);
}
