#pragma once
#include <string>
#include <iostream>

class pacient {
    private:
        std::string nume;
        std::string prenume;
        int varsta;
    public:
        pacient(const std::string& n,const std::string& pre, const int v);
        std::string get_nume() const;
        std::string get_prenume() const;
        void afisare() const;
};