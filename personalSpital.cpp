#include <string>
#include "personalSpital.h"

int personalSpital::idCounter = 0;

// Constructorul clasei personalSpital care initializeaza numele, prenumele, functia si id-ul personalului spitalului
personalSpital::personalSpital(const std::string& n, const std::string& p, const std::string& f) : nume(n), prenume(p), functie(f) {
    id = ++idCounter;
}

// Metoda de afisare a informatiilor despre personalul spitalului
void personalSpital::afisare() const {
    std::cout << "ID: " << id << "| Nume: " << nume << "| Prenume: " << prenume << "| Functie: " << functie << std::endl;
}



