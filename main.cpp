#include "DatabaseManager.h"
#include "meniuSpital.h"
#include "observer.h"

int main() {

    meniuSpital meniu;
    // Pornim baza de date
    DatabaseManager db("spitalul_meu.db");
    db.creareTabele();

    HospitalLogger* logger = new HospitalLogger();
    meniu.ataseazaLoggerLaSpital(logger);

    // Pornim meniul si ii pasam baza de date
    meniu.ruleaza(db);

    
    delete logger;
    return 0;
}