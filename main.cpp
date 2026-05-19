// Asigura-te ca ai aceste include-uri sus
#include "DatabaseManager.h"
#include "meniuSpital.h"

int main() {
    // Pornim baza de date
    DatabaseManager db("spitalul_meu.db");
    db.creareTabele();

    // Pornim meniul si ii pasam baza de date
    meniuSpital meniu;
    meniu.ruleaza(db);

    return 0;
}