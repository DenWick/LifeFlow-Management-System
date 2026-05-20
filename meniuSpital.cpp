#include "meniuSpital.h"
#include "medic.h"
#include "rezident.h"
#include "asistent.h"
#include "consultatie.h"
#include "interventie.h"
#include "reteta.h"
#include "sectie.h"
#include "DatabaseManager.h"
#include "personalFactory.h"
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
void meniuSpital::ruleaza(DatabaseManager& db) {
    optiune = -1;

    for (auto* x : db.incarcaPersonal())    spitalulMeu.adaugaPersonal(x);
    for (auto* x : db.incarcaPacienti())    spitalulMeu.adaugaPacient(x);
    for (auto* x : db.incarcaConsultatii()) spitalulMeu.adaugaConsultatie(x);
    for (auto* x : db.incarcaSectii())      spitalulMeu.adaugaSectie(x);
    for (auto* x : db.incarcaRetete())      spitalulMeu.adaugaReteta(x);

    while (true) {
        afisareMeniu();
        std::cin >> optiune;

        if (optiune == 0) {
            std::cout << "Se salveaza datele in baza de date...\n";

            db.salveazaTotSpitalul(
                spitalulMeu.getPersonal(),
                spitalulMeu.getPacienti(),
                spitalulMeu.getConsultatii(),
                spitalulMeu.getRetete(),
                spitalulMeu.getSectii()
            );
            
            std::cout << "Iesire din program. La revedere!\n";
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
                std::cout << "Nume si Prenume: "; 
                std::cin >> nume >> prenume;

                if (tip == 1) {
                    std::string spec; int sal;
                    std::cout << "Specializare: "; std::cin >> spec;
                    std::cout << "Salariu: "; std::cin >> sal;
                    
                    personalSpital* m = PersonalFactory::creeazaMedic(nume, prenume, spec, sal);
                    spitalulMeu.adaugaPersonal(m);
                } 
                else if (tip == 2) {
                    std::string sectie;
                    std::cout << "Sectie: "; std::cin >> sectie;
                    
                    personalSpital* a = PersonalFactory::creeazaAsistent(nume, prenume, sectie);
                    spitalulMeu.adaugaPersonal(a);
                } 
                else if (tip == 3) {
                    std::string spec, sectie; int an;
                    std::cout << "Specializare: "; std::cin >> spec;
                    std::cout << "Sectie: "; std::cin >> sectie;
                    std::cout << "An rezidentiat: "; std::cin >> an;
                    
                    personalSpital* r = PersonalFactory::creeazaRezident(nume, prenume, spec, sectie, an);
                    spitalulMeu.adaugaPersonal(r);
                }
                std::cout << "Angajatul a fost adaugat cu succes!\n";
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
                std::cout << "Prenume pacient de sters: "; std::cin >> prenumePacient;
                spitalulMeu.stergePacient(numePacient, prenumePacient);
                db.stergePacientDinDB(numePacient, prenumePacient);
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
            else if(optiune == 7) {
                std::string denumire;
                int numar_medicamente;

                std::cin.ignore();

                std::cout << "Denumire reteta: ";
                std::getline(std::cin, denumire);

                std::cout << "Numar medicamente care alcatuiesc reteta: "; std::cin >> numar_medicamente;

                std::cin.ignore();
                
                reteta* r = new reteta(denumire);

                for (int i = 0 ; i < numar_medicamente; i++) {
                    std::string medicament;
                    std::cout << "Adauga medicamentul " << ( i + 1 ) << ": ";

                    std::getline(std::cin, medicament);
                    r->adaugaMedicament(medicament);
                }

                spitalulMeu.adaugaReteta(r);
                std::cout << "Reteta adaugata cu succes!\n";
            }
            // Adaugare consultatie
            else if(optiune == 8){
                std::string data, ora, numeMedic, prenumeMedic, numePacient, prenumePacient;
                std::cout << "Data consultatie: "; std::cin >> data;
                std::cout << "Ora consultatie: "; std::cin >> ora;
                std::cout << "Nume medic: "; std::cin >> numeMedic;
                std::cout << "Prenume medic: "; std::cin >> prenumeMedic;
                std::cout << "Nume pacient: "; std::cin >> numePacient;
                std::cout << "Prenume pacient: "; std::cin >> prenumePacient;

                consultatie* c = new consultatie(data, ora, numeMedic, prenumeMedic, numePacient, prenumePacient);
                std::cout << "Consultatie programata: " << c->get_data() << " la ora "
                          << c->get_ora() << " | Medic: " << c->get_nume_medic() << " " << c->get_prenume_medic()
                          << " | Pacient: " << c->get_nume_pacient() << " " << c->get_prenume_pacient() << "\n";
                spitalulMeu.adaugaConsultatie(c);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }
    }
}

int meniuSpital::getOptiune() const {
    return optiune;
}