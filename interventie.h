#pragma once 
#include <string>
#include <iostream>
#include "consultatie.h"

class interventie : public consultatie {
    private:
        std::string sectie;
    public:
        interventie(const std::string& data, const std::string& ora, const std::string& nume_medic, const std::string& prenume_medic, const std::string& nume_pacient, const std::string& prenume_pacient, const std::string& sectie);
        std::string get_sectie() const;
    };
