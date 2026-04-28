#include "rezident.h"

// Constructorul clasei rezident care inițializează toate atributele moștenite și atributul specific clasei rezident
rezident::rezident(const std::string& n, const std::string& pre, const std::string& f, const std::string& s, int sal, const std::string& sp, const std::string& p, int an) 
: personalSpital(n, pre, f), 
medic(n, pre, f, s, sal), 
asistent(n, pre, f, sp, p), 
anRezidentiat(an) {}

// Implementarea metodei de afișare pentru clasa rezident
void rezident::afisare() const {
    personalSpital::afisare();
    std::cout << "| Specializare: " << medic::specializare << " | Salariu: " << medic::salariu 
              << " | Ore de lucru: " << asistent::oreLucru << " | An rezidentiat: " << anRezidentiat << std::endl;
}