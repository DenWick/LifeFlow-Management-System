#include "consultatie.h"

// Constructorul clasei consultatie
consultatie::consultatie(const std::string& d, const std::string& o, const std::string& m, const std::string& pm, const std::string& p, const std::string& pp) : 
data(d), 
ora(o), 
nume_medic(m), 
prenume_medic(pm), 
nume_pacient(p), 
prenume_pacient(pp) {}

// Getters pentru a accesa atributele private ale clasei consultatie
std::string consultatie::get_data() const {
    return data;
}

std::string consultatie::get_ora() const {
    return ora;
}

std::string consultatie::get_nume_medic() const {
    return nume_medic;
}

std::string consultatie::get_prenume_medic() const {
    return prenume_medic;
}

std::string consultatie::get_nume_pacient() const {
    return nume_pacient;
}

std::string consultatie::get_prenume_pacient() const {
    return prenume_pacient;
}