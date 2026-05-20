#include "DatabaseManager.h"
#include "medic.h"
#include "asistent.h"
#include "rezident.h"
#include "pacient.h"
#include "consultatie.h"
#include "reteta.h"
#include "sectie.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbPath) 
    : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    std::cout << "[DB] Conexiune la baza de date stabilita cu succes!\n";
}
void DatabaseManager::creareTabele() {
    try {
        // Tabel medici
        db.exec("CREATE TABLE IF NOT EXISTS Medici ("
                "id INTEGER PRIMARY KEY, "
                "nume TEXT, prenume TEXT, functie TEXT, specializare TEXT, salariu INTEGER)");

        // Tabel asistenti
        db.exec("CREATE TABLE IF NOT EXISTS Asistenti ("
                "id INTEGER PRIMARY KEY, "
                "nume TEXT, prenume TEXT, functie TEXT, specializare TEXT, ore_lucru TEXT)");
        
        // Tabel rezidenti
        db.exec("CREATE TABLE IF NOT EXISTS Rezidenti ("
                "id INTEGER PRIMARY KEY, "
                "nume TEXT, prenume TEXT, functie TEXT, specializare TEXT, salariu INTEGER, ore_lucru TEXT, an_rezidentiat INTEGER)");
        
        // Tabel angajati        
        db.exec("CREATE VIEW IF NOT EXISTS Tabel_Personal AS "
                "SELECT id, nume, prenume, functie, specializare FROM Medici "
                "UNION "
                "SELECT id, nume, prenume, functie, specializare FROM Asistenti "
                "UNION "
                "SELECT id, nume, prenume, functie, specializare FROM Rezidenti");
        
        // Tabel pacienti
        db.exec("CREATE TABLE IF NOT EXISTS Pacienti (id INTEGER PRIMARY KEY AUTOINCREMENT, nume TEXT, prenume TEXT, varsta INTEGER)");
        
        // Tabel consultatii
        db.exec("CREATE TABLE IF NOT EXISTS Consultatii (id INTEGER PRIMARY KEY AUTOINCREMENT, data TEXT, ora TEXT, nume_medic TEXT, prenume_medic TEXT, nume_pacient TEXT, prenume_pacient TEXT)");
        
        // Tabel sectii
        db.exec("CREATE TABLE IF NOT EXISTS Sectii (id INTEGER PRIMARY KEY AUTOINCREMENT, nume_sectie TEXT)");
        
        // Tabel retete
        db.exec("CREATE TABLE IF NOT EXISTS Retete (id INTEGER PRIMARY KEY, denumire TEXT, medicamente_text TEXT)");

        std::cout << "[DB] Tabelele si View-ul central au fost create cu succes.\n";
    } catch (std::exception& e) {
        std::cout << "[DB] Eroare la crearea tabelelor: " << e.what() << "\n";
    }
}

