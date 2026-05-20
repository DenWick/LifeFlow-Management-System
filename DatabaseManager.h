#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>
#include "personalSpital.h"
#include "pacient.h"
#include "consultatie.h"
#include "reteta.h"
#include "sectie.h"

class DatabaseManager {
    private:
        SQLite::Database db;

    public:
        DatabaseManager(const std::string& dbPath);

        void creareTabele();

        void salveazaPersonal(const std::vector<personalSpital*>& lista);

        void stergePacientDinDB(const std::string& nume, const std::string& prenume);

        void actualizeazaSalariuMedicInDB(int idMedic, int salariuNou);

        void stergeConsultatieDinDB(const std::string& nume_medic, const std::string& prenume_medic, const std::string& nume_pacient, const std::string& prenume_pacient, const std::string& data, const std::string& ora);

        void salveazaTotSpitalul(
        const std::vector<personalSpital*>& pers,
        const std::vector<pacient*>& pac,
        const std::vector<consultatie*>& cons,
        const std::vector<reteta*>& ret,
        const std::vector<sectie*>& sec
        );
        
        std::vector<personalSpital*> incarcaPersonal();
        std::vector<pacient*> incarcaPacienti();
        std::vector<consultatie*> incarcaConsultatii();
        std::vector<sectie*> incarcaSectii();
        std::vector<reteta*> incarcaRetete();
};