#pragma once
#include "spital.h"
#include "observer.h"

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
        void ataseazaLoggerLaSpital(IObserver* logger) {
            spitalulMeu.ataseazaObservator(logger);
        }
            ~meniuSpital() = default;
};