void DatabaseManager::salveazaPersonal(const std::vector<personalSpital*>& lista) {
    try {
        db.exec("DELETE FROM Medici");
        db.exec("DELETE FROM Asistenti");
        db.exec("DELETE FROM Rezidenti");

        for (auto* angajat : lista) {
            rezident* rez = dynamic_cast<rezident*>(angajat);
            if (rez != nullptr) {
                SQLite::Statement query(db, "INSERT INTO Rezidenti (id, nume, prenume, functie, specializare, salariu, ore_lucru, an_rezidentiat) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                query.bind(1, rez->getId());
                query.bind(2, rez->getNume());
                query.bind(3, rez->getPrenume());
                query.bind(4, rez->getFunctie());
                query.bind(5, rez->medic::getSpecializare());
                query.bind(6, rez->getSalariu());
                query.bind(7, rez->getOreLucru());
                query.bind(8, rez->getAn());
                query.exec();
                continue; 
            }

            medic* med = dynamic_cast<medic*>(angajat);
            if (med != nullptr) {
                SQLite::Statement query(db, "INSERT INTO Medici (id, nume, prenume, functie, specializare, salariu) VALUES (?, ?, ?, ?, ?, ?)");
                query.bind(1, med->getId());
                query.bind(2, med->getNume());
                query.bind(3, med->getPrenume());
                query.bind(4, med->getFunctie());
                query.bind(5, med->getSpecializare());
                query.bind(6, med->getSalariu());
                query.exec();
                continue;
            }

            asistent* asis = dynamic_cast<asistent*>(angajat);
            if (asis != nullptr) {
                SQLite::Statement query(db, "INSERT INTO Asistenti (id, nume, prenume, functie, specializare, ore_lucru) VALUES (?, ?, ?, ?, ?, ?)");
                query.bind(1, asis->getId());
                query.bind(2, asis->getNume());
                query.bind(3, asis->getPrenume());
                query.bind(4, asis->getFunctie());
                query.bind(5, asis->getSpecial());
                query.bind(6, asis->getOreLucru());
                query.exec();
                continue;
            }
        }
        std::cout << "[DB] Datele si ID-urile au fost salvate cu succes!\n";
    } catch (std::exception& e) {
        std::cout << "[DB] Eroare la salvare: " << e.what() << "\n";
    }
}

std::vector<personalSpital*> DatabaseManager::incarcaPersonal() {
    std::vector<personalSpital*> listaIncarcata;

    try {
        // Incarcam medicii
        SQLite::Statement queryMedici(db, "SELECT id, nume, prenume, functie, specializare, salariu FROM Medici");
        while (queryMedici.executeStep()) {
            int id = queryMedici.getColumn(0).getInt();
            std::string nume = queryMedici.getColumn(1).getString();
            std::string prenume = queryMedici.getColumn(2).getString();
            std::string functie = queryMedici.getColumn(3).getString();
            std::string specializare = queryMedici.getColumn(4).getString();
            int salariu = queryMedici.getColumn(5).getInt();
            
            medic* m = new medic(nume, prenume, functie, specializare, salariu);
            m->setId(id);
            listaIncarcata.push_back(m);
        }

        // Incarcam asistentii
        SQLite::Statement queryAsis(db, "SELECT id, nume, prenume, functie, specializare, ore_lucru FROM Asistenti");
        while (queryAsis.executeStep()) {
            int id = queryAsis.getColumn(0).getInt();
            std::string nume = queryAsis.getColumn(1).getString();
            std::string prenume = queryAsis.getColumn(2).getString();
            std::string functie = queryAsis.getColumn(3).getString();
            std::string specializare = queryAsis.getColumn(4).getString();
            std::string ore_lucru = queryAsis.getColumn(5).getString();

            asistent* a = new asistent(nume, prenume, functie, specializare, ore_lucru);
            a->setId(id);
            listaIncarcata.push_back(a);
        }

        // Incarcam rezidentii
        SQLite::Statement queryRez(db, "SELECT id, nume, prenume, functie, specializare, salariu, ore_lucru, an_rezidentiat FROM Rezidenti");
        while (queryRez.executeStep()) {
            int id = queryRez.getColumn(0).getInt();
            std::string nume = queryRez.getColumn(1).getString();
            std::string prenume = queryRez.getColumn(2).getString();
            std::string functie = queryRez.getColumn(3).getString();
            std::string specializare = queryRez.getColumn(4).getString();
            int salariu = queryRez.getColumn(5).getInt();
            std::string ore_lucru = queryRez.getColumn(6).getString();
            int an_rezidentiat = queryRez.getColumn(7).getInt();

            rezident* r = new rezident(nume, prenume, functie, specializare, salariu, specializare, ore_lucru, an_rezidentiat);
            r->setId(id);
            listaIncarcata.push_back(r);
        }
    } catch (std::exception& e) {
        std::cout << "[DB] Eroare la incarcare: " << e.what() << "\n";
    }

    return listaIncarcata;
}

void DatabaseManager::salveazaTotSpitalul(
    const std::vector<personalSpital*>& pers,
    const std::vector<pacient*>& pac,
    const std::vector<consultatie*>& cons,
    const std::vector<reteta*>& ret,
    const std::vector<sectie*>& sec) 
{
    try {
        salveazaPersonal(pers);

        // Salvare Pacienti
        db.exec("DELETE FROM Pacienti");
        db.exec("DELETE FROM sqlite_sequence WHERE name='Pacienti'");
        for (auto* p : pac) {
            SQLite::Statement q(db, "INSERT INTO Pacienti (nume, prenume, varsta) VALUES (?, ?, ?)");
            q.bind(1, p->get_nume());
            q.bind(2, p->get_prenume());
            q.bind(3, p->get_varsta());
            q.exec();
        }

        // Salvare Consultatii
        db.exec("DELETE FROM Consultatii");
        db.exec("DELETE FROM sqlite_sequence WHERE name='Consultatii'");
        for (auto* c : cons) {
            SQLite::Statement q(db, "INSERT INTO Consultatii (data, ora, nume_medic, prenume_medic, nume_pacient, prenume_pacient) VALUES (?, ?, ?, ?, ?, ?)");
            q.bind(1, c->get_data());
            q.bind(2, c->get_ora());
            q.bind(3, c->get_nume_medic());
            q.bind(4, c->get_prenume_medic());
            q.bind(5, c->get_nume_pacient());
            q.bind(6, c->get_prenume_pacient());
            q.exec();
        }

        // Salvare Sectii
        db.exec("DELETE FROM Sectii");
        db.exec("DELETE FROM sqlite_sequence WHERE name='Sectii'");
        for (auto* s : sec) {
            SQLite::Statement qSec(db, "INSERT INTO Sectii (nume_sectie) VALUES (?)");
            qSec.bind(1, s->get_nume());
            qSec.exec();

        }

        // Salvare Retete
        db.exec("DELETE FROM Retete");
        for (auto* r : ret) {
            std::string medText = "";
            for (const auto& m : r->getMedicamente()) {
                medText += m + ",";
            }
            SQLite::Statement q(db, "INSERT INTO Retete (id, denumire, medicamente) VALUES (?, ?, ?)");
            q.bind(1, r->getIdReteta());
            q.bind(2, r->getDenumire());
            q.bind(3, medText);
            q.exec();
        }
        std::cout << "[DB] Toate datele spitalului au fost salvate cu succes la iesire!\n";
    } catch (std::exception& e) {
        std::cout << "[DB] Eroare la salvarea globala: " << e.what() << "\n";
    }
}

void DatabaseManager::stergePacientDinDB(const std::string& nume, const std::string& prenume) {
    try {
        SQLite::Statement query(db, "DELETE FROM Pacienti WHERE nume = ? AND prenume = ?");
        query.bind(1, nume);
        query.bind(2, prenume);
        query.exec();
        std::cout << "[DB] Pacientul a fost sters direct si din tabelul SQL!\n";
    } catch (std::exception& e) {
        std::cout << "[DB] Eroare la stergerea din baza de date: " << e.what() << "\n";
    }
}

void DatabaseManager::stergeConsultatieDinDB(const std::string& nume_medic, const std::string& prenume_medic, const std::string& nume_pacient, const std::string& prenume_pacient, const std::string& data, const std::string& ora) {
    try {
        SQLite::Statement query(db, "DELETE FROM Consultatii WHERE nume_medic = ? AND prenume_medic = ? AND nume_pacient = ? AND prenume_pacient = ? AND data = ? AND ora = ?");
        query.bind(1, nume_medic);
        query.bind(2, prenume_medic);
        query.bind(3, nume_pacient);
        query.bind(4, prenume_pacient);
        query.bind(5, data);
        query.bind(6, ora);
        query.exec();
        std::cout << "[DB] Consultatia a fost stearsa cu succes din baza de date!\n";
    } catch (std::exception& e) {
        std::cout << "[DB] Eroare la stergerea din baza de date: " << e.what() << "\n";
    }
}


std::vector<pacient*> DatabaseManager::incarcaPacienti() {
    std::vector<pacient*> lista;
    try {
        SQLite::Statement q(db, "SELECT nume, prenume, varsta FROM Pacienti");
        while (q.executeStep()) {
            lista.push_back(new pacient(q.getColumn(0).getString(), q.getColumn(1).getString(), q.getColumn(2).getInt()));
        }
    } catch(...) {}
    return lista;
}

std::vector<consultatie*> DatabaseManager::incarcaConsultatii() {
    std::vector<consultatie*> lista;
    try {
        SQLite::Statement q(db, "SELECT data, ora, nume_medic, prenume_medic, nume_pacient, prenume_pacient FROM Consultatii");
        while (q.executeStep()) {
            lista.push_back(new consultatie(q.getColumn(0).getString(), q.getColumn(1).getString(), q.getColumn(2).getString(), q.getColumn(3).getString(), q.getColumn(4).getString(), q.getColumn(5).getString()));
        }
    } catch(...) {}
    return lista;
}

std::vector<sectie*> DatabaseManager::incarcaSectii() {
    std::vector<sectie*> lista;
    try {
        SQLite::Statement q(db, "SELECT nume_sectie FROM Sectii");
        while (q.executeStep()) {
            std::string numeSectie = q.getColumn(0).getString();
            sectie* s = new sectie(numeSectie);
            lista.push_back(s);
        }
    } catch(...) {}
    return lista;
}

#include <sstream>
std::vector<reteta*> DatabaseManager::incarcaRetete() {
    std::vector<reteta*> lista;
    try {
        SQLite::Statement q(db, "SELECT denumire, medicamente_text FROM Retete");
        while (q.executeStep()) {
            reteta* r = new reteta(q.getColumn(0).getString());
            std::string medText = q.getColumn(1).getString();
            
            std::stringstream ss(medText);
            std::string med;
            while (std::getline(ss, med, ',')) {
                if (!med.empty()) r->adaugaMedicament(med);
            }
            lista.push_back(r);
        }
    } catch(...) {}
    return lista;
}

void DatabaseManager::actualizeazaSalariuMedicInDB(int idMedic, int salariuNou) {
    try {
        SQLite::Statement updateMedici(db, "UPDATE Medici SET salariu = ? WHERE id = ?");
        updateMedici.bind(1, salariuNou);
        updateMedici.bind(2, idMedic);
        updateMedici.exec();

        SQLite::Statement updateRezidenti(db, "UPDATE Rezidenti SET salariu = ? WHERE id = ?");
        updateRezidenti.bind(1, salariuNou);
        updateRezidenti.bind(2, idMedic);
        updateRezidenti.exec();
        
        std::cout << "[DB] Salariu actualizat cu succes în baza de date!\n";
    } catch (std::exception& e) {
        std::cerr << "[DB] Eroare la actualizarea salariului: " << e.what() << "\n";
    }
}