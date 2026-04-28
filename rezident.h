#pragma once
#include <string>
#include <iostream>
#include "medic.h"
#include "asistent.h"

class rezident: virtual public medic, virtual public asistent {
    private:
        int anRezidentiat;
    public:
        rezident(const std::string& n,const std::string& pre, const std::string& f, const std::string& s, int sal, const std::string& sp, const std::string& p, int an);

        void afisare() const override;

        virtual ~rezident() {}
};

