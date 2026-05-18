#pragma once
#include "spital.h"

class meniuSpital {
    private:
        spital spitalulMeu;
        void afisareMeniu() const;
        int optiune;
    public:
    int getOptiune() const;
        meniuSpital();
        void ruleaza();
        ~meniuSpital() = default;
};