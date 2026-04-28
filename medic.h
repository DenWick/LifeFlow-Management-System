#pragma once
#include "personalSpital.h"
#include <string>

class medic : virtual public personalSpital {
    protected:
        std::string specializare;
        int salariu;
    public:
        medic(const std::string& n,const std::string& p, const std::string& f, const std::string& s, int sal);

        void afisare() const override;

        void setSalariu(int sal) { salariu = sal; }

        virtual ~medic() {}
};