#pragma once 
#include <string>
#include <vector>
#include "medic.h"

class sectie {
    private:
        std::string nume;
        std::vector<medic*> medici;
    public:
        explicit sectie(const std::string& n);
        void adaugaMedic(medic* m);
        void afisare() const;

        std::string get_nume() const { return nume; }
        const std::vector<medic*>& getMedici() const { return medici; }

        ~sectie();
};