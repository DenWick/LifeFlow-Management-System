#pragma once
#include "spital.h"

class DatabaseManager;
class meniuSpital {
    private:
        spital spitalulMeu;
        void afisareMeniu() const;
        int optiune;
    public:
    int getOptiune() const;
        meniuSpital();
        void ruleaza(DatabaseManager& db);
        ~meniuSpital() = default;
};