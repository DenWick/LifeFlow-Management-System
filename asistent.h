#pragma once
#include <string>
#include <iostream>
#include "personalSpital.h"

class asistent : virtual public personalSpital {
    protected:
        std::string specializare;
        std::string oreLucru;
    public:
        asistent(const std::string& n,const std::string& pre, const std::string& f, const std::string& s, const std::string& p);

        void afisare() const override;
};