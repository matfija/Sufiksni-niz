// Biblioteka za Qt aplikaciju
#include <QtWidgets/QApplication>

// Biblioteka za Qt prozor
#include <QtWidgets/QMainWindow>

// Biblioteka za Qt grafikone
#include <QtCharts/QChartView>

// Biblioteka za Qt liniju
#include <QtCharts/QLineSeries>

// Biblioteka za matematiku
#include <cmath>

// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Biblioteka za Kerkejnen-Sandersa
#include "KaSa03.hpp"

// Biblioteka za algoritam SA-IS
#include "SAIS09.hpp"

// Upotreba imenskog prostora grafikona
QT_CHARTS_USE_NAMESPACE

// Šablon za tabeliranje ponašanja algoritma
template <typename SuffArr>
static QLineSeries *tabeliraj(const char *const niska,
                              const char *const algoritam) {
    // Instanciranje Qt linije
    auto series = new QLineSeries();

    // Određivanje dužine niske
    const auto n = strlen(niska);

    // Prolazak kroz i = [1, 2, ..., 2^j, ..., n]
    for (size_t i = 1; i <= n; i *= 2) {
        // Merenje vremena na početku rada algoritma
        const auto start = std::chrono::high_resolution_clock::now();

        // Konstrukcija sufiksnog niza nad i karaktera
        SuffArr sa(niska+n-i);

        // Merenje vremena na kraju rada algoritma
        const auto end = std::chrono::high_resolution_clock::now();

        // Dodavanje rezultata na vremensku seriju
        series->append(std::log2(i), std::log2((end - start).count()));
    }

    // Postavljanje imena serije
    series->setName(algoritam);

    // Vraćanje određene linije
    return series;
}

// Glavna funkcija programa
int main(int argc, char *argv[]) {
    // Instanciranje Qt aplikacije
    QApplication a(argc, argv);

    // Instanciranje Qt grafikona
    const auto grafikon = new QChart;

    // Generisanje pseudoslučajne niske
    const auto niska = randnis(100'000, 'a', 'z');

    // Dodavanje naivnog sortiranja
    grafikon->addSeries(tabeliraj<NaiveSort>(niska, "NaiveSort"));

    // Dodavanje dupliranja prefiksa
    grafikon->addSeries(tabeliraj<PrefixDoubling>(niska, "PrefixDoubling"));

    // Dodavanje Kerkejnen-Sandersa
    grafikon->addSeries(tabeliraj<KaSa03>(niska, "KaSa03"));

    // Oslobađanje memorije
    delete[] niska;

    // Postavljanje podrazumevanih osa
    grafikon->createDefaultAxes();

    // Instanciranje pogleda na Qt grafikon
    const auto pogled = new QChartView(grafikon);

    // Zastavica za jasniji grafikon
    pogled->setRenderHint(QPainter::Antialiasing);

    // Instanciranje Qt prozora
    QMainWindow window;

    // Postavljanje pogleda na grafikon
    window.setCentralWidget(pogled);

    // Postavljanje naslova prozora
    window.setWindowTitle("Konstrukcija sufiksnog niza");

    // Postavljanje veličine prozora
    window.resize(960, 540);

    // Prikaz napravljenog prozora
    window.show();

    // Predavanje izvršavanja aplikaciji
    return a.exec();
}
