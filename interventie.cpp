#include "interventie.h"

// Constructorul clasei interventie
interventie::interventie(const std::string& data, const std::string& ora, const std::string& nume_medic, const std::string& nume_pacient, const std::string& s) : 
consultatie(data, ora, nume_medic, nume_pacient), 
sectie(s) {}

std::string interventie::get_sectie() const {
    return sectie;
}