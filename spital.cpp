#include "spital.h"
#include "exceptiiSpital.h"
#include <iostream>
#include <algorithm>

// Constructor
spital::spital(const std::string& n) : numeSpital(n) {}

// Metode de adaugare
void spital::adaugaPersonal(personalSpital* p) {
    personal.push_back(p);
}

void spital::adaugaSectie(sectie* s) {
    sectii.push_back(s);
}

void spital::adaugaPacient(pacient* p) {
    pacienti.push_back(p);
}

void spital::adaugaReteta(reteta* r) {
    retete.push_back(r);
}

// Stergere pacient
void spital::stergePacient(const std::string& numeCautat, std::string prenumeCautat) {
    bool gasit = false;
    for (auto it = pacienti.begin(); it != pacienti.end(); ) {
        if ((*it)->get_nume() == numeCautat && (*it)->get_prenume() == prenumeCautat) {
            delete *it;
            it = pacienti.erase(it);
            gasit = true;
            std::cout << "Pacientul a fost externat.\n";
        } else {
            ++it;
        }
    }
    
    if (!gasit) {
        throw std::runtime_error("Pacientul nu a fost gasit!");
    }
}

// Afisare informatii spital
void spital::afisare() const {
    std::cout << "Spital: " << numeSpital << "\n";
    
    std::cout << "Personal:\n";
    for (const personalSpital* p : personal) {
        p->afisare();
    }

    std::cout << "Sectii:\n";
    for (const sectie* s : sectii) {
        s->afisare();
    }

    std::cout << "Pacienti:\n";
    for (const pacient* p : pacienti) {
        p->afisare();
    }

    std::cout << "Retete:\n";
    for (const reteta* r : retete) {
        r->afiseaza();
    }
}

// Modificare salariu medic
void spital::modificaSalariuMedic(int idCautat, int salariuNou) {
    bool gasit = false;

    for (auto p : personal) {
        if (p->getId() == idCautat) {
            medic* m = dynamic_cast<medic*>(p);

            if (m != nullptr) {
                m->setSalariu(salariuNou);
                std::cout << "Salariul pentru medicul cu ID " << idCautat << " a fost actualizat la " << salariuNou << ".\n";
                gasit = true;
                break;
            } else {
                throw std::runtime_error("Angajatul cu ID-ul respectiv nu este medic (nu are salariu de modificat).");
            }
        }
    }

    if (!gasit) {
        throw std::runtime_error("Eroare: Medicul cu ID-ul " + std::to_string(idCautat) + " nu a fost gasit!");
    }
}

// Destructor
spital::~spital() {
    for (auto& p : personal) {
        delete p;
    }
    for (auto& s : sectii) {
        delete s;
    }
    for (auto& pac : pacienti) {
        delete pac;
    }
    for (auto& r : retete) {
        delete r;
    }

    personal.clear();
    sectii.clear();
    pacienti.clear();
    retete.clear();
    std::cout << "Spitalul " << numeSpital << " a dat faliment!\n";
}