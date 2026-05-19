#pragma once
#include <string>
#include <iostream>
#include <vector>

class reteta {
    private:
        int idReteta;
        static int contorRetete;
        std::string denumire;
        std::vector<std::string> medicamente;
    public:
        explicit reteta(const std::string& denumire);
        reteta(const reteta& alta);
        reteta& operator=(const reteta& alta);
        void adaugaMedicament(const std::string& medicament);
        void afiseaza() const;

        int getIdReteta() const { return idReteta; }
        std::string getDenumire() const { return denumire; }
        const std::vector<std::string>& getMedicamente() const { return medicamente; }

        ~reteta();
};