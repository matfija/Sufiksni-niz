// Biblioteka za testiranje
#include <QtTest>

// Biblioteka za naivno sortiranje
#include "NaiveSort.hpp"

// Biblioteka za dupliranje prefiksa
#include "PrefixDoubling.hpp"

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
    void poznato(SuffixArray *, std::vector<size_t>);

    // Funkcija za poređenje rezultata svih algoritama
    void uporedi(const char *const);

// Slotovi za konkretne testove
private Q_SLOTS:
    void naive();
    void doubling();
    void poredi();
    void random();
};

// Funkcija za proveru poznatih rezultata
void SuffixTest::poznato(SuffixArray *sa,
                         std::vector<size_t> ispravno) {
    // Dobijeni sufiksni niz kao vektor
    std::vector<size_t> sufiks(sa->getN());
    std::copy_n(sa->getNiz(), sa->getN(), std::begin(sufiks));

    // Jednostavno poređenje dva vektora
    QCOMPARE(sufiks, ispravno);
}

// Funkcija za poređenje rezultata svih algoritama
void SuffixTest::uporedi(const char *const niska) {
    // Naivno sortiranje niske
    NaiveSort ns(niska);
    ns.napraviSufiksniNiz();

    // Dobijeni sufiksni niz kao vektor
    std::vector<size_t> sns(ns.getN());
    std::copy_n(ns.getNiz(), ns.getN(), std::begin(sns));

    // Dupliranje prefiksa niske
    PrefixDoubling pd(niska);
    pd.napraviSufiksniNiz();

    // Dobijeni sufiksni niz kao vektor
    std::vector<size_t> spd(pd.getN());
    std::copy_n(pd.getNiz(), pd.getN(), std::begin(spd));

    // Jednostavno poređenje dva vektora
    QCOMPARE(spd, sns);
}

// Testiranje naivnog sortiranja
void SuffixTest::naive() {
    {
        // Naivno sortiranje banane
        NaiveSort ns(banana);
        ns.napraviSufiksniNiz();

        // Provera poznatih rezultata
        poznato(&ns, {5, 3, 1, 0, 4, 2});
    }

    {
        // Naivno sortiranje Misisipija
        NaiveSort ns(mississippi);
        ns.napraviSufiksniNiz();

        // Provera poznatih rezultata
        poznato(&ns, {10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2});
    }
}

// Testiranje dupliranja prefiksa
void SuffixTest::doubling() {
    {
        // Dupliranje prefiksa banane
        PrefixDoubling pd(banana);
        pd.napraviSufiksniNiz();

        // Provera poznatih rezultata
        poznato(&pd, {5, 3, 1, 0, 4, 2});
    }

    {
        // Dupliranje prefiksa Misisipija
        PrefixDoubling pd(mississippi);
        pd.napraviSufiksniNiz();

        // Provera poznatih rezultata
        poznato(&pd, {10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2});
    }
}

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
}

// Testiranje na primeru slučajne niske
void SuffixTest::random() {
    // Marsenov generator pseudoslučajnih brojeva
    std::mt19937 rng(0);

    // Inicijalno prazna niska (niz karaktera)
    std::vector<char> niska;

    // Generisanje velikog broja karaktera
    for (int i = 0; i < 100'000; i++) {
        niska.push_back(std::uniform_int_distribution<char>('a', 'z')(rng));
    }

    // Zatvaranje niske nultim karakterom
    niska.push_back('\0');

    // Poređenje na primeru slučajne niske
    uporedi(niska.data());
}

// Automatski main sa jednom klasom
QTEST_APPLESS_MAIN(SuffixTest)

// Moc sa svim potrebnim informacijama
#include "main.moc"
