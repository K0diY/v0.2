#include "Studentas.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <iomanip>

void nuskaitytiIsFailo(std::vector<Studentas>& studentai) {
    std::ifstream file("kursiokai.txt");
    if (!file) throw std::runtime_error("Nepavyko atidaryti failo.");
    std::string vardas, pavarde;
    while (file >> vardas >> pavarde) {
        Studentas studentas(vardas, pavarde);
        studentai.push_back(studentas);
    }
}

// Generuoja atsitiktin� student� s�ra�� ir i�saugo � fail�
void generuotiFaila(const std::string& failoVardas, int studentuKiekis) {
    std::ofstream file(failoVardas);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nd_dist(1, 10); // Nam� darb� balai tarp 1 ir 10
    std::uniform_int_distribution<> egz_dist(1, 10); // Egzamin� balai tarp 1 ir 10

    for (int i = 1; i <= studentuKiekis; ++i) {
        file << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < 5; ++j) { // 5 nam� darb� balai
            file << " " << nd_dist(gen);
        }
        file << " " << egz_dist(gen) << "\n";
    }
}

// Nuskaitymas i� failo
void nuskaitytiIsFailo(const std::string& failoVardas, std::vector<Studentas>& studentai) {
    std::ifstream file(failoVardas);
    if (!file) throw std::runtime_error("Nepavyko atidaryti failo.");

    std::string vardas, pavarde;
    int egzaminas;
    std::vector <int> namuDarbai(5);

    while (file >> vardas >> pavarde) {
        for (int& nd : namuDarbai) file >> nd;
        file >> egzaminas;
        studentai.emplace_back (vardas, pavarde, namuDarbai, egzaminas);
    }
}

// Padalina studentus � dvi kategorijas pagal galutin� pa�ym�
void rusiuotiStudentus(const std::vector<Studentas>& studentai, std::vector<Studentas>& nuskriaustukai, std::vector<Studentas>& galvotieji) {
    for (const auto& studentas : studentai) {
        if (studentas.gautiGalutini() < 5.0)
            nuskriaustukai.push_back(studentas);
        else
            galvotieji.push_back(studentas);
    }
}

// I�saugo studentus � fail�
void issaugotiIFaila(const std::string& failoVardas, const std::vector<Studentas>& studentai) {
    std::ofstream file(failoVardas);
    file << std::setw(15) << "Pavard�" << std::setw(15) << "Vardas" << std::setw(15) << "Galutinis (Vid.)" << "\n";
    file << "----------------------------------------------------------\n";
    for (const auto& studentas : studentai) {
        file << studentas;
    }
}

int main() {
    std::vector<Studentas> studentai;
    int pasirinkimas;
    bool naudotiVidurki;

    std::cout << "Pasirinkite pa�ymio skai�iavimo metod� (1 - vidurkis, 2 - mediana): ";
    std::cin >> pasirinkimas;
    naudotiVidurki = pasirinkimas == 1;

    nuskaitytiIsFailo(studentai);

    for (Studentas& studentas : studentai) studentas.skaiciuotiGalutini(naudotiVidurki);

    std::cout << "Pavard�     Vardas       Galutinis (Vid.) / Galutinis (Med.)" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    for (const Studentas& studentas : studentai) std::cout << studentas;

    const std::vector <int> studentuSkaiciai = { 1000, 10000, 100000, 1000000, 10000000 };
    for (int kiekis : studentuSkaiciai) {
        std::string failoVardas = "studentai_" + std::to_string(kiekis) + ".txt";

        // Failo generavimas
        auto pradzia = std::chrono::high_resolution_clock::now();
        generuotiFaila(failoVardas, kiekis);
        auto pabaiga = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> trukme = pabaiga - pradzia;
        std::cout << "Failo generavimas (" << kiekis << " irasu): " << trukme.count() << " s\n";

        // Duomen� nuskaitymas
        std::vector<Studentas> studentai;
        pradzia = std::chrono::high_resolution_clock::now();
        nuskaitytiIsFailo(failoVardas, studentai);
        pabaiga = std::chrono::high_resolution_clock::now();
        trukme = pabaiga - pradzia;
        std::cout << "Duomen� nuskaitymas (" << kiekis << " irasu): " << trukme.count() << " s\n";

        // Galutinio balo skai�iavimas ir r��iavimas � kategorijas
        for (auto& studentas : studentai) studentas.skaiciuotiGalutini(true);

        std::vector<Studentas> nuskriaustukai, galvotieji;
        pradzia = std::chrono::high_resolution_clock::now();
        rusiuotiStudentus(studentai, nuskriaustukai, galvotieji);
        pabaiga = std::chrono::high_resolution_clock::now();
        trukme = pabaiga - pradzia;
        std::cout << "R��iavimas � kategorijas (" << kiekis << " irasu): " << trukme.count() << " s\n";

        // I�vedimas � atskirus failus
        pradzia = std::chrono::high_resolution_clock::now();
        issaugotiIFaila("nuskriaustukai_" + std::to_string(kiekis) + ".txt", nuskriaustukai);
        issaugotiIFaila("galvotieji_" + std::to_string(kiekis) + ".txt", galvotieji);
        pabaiga = std::chrono::high_resolution_clock::now();
        trukme = pabaiga - pradzia;
        std::cout << "I�vedimas � failus (" << kiekis << " irasu): " << trukme.count() << " s\n";
    }

    return 0;
}