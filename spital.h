#pragma once
#include <vector>
#include <string>
#include "sectie.h"
#include "personalSpital.h"
#include "reteta.h"
#include "pacient.h"
#include "consultatie.h"

class spital {
    private:
        std::string numeSpital;
        std::vector<personalSpital*> personal;
        std::vector<sectie*> sectii;
        std::vector<pacient*> pacienti;
        std::vector<reteta*> retete;
        std::vector<consultatie*> consultatii;
    public:
        explicit spital(const std::string& n);

        // Metode de adaugare
        void adaugaPersonal(personalSpital* p);
        void adaugaPacient(pacient* p);
        void adaugaSectie(sectie* s);
        void adaugaReteta(reteta* r);
        void adaugaConsultatie(consultatie* c);
        int getNumarPersonal() const;

        // Stergere pacient
        void stergePacient(const std::string& numePacient , std::string prenumePacient);

        // Modificare salariu medic
        void modificaSalariuMedic(int idCautat, int salariuNou);

        // Afisare informatii spital
        void afisare() const;

        ~spital();
};