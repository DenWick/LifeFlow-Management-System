#pragma once
#include "personalSpital.h"
#include "medic.h"
#include "asistent.h"
#include "rezident.h"
#include <string>

class PersonalFactory {
public:
    static inline personalSpital* creeazaMedic(const std::string& nume, const std::string& prenume, const std::string& spec, int salariu) {
        return new medic(nume, prenume, "Medic", spec, salariu);
    }
    
    static inline personalSpital* creeazaAsistent(const std::string& nume, const std::string& prenume, const std::string& sectie) {
        return new asistent(nume, prenume, "Asistent", sectie, "08:00-16:00");
    }
    
    static inline personalSpital* creeazaRezident(const std::string& nume, const std::string& prenume, const std::string& spec, const std::string& sectie, int an) {
        return new rezident(nume, prenume, "Rezident", spec, 5000, sectie, "08:00", an);
    }
};