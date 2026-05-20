#pragma once
#include <vector>
#include <string>
#include "sectie.h"
#include "personalSpital.h"
#include "reteta.h"
#include "pacient.h"
#include "consultatie.h"
#include "repository.h"
#include "observer.h"

class spital {
    protected:
        std::string numeSpital;
        repository<personalSpital> personal;
        repository<sectie> sectii;
        repository<pacient> pacienti;
        repository<reteta> retete;
        repository<consultatie> consultatii;
        std::vector<IObserver*> observatori;
        
    public:
        explicit spital(const std::string& n);

        void ataseazaObservator(IObserver* obs) {
            observatori.push_back(obs);
        }
        void notifica(const std::string& mesaj) {
            for( auto* obs : observatori) {
                obs -> onEvent(mesaj);
            }
        }

        spital(const spital&) = delete;
        spital& operator=(const spital&) = delete;

        // Metode de adaugare
        void adaugaPersonal(personalSpital* p);
        void adaugaPacient(pacient* p);
        void adaugaSectie(sectie* s);
        void adaugaReteta(reteta* r);
        void adaugaConsultatie(consultatie* c);
        
        int getNumarPersonal() const;
        
        const std::vector<personalSpital*>& getPersonal() const;
        const std::vector<pacient*>& getPacienti() const;
        const std::vector<consultatie*>& getConsultatii() const;
        const std::vector<reteta*>& getRetete() const;
        const std::vector<sectie*>& getSectii() const;

        // Stergere pacient
        void stergePacient(const std::string& numePacient , std::string prenumePacient);

        // Modificare salariu medic
        void modificaSalariuMedic(int idCautat, int salariuNou);

        // Afisare informatii spital
        void afisare() const;

        ~spital();
};