#include "Studentas.h"

// Numatytojo konstruktoriaus apibrëþimas
Studentas::Studentas() : vardas_(""), pavarde_(""), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0), galutinisBalas_(0.0) {}

// Konstruktorius su parametrais
Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0), galutinisBalas_(0.0) {}

// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_), namuDarbai_(other.namuDarbai_),
    egzaminas_(other.egzaminas_), galutinisVid_(other.galutinisVid_), galutinisMed_(other.galutinisMed_), galutinisBalas_(other.galutinisBalas_) {}

// Priskyrimo operatorius
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        namuDarbai_ = other.namuDarbai_;
        egzaminas_ = other.egzaminas_;
        galutinisVid_ = other.galutinisVid_;
        galutinisMed_ = other.galutinisMed_;
        galutinisBalas_ = other.galutinisBalas_;
    }
    return *this;
}

// Destruktorius
Studentas::~Studentas() {}

// Duomenø ávedimas
void Studentas::ivestiDuomenis() {
    std::cout << "Áveskite vardà ir pavardæ: ";
    std::cin >> vardas_ >> pavarde_;
    int rezultatas;
    std::cout << "Áveskite namø darbø rezultatus (baigti -1): ";
    while (std::cin >> rezultatas && rezultatas != -1) {
        namuDarbai_.push_back(rezultatas);
    }
    std::cout << "Áveskite egzamino rezultatà: ";
    std::cin >> egzaminas_;
}

// Duomenø iðvedimas
void Studentas::isvestiDuomenis(std::ostream& out) const {
    out << std::setw(15) << pavarde_ << std::setw(15) << vardas_
        << std::setw(15) << std::fixed << std::setprecision(2) << galutinisVid_
        << std::setw(15) << galutinisMed_ << std::endl;
}

// Vidurkio skaièiavimas
double Studentas::skaiciuotiVidurki() const {
    double sum = 0;
    for (int nd : namuDarbai_) sum += nd;
    return sum / namuDarbai_.size();
}

// Medianos skaièiavimas
double Studentas::skaiciuotiMediana() const {
    std::vector<int> temp = namuDarbai_;
    std::sort(temp.begin(), temp.end());
    if (temp.size() % 2 == 0) return (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2.0;
    else return temp[temp.size() / 2];
}

// Galutinio paþymio skaièiavimas
void Studentas::skaiciuotiGalutini(bool naudotiVidurki) {
    if (naudotiVidurki) galutinisVid_ = 0.4 * skaiciuotiVidurki() + 0.6 * egzaminas_;
    else galutinisMed_ = 0.4 * skaiciuotiMediana() + 0.6 * egzaminas_;
}

// Perdengtas >> operatorius
std::istream& operator>>(std::istream& in, Studentas& studentas) {
    studentas.ivestiDuomenis();
    return in;
}

// Perdengtas << operatorius
std::ostream& operator<<(std::ostream& out, const Studentas& studentas) {
    studentas.isvestiDuomenis(out);
    return out;
}