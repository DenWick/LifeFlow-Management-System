#include "sectie.h"

// Implementarea constructorului pentru clasa sectie
sectie::sectie(const std::string& n) : nume(n) {}

// Implementarea metodei pentru adaugarea unui medic in sectie
void sectie::adaugaMedic(medic* m) {
    medici.push_back(m);
}

// Implementarea metodei pentru afisarea informatiilor despre sectie si medicii din ea
void sectie::afisare() const {
    if (medici.empty()) {
        std::cout<< "Sectia " << nume << " nu are medici." <<std::endl;
    } else {
        std::cout<< "Sectia " << nume << " are urmatorii medici:" <<std::endl;
        for (const medic* m : medici) {
            m->afisare();
        }
    }
}

// Implementarea destructorului pentru clasa sectie
sectie::~sectie() {
    for (auto m : medici) {
        delete m;
    }
    medici.clear();
}
