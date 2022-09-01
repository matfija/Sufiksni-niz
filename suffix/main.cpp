// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Glavna funkcija programa
int main() {
    // Banana kao jednostavan primer
    const char *const banana = "banana";

    // Instanciranje naivnog sortiranja
    NaiveSort ns(banana);

    // Sufiksni niz naivnim sortiranjem
    ns.napraviSufiksniNiz();

    // Ispis rezultata naivnog sortiranja
    std::cout << ns << std::endl;

    // Uspešan prekid rada programa
    exit(EXIT_SUCCESS);
}
