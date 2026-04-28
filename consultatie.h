#pragma once
#include <string>
#include <iostream>

class consultatie  {
    private:
        std::string data;
        std::string ora;
        std::string nume_medic;
        std::string prenume_medic;
        std::string nume_pacient;
        std::string prenume_pacient;
    public:
        consultatie(const std::string& data, const std::string& ora, const std::string& nume_medic, const std::string& prenume_medic, const std::string& nume_pacient, const std::string& prenume_pacient);
        std::string get_data() const;
        std::string get_ora() const;
        std::string get_nume_medic() const;
        std::string get_prenume_medic() const;
        std::string get_nume_pacient() const;
        std::string get_prenume_pacient() const;
        virtual ~consultatie() = default;
};
        