#include "pacient.h"

// Constructorul clasei Pacient
pacient::pacient(const std::string& n,const std::string& pre, const int v) : nume(n), prenume(pre), varsta(v) {}

// Metoda pentru obținerea numelui pacientului
std::string pacient::get_nume() const {
    return nume;
}

// Metoda pentru obținerea prenumelui pacientului
std::string pacient::get_prenume() const {
    return prenume;
}

// Metoda pentru afișarea informațiilor despre pacient
void pacient::afisare() const {
    std::cout << "| Nume: " << nume << " " << prenume << " | Varsta: " << varsta << std::endl;
}