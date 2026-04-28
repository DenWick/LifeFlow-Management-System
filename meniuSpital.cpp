#include "meniuSpital.h"
#include "medic.h"
#include "rezident.h"
#include "asistent.h"
#include "consultatie.h"
#include "interventie.h"
#include "reteta.h"
#include "sectie.h"
#include <iostream>
#include <string>

// Constructor pentru meniuSpital
meniuSpital::meniuSpital() : spitalulMeu("Spitalul judetean") {} 

// Metoda pentru afișarea meniului
void meniuSpital::afisareMeniu() const {
    std::cout<<" ---------- SISTEM GESTIUNE SPITAL ---------- "<<std::endl;
    std::cout<<"1. Adauga personal spital"<<std::endl;
    std::cout<<"2. Adauga pacient"<<std::endl;
    std::cout<<"3. Afiseaza raport general"<<std::endl;
    std::cout<<"4. Modifica salariu medic"<<std::endl;
    std::cout<<"5. Sterge pacient"<<std::endl;
    std::cout<<"6. Adauga sectie"<<std::endl;
    std::cout<<"7. Adauga reteta"<<std::endl;
    std::cout<<"8. Adauga consultatie"<<std::endl;
    std::cout<<"0. Iesire"<<std::endl;
    std::cout<<"--------------------------------------------- "<<std::endl;
    std::cout<<"Alege o optiune: ";
}

// Functia de rulare a meniului
void meniuSpital::ruleaza() {
    int optiune = -1;
    while (true) { 
        afisareMeniu();
        
        if (!(std::cin >> optiune)) {
            break; 
        }

        try {
            //Iesire din sistem
            if (optiune == 0) {
                std::cout << "Iesire din sistem..." << std::endl;
                break;
            }

            // Adaugare personal
            if (optiune == 1) {
                std::cout << "Ce doriti sa adaugati?\n";
                std::cout << "1. Medic\n2. Asistent\n3. Rezident\n";
                int tip; std::cin >> tip;

                std::string nume, prenume;
                std::cout << "Nume: "; std::cin >> nume >> prenume;

                if (tip == 1) {
                    std::string spec;
                    std::string functie = "Medic";
                    int sal;
                    std::cout << "Specializare: "; std::cin >> spec;
                    std::cout << "Salariu: "; std::cin >> sal;
                    // Upcasting automat: Medic* devine personalSpital*
                    spitalulMeu.adaugaPersonal(new medic(nume, prenume, functie, spec, sal));
                } 
                else if (tip == 2) {
                    std::string sectie;
                    std::string functie = "Asistent";
                    std::cout << "Sectie: "; std::cin >> sectie;
                    spitalulMeu.adaugaPersonal(new asistent(nume, prenume, functie, sectie, "08:00-16:00"));
                } 
                else if (tip == 3) {
                    std::string spec, sectie;
                    std::string functie = "Rezident";
                    int an;
                    std::cout << "Specializare: "; std::cin >> spec;
                    std::cout << "Sectie: "; std::cin >> sectie;
                    std::cout << "An rezidentiat: "; std::cin >> an;
                    // Rezident moștenește de la ambele, deci e și personalSpital
                    spitalulMeu.adaugaPersonal(new rezident(nume, prenume, functie, spec, 5000, sectie, "08:00", an));
                }
                std::cout << "Adaugat cu succes!\n";
            }
            // Adaugare pacient
            else if(optiune == 2){
                std::string nume;
                std::string prenume;
                int varsta;
                std::cout << "Nume pacient: "; std::cin >> nume >> prenume;
                std::cout << "Varsta pacient: "; std::cin >> varsta;

                spitalulMeu.adaugaPacient(new pacient(nume, prenume, varsta));
                std::cout << "Pacient adaugat cu succes!\n";
            }
            // Afisare raport general
            else if(optiune == 3){
                spitalulMeu.afisare();
            }
            // Modificare salariu medic
            else if(optiune == 4){
                int idDeCautat, salariuNou;
                std::cout << "Introduceti ID-ul medicului: ";
                std::cin >> idDeCautat;
                std::cout << "Introduceti noul salariu: ";
                std::cin >> salariuNou;

                try {
                    spitalulMeu.modificaSalariuMedic(idDeCautat, salariuNou);
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
            // Stergere pacient
            else if(optiune == 5){
                std::string numePacient;
                std::string prenumePacient;
                std::cout << "Nume pacient de sters: "; std::cin >> numePacient;
                spitalulMeu.stergePacient(numePacient, prenumePacient);
                std::cout << "Pacient sters cu succes!\n";
            }
            // Adaugare sectie
            else if(optiune == 6){
                std::string numeSectie;
                std::cout << "Nume sectie: "; std::cin >> numeSectie;
                sectie* s = new sectie(numeSectie);

                std::string numeMedic, prenumeMedic, spec;
                int sal;
                std::cout << "Adauga un medic in sectie.\n";
                std::cout << "Nume medic: "; std::cin >> numeMedic;
                std::cout << "Prenume medic: "; std::cin >> prenumeMedic;
                std::cout << "Specializare: "; std::cin >> spec;
                std::cout << "Salariu: "; std::cin >> sal;
                s->adaugaMedic(new medic(numeMedic, prenumeMedic,"Medic" , spec, sal));

                spitalulMeu.adaugaSectie(s);
                std::cout << "Sectie adaugata cu succes!\n";
            }
            // Adaugare reteta
            else if(optiune == 7){
                std::string denumire;
                std::cout << "Denumire reteta: "; std::cin >> denumire;
                reteta* r = new reteta(denumire);

                std::string medicament;
                std::cout << "Adauga un medicament: "; std::cin >> medicament;
                r->adaugaMedicament(medicament);

                spitalulMeu.adaugaReteta(r);
                std::cout << "Reteta adaugata cu succes!\n";
            }
            // Adaugare consultatie
            else if(optiune == 8){
                std::string data, ora, numeMedic, numePacient;
                std::cout << "Data consultatie: "; std::cin >> data;
                std::cout << "Ora consultatie: "; std::cin >> ora;
                std::cout << "Nume medic: "; std::cin >> numeMedic;
                std::cout << "Nume pacient: "; std::cin >> numePacient;

                consultatie c(data, ora, numeMedic, numePacient);
                std::cout << "Consultatie programata: " << c.get_data() << " la ora " 
                          << c.get_ora() << " | Medic: " << c.get_nume_medic() 
                          << " | Pacient: " << c.get_nume_pacient() << "\n";
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }
    }
}