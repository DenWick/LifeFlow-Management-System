#pragma once
#include <string>
#include <iostream>

class personalSpital {
    private:
        static int idCounter;
        int id;
        std::string nume;
        std::string functie;
        std::string prenume;
    public:
        personalSpital(const std::string& n, const std::string& p, const std::string& f);

        int getId() const { return id; }
        
        virtual void afisare() const = 0;

        virtual ~personalSpital() {}
};