#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

class Studentas {
public:
    Studentas();                                 // numatytasis konstruktorius
    Studentas(const std::string& vardas, const std::string& pavarde); // konstruktorius su parametrais
    Studentas(const Studentas& other);           // kopijavimo konstruktorius
    Studentas& operator=(const Studentas& other); // priskyrimo operatorius
    ~Studentas();                                // destruktorius

    void ivestiDuomenis();                       // duomenø ávedimo metodas
    void isvestiDuomenis(std::ostream& out) const; // duomenø iðvedimo metodas

    void skaiciuotiGalutini(bool naudotiVidurki); // galutinio paþymio skaièiavimas
    double gautiGalutini() const { return galutinisBalas_; } // Getteris galutiniam balui

    friend std::istream& operator>>(std::istream& in, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);

private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> namuDarbai_;
    int egzaminas_;
    double galutinisVid_; // galutinis paþymys pagal vidurká
    double galutinisMed_; // galutinis paþymys pagal medianà
    double galutinisBalas_; //Galutinis balas

    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;
};

#endif
