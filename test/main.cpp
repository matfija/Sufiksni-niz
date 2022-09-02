// Biblioteka za testiranje
#include <QtTest>

// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

// Biblioteka za Kerkejnen-Sandersa
#include "KaSa03.hpp"

// Biblioteka za algoritam SA-IS
#include "SAIS09.hpp"

// Klasa za testiranje algoritama
class SuffixTest : public QObject {
    Q_OBJECT

private:
    // Banana i Misisipi kao jednostavni primeri
    const char *const banana = "banana";
    const char *const mississippi = "mississippi";

    // Lorem ipsum kao nešto složeniji primer
    const char *const lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                              "Quisque porta nec dui sed commodo. Lorem ipsum dolor sit amet, "
                              "consectetur adipiscing elit. Etiam tempor rhoncus orci, quis "
                              "ornare quam scelerisque sit amet. Sed dignissim quam sed nunc "
                              "euismod, vel vulputate nisl consectetur. Class aptent taciti "
                              "sociosqu ad litora torquent per conubia nostra, per inceptos "
                              "himenaeos. Praesent ultrices nibh et ex efficitur, a lobortis "
                              "sapien molestie. Duis at pulvinar nunc. Duis nec est nec leo "
                              "fringilla aliquam. Integer ut efficitur nulla, a imperdiet justo. "
                              "Pellentesque in augue lacus. Pellentesque orci nulla, mattis eu "
                              "consectetur quis, lacinia non ex. Aenean eget lectus euismod, "
                              "ultrices arcu id, elementum magna. Aenean est purus, fringilla "
                              "ut viverra sit amet, rhoncus sed magna. Maecenas eu scelerisque "
                              "tortor, sed efficitur libero.";

    // Proteinska sekvenca kao nešto složeniji primer
    const char *const spike = "MFVFLVLLPLVSSQCVNLTTRTQLPPAYTNSFTRGVYYPDKVFRSSVLHSTQDLFLPFFSNVTWFHAIHVS"
                              "GTNGTKRFDNPVLPFNDGVYFASTEKSNIIRGWIFGTTLDSKTQSLLIVNNATNVVIKVCEFQFCNDPFLG"
                              "VYYHKNNKSWMESEFRVYSSANNCTFEYVSQPFLMDLEGKQGNFKNLREFVFKNIDGYFKIYSKHTPINLV"
                              "RDLPQGFSALEPLVDLPIGINITRFQTLLALHRSYLTPGDSSSGWTAGAAAYYVGYLQPRTFLLKYNENGT"
                              "ITDAVDCALDPLSETKCTLKSFTVEKGIYQTSNFRVQPTESIVRFPNITNLCPFGEVFNATRFASVYAWNR"
                              "KRISNCVADYSVLYNSASFSTFKCYGVSPTKLNDLCFTNVYADSFVIRGDEVRQIAPGQTGKIADYNYKLP"
                              "DDFTGCVIAWNSNNLDSKVGGNYNYLYRLFRKSNLKPFERDISTEIYQAGSTPCNGVEGFNCYFPLQSYGF"
                              "QPTNGVGYQPYRVVVLSFELLHAPATVCGPKKSTNLVKNKCVNFNFNGLTGTGVLTESNKKFLPFQQFGRD"
                              "IADTTDAVRDPQTLEILDITPCSFGGVSVITPGTNTSNQVAVLYQDVNCTEVPVAIHADQLTPTWRVYSTG"
                              "SNVFQTRAGCLIGAEHVNNSYECDIPIGAGICASYQTQTNSPRRARSVASQSIIAYTMSLGAENSVAYSNN"
                              "SIAIPTNFTISVTTEILPVSMTKTSVDCTMYICGDSTECSNLLLQYGSFCTQLNRALTGIAVEQDKNTQEV"
                              "FAQVKQIYKTPPIKDFGGFNFSQILPDPSKPSKRSFIEDLLFNKVTLADAGFIKQYGDCLGDIAARDLICA"
                              "QKFNGLTVLPPLLTDEMIAQYTSALLAGTITSGWTFGAGAALQIPFAMQMAYRFNGIGVTQNVLYENQKLI"
                              "ANQFNSAIGKIQDSLSSTASALGKLQDVVNQNAQALNTLVKQLSSNFGAISSVLNDILSRLDKVEAEVQID"
                              "RLITGRLQSLQTYVTQQLIRAAEIRASANLAATKMSECVLGQSKRVDFCGKGYHLMSFPQSAPHGVVFLHV"
                              "TYVPAQEKNFTTAPAICHDGKAHFPREGVFVSNGTHWFVTQRNFYEPQIITTDNTFVSGNCDVVIGIVNNT"
                              "VYDPLQPELDSFKEELDKYFKNHTSPDVDLGDISGINASVVNIQKEIDRLNEVAKNLNESLIDLQELGKYE"
                              "QYIKWPWYIWLGFIAGLIAIVMVTIMLCCMTSCCSCLKGCCSCGSCCKFDEDDSEPVLKGVKLHYT";

    // Funkcija za proveru poznatih rezultata
    void poznato(SuffixArray &, std::vector<size_t>);

    // Funkcija za poređenje rezultata svih algoritama
    void uporedi(const char *const);

// Slotovi za konkretne testove
private Q_SLOTS:
    void naive();
    void doubling();
    void kasa03();
    void sais09();
    void poredi();
};

// Funkcija za proveru poznatih rezultata
void SuffixTest::poznato(SuffixArray &sa,
                         std::vector<size_t> ispravno) {
    QCOMPARE(sa.getV(), ispravno);
}

// Funkcija za poređenje rezultata svih algoritama
void SuffixTest::uporedi(const char *const niska) {
    // Naivno sortiranje niske
    NaiveSort ns(niska);

    // Dupliranje prefiksa niske
    PrefixDoubling pd(niska);

    // Jednostavno poređenje dva vektora
    QCOMPARE(pd.getV(), ns.getV());
}

// Testiranje naivnog sortiranja
void SuffixTest::naive() {
    {
        // Naivno sortiranje banane
        NaiveSort ns(banana);

        // Provera poznatih rezultata
        poznato(ns, {5, 3, 1, 0, 4, 2});
    }

    {
        // Naivno sortiranje Misisipija
        NaiveSort ns(mississippi);

        // Provera poznatih rezultata
        poznato(ns, {10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2});
    }
}

// Testiranje dupliranja prefiksa
void SuffixTest::doubling() {
    {
        // Dupliranje prefiksa banane
        PrefixDoubling pd(banana);

        // Provera poznatih rezultata
        poznato(pd, {5, 3, 1, 0, 4, 2});
    }

    {
        // Dupliranje prefiksa Misisipija
        PrefixDoubling pd(mississippi);

        // Provera poznatih rezultata
        poznato(pd, {10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2});
    }
}

// Testiranje Kerkejnen-Sandersa
void SuffixTest::kasa03() { }

// Testiranje algoritma SA-IS
void SuffixTest::sais09() { }

// Testiranje poređenjem svih algoritama
void SuffixTest::poredi() {
    // Poređenje na primeru banane
    uporedi(banana);

    // Poređenje na primeru Misisipija
    uporedi(mississippi);

    // Poređenje na primeru lorem ipsuma
    uporedi(lorem);

    // Poređenje na primeru proteinske sekvence
    uporedi(spike);

    // Poređenje na primeru slučajne niske
    uporedi(randnis(100'000, 'a', 'z'));
}

// Automatsko generisanje glavne funkcije
QTEST_APPLESS_MAIN(SuffixTest)

// Moc sa svim potrebnim informacijama
#include "main.moc"
