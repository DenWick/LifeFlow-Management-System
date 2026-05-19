#pragma once
#include <string>
#include <iostream>

class personalSpital {
    private:
        static int idCounter;
        int id;
        std::string nume;
        std::string prenume;
        std::string functie;
    public:
        personalSpital(const std::string& n, const std::string& p, const std::string& f);

        int getId() const { return id; }
        void setId(int idNou) { id = idNou; }

        std::string getNume() const { return nume; }
        std::string getPrenume() const { return prenume; }
        std::string getFunctie() const { return functie; }
        
        virtual void afisare() const = 0;

        virtual ~personalSpital() {}
};