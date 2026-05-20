#include "spital.h"
#include "exceptiiSpital.h"
#include <iostream>

// Constructor
spital::spital(const std::string& n) : numeSpital(n) {}

// Metode de adaugare
void spital::adaugaPersonal(personalSpital* p) { 
    personal.adauga(p); 

}
void spital::adaugaSectie(sectie* s) { 
    sectii.adauga(s); 
}

void spital::adaugaPacient(pacient* p) {
    pacienti.adauga(p);
    notifica("Pacientul " + p->get_nume() + " " + p->get_prenume() + " a fost internat in spital.");
}

void spital::adaugaReteta(reteta* r) { 
    retete.adauga(r); 
}

void spital::adaugaConsultatie(consultatie* c) { 
    consultatii.adauga(c); 
}

// Gettere care acceseaza vectorul din interiorul template-ului
const std::vector<personalSpital*>& spital::getPersonal() const { return personal.getToate(); }
const std::vector<pacient*>& spital::getPacienti() const { return pacienti.getToate(); }
const std::vector<consultatie*>& spital::getConsultatii() const { return consultatii.getToate(); }
const std::vector<reteta*>& spital::getRetete() const { return retete.getToate(); }
const std::vector<sectie*>& spital::getSectii() const { return sectii.getToate(); }

// Stergere pacient
void spital::stergePacient(const std::string& numeCautat, std::string prenumeCautat) {
    bool gasit = false;
    for (auto* p : pacienti.getToate()) {
        if (p->get_nume() == numeCautat && p->get_prenume() == prenumeCautat) {
            pacienti.elimina(p);
            gasit = true;
            notifica("Pacientul " + numeCautat + " " + prenumeCautat + " a fost externat cu succes.");
            break; 
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
    for (const personalSpital* p : personal.getToate()) {
        p->afisare();
    }

    std::cout << "Sectii:\n";
    for (const sectie* s : sectii.getToate()) {
        s->afisare();
    }

    std::cout << "Pacienti:\n";
    for (const pacient* p : pacienti.getToate()) {
        p->afisare();
    }

    std::cout << "Retete:\n";
    for (const reteta* r : retete.getToate()) {
        r->afiseaza();
    }

    std::cout << "Consultatii:\n";
    for (const consultatie* c : consultatii.getToate()) {
        std::cout << "| Data: " << c->get_data() << " | Ora: " << c->get_ora()
                  << " | Medic: " << c->get_nume_medic() << " " << c->get_prenume_medic()
                  << " | Pacient: " << c->get_nume_pacient() << " " << c->get_prenume_pacient() << "\n";
    }
}

// Modificare salariu medic
void spital::modificaSalariuMedic(int idCautat, int salariuNou) {
    if (salariuNou < 0) {
        throw NegativeSalaryException();
    }

    bool gasit = false;

    for (auto p : personal.getToate()) {
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

// Getter pentru numarul de membrii din personal
int spital::getNumarPersonal() const {
    return personal.getToate().size();
}

// Destructor
spital::~spital() {
}