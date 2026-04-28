#include "asistent.h"

// Constructorul clasei asistent care initializeaza numele, prenumele, functia, specializarea si id-ul asistentului
asistent::asistent(const std::string& n, const std::string& pre, const std::string& f, const std::string& s, const std::string& p) : personalSpital(n, pre, f), specializare(s), oreLucru(p) {}

// Metoda de afisare a informatiilor despre asistent
void asistent::afisare() const {
    personalSpital::afisare();
    std::cout << "| Specializare: " << specializare << " |  Ore de lucru: " << oreLucru << std::endl;
}