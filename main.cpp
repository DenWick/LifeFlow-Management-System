#include "DatabaseManager.h"
#include "meniuSpital.h"
#include "observer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "personalFactory.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

class GUILogger : public IObserver {
public:
    std::vector<std::string> mesaje;
    void onEvent(const std::string& eveniment) override {
        mesaje.push_back("[NOTIFICARE] " + eveniment);
    }
};

int main() {

    meniuSpital meniu;
    spital spitalulMeu;
    
    // Pornim baza de date
    DatabaseManager db("spitalul_meu.db");
    db.creareTabele();

    for (auto* x : db.incarcaPersonal())    spitalulMeu.adaugaPersonal(x);
    for (auto* x : db.incarcaPacienti())    spitalulMeu.adaugaPacient(x);
    for (auto* x : db.incarcaConsultatii()) spitalulMeu.adaugaConsultatie(x);

    GUILogger* guiLogger = new GUILogger();
    spitalulMeu.ataseazaObservator(guiLogger);

    // Initializam GLFW
    if (!glfwInit()) {
        std::cerr << "Eroare la initializarea GLFW!\n";
        return -1;
    }

    // Setam versiunea de OpenGL
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Cream fereastra principala
    GLFWwindow* window = glfwCreateWindow(1280, 720, "LifeFlow-Management-System", nullptr, nullptr);
    if (!window) {
        std::cerr << "Eroare la crearea ferestrei!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initializam Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        
        // Deschidem fereastra principala fara margini si fara titlu (stil Dashboard)
        ImGui::Begin("Dashboard Spital", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

        // Meniul superior
        if (ImGui::BeginTabBar("MeniuSpital", ImGuiTabBarFlags_None)) {
            
            // Personal Spital
            if (ImGui::BeginTabItem("Personal Spital")) {

                ImGui::TextColored(ImVec4(0.87f, 1.0f, 0.6f, 1.0f), "Angajare Personal Nou");

                static char nume[64] = "";
                static char prenume[64] = "";
                static char spec[64] = "";
                static char sectie[64] = "";
                static int salariu = 5000;
                static int an_rezidentiat = 1;
                static int tipSelectat = 0;

                ImGui::InputText("Nume", nume, 64);
                ImGui::InputText("Prenume", prenume, 64);
                ImGui::Combo("Functie", &tipSelectat, "Medic\0Asistent\0Rezident\0");

                // Medic
                if (tipSelectat == 0) {
                    ImGui::InputText("Specializare", spec, 64);
                    ImGui::InputInt("Salariu", &salariu);
                } 
                // Asistent
                else if (tipSelectat == 1) {
                    ImGui::InputText("Sectie", sectie, 64);
                } 
                // Rezident
                else if (tipSelectat == 2) {
                    ImGui::InputText("Specializare", spec, 64);
                    ImGui::InputText("Sectie", sectie, 64);
                    ImGui::InputInt("An Rezidentiat", &an_rezidentiat);
                }

                if (ImGui::Button("Angajeaza", ImVec2(200, 30))) {
                    if (strlen(nume) > 0 && strlen(prenume) > 0) {
                        personalSpital* nou = nullptr;

                        if (tipSelectat == 0) {
                            nou = PersonalFactory::creeazaMedic(nume, prenume, spec, salariu);
                        } else if (tipSelectat == 1) {
                            nou = PersonalFactory::creeazaAsistent(nume, prenume, sectie);
                        } else if (tipSelectat == 2) {
                            nou = PersonalFactory::creeazaRezident(nume, prenume, spec, sectie, an_rezidentiat);
                        }
                        
                        if (nou) {
                            spitalulMeu.adaugaPersonal(nou);
                            
                            db.salveazaTotSpitalul(
                                spitalulMeu.getPersonal(), 
                                spitalulMeu.getPacienti(), 
                                spitalulMeu.getConsultatii(), 
                                spitalulMeu.getRetete(), 
                                spitalulMeu.getSectii()
                            );
                            
                            memset(nume, 0, 64); memset(prenume, 0, 64); 
                            memset(spec, 0, 64); memset(sectie, 0, 64);
                            salariu = 5000; an_rezidentiat = 1;
                        }
                    }
                }

                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Lista Angajati Existenti:");
                
                static int indexPersoanaSelectata = -1;
                static int salariuNou = 0;
                static bool deschidePopup = false;

                static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
                if (ImGui::BeginTable("TabelPersonal", 5, flags)) {
                    ImGui::TableSetupColumn("Nume");
                    ImGui::TableSetupColumn("Prenume");
                    ImGui::TableSetupColumn("Functie");
                    ImGui::TableSetupColumn("Salariu");
                    ImGui::TableSetupColumn("Actiuni");
                    ImGui::TableHeadersRow();

                    auto& lista = spitalulMeu.getPersonal();
                    for (size_t i = 0; i < lista.size(); i++) {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::Text("%s", lista[i]->getNume().c_str());
                        ImGui::TableSetColumnIndex(1); ImGui::Text("%s", lista[i]->getPrenume().c_str());
                        ImGui::TableSetColumnIndex(2); ImGui::Text("%s", lista[i]->getFunctie().c_str());

                        ImGui::TableSetColumnIndex(3);
                        int salariuCurent = lista[i] -> getSalariu();

                        if( salariuCurent > 0 ) {
                            ImGui::Text("%d RON", salariuCurent);
                        }
                        
                        ImGui::TableSetColumnIndex(4);
                        
                        std::string labelButon = "Modifica Salariu##" + std::to_string(i);
                        if (ImGui::Button(labelButon.c_str())) {
                            indexPersoanaSelectata = i;
                            salariuNou = 5000;
                            deschidePopup = true;
                        }
                    }
                    ImGui::EndTable();
                }

                //  Modificarea salariului
                if (deschidePopup) {
                    ImGui::OpenPopup("Modifica Salariu");
                    deschidePopup = false;
                }

                ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

                if (ImGui::BeginPopupModal("Modifica Salariu", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    ImGui::Text("Seteaza un salariu nou pentru angajatul selectat.\n\n");
                    ImGui::Separator();

                    ImGui::InputInt("Salariu Nou (RON)", &salariuNou);

                    ImGui::Spacing();
                    
                    if (ImGui::Button("Salveaza", ImVec2(120, 0))) {
                        auto& lista = spitalulMeu.getPersonal();
                        auto* angajat = lista[indexPersoanaSelectata];

                        int idAngajat = angajat->getId();

                        spitalulMeu.modificaSalariuMedic(idAngajat, salariuNou);

                        db.salveazaTotSpitalul(
                            spitalulMeu.getPersonal(), 
                            spitalulMeu.getPacienti(), 
                            spitalulMeu.getConsultatii(), 
                            spitalulMeu.getRetete(), 
                            spitalulMeu.getSectii()
                        );

                        if (guiLogger) {
                            guiLogger->onEvent("Salariul a fost actualizat din interfata grafica.");
                        }

                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SetItemDefaultFocus();
                    ImGui::SameLine();
                    
                    // Buton de anulare
                    if (ImGui::Button("Anuleaza", ImVec2(120, 0))) {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }

                ImGui::EndTabItem();
            }

            // Pacienti si consultatii
            if (ImGui::BeginTabItem("Evidenta Pacienti & Consultatii")) {

                ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "Formular Internare");
                
                static char numeP[64] = "";
                static char prenumeP[64] = "";
                static char afectiune[128] = "";
                static int varsta = 0;

                ImGui::InputText("Nume Pacient", numeP, 64);
                ImGui::InputText("Prenume Pacient", prenumeP, 64);
                ImGui::InputInt("Varsta", &varsta);

                if (ImGui::Button("Interneaza Pacient", ImVec2(200, 30))) {
                    if (strlen(numeP) > 0 && strlen(prenumeP) > 0) {
                        
                        pacient* pNou = new pacient(numeP, prenumeP, varsta);
                        spitalulMeu.adaugaPacient(pNou);
                        
                        // Salvam in baza de date
                        db.salveazaTotSpitalul(
                            spitalulMeu.getPersonal(), 
                            spitalulMeu.getPacienti(), 
                            spitalulMeu.getConsultatii(), 
                            spitalulMeu.getRetete(), 
                            spitalulMeu.getSectii()
                        );
                        
                        // Notificare Observer
                        if (guiLogger) {
                            guiLogger->onEvent("S-a internat pacientul " + std::string(numeP) + " " + std::string(prenumeP) + ".");
                        }

                        // Golim campurile
                        memset(numeP, 0, 64); memset(prenumeP, 0, 64); memset(afectiune, 0, 128);
                        varsta = 0;
                    }
                }

                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Pacienti Internati in Sectii:");
                
                static ImGuiTableFlags flagsPacienti = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
                
                if (ImGui::BeginTable("TabelPacienti", 3, flagsPacienti)) {
                    ImGui::TableSetupColumn("Nume");
                    ImGui::TableSetupColumn("Prenume");
                    ImGui::TableSetupColumn("Varsta");
                    ImGui::TableHeadersRow();

                    auto& listaPacienti = spitalulMeu.getPacienti();
                    
                    for (size_t i = 0; i < listaPacienti.size(); i++) {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::Text("%s", listaPacienti[i]->get_nume().c_str());
                        ImGui::TableSetColumnIndex(1); ImGui::Text("%s", listaPacienti[i]->get_prenume().c_str());
                        
                        ImGui::TableSetColumnIndex(2); ImGui::Text("%d ani", listaPacienti[i]->get_varsta());
                        
                        // Butonul de Externare
                        std::string labelButon = "Externeaza##" + std::to_string(i);
                        
                        // Punem o culoare rosiatica pe buton pentru a indica o actiune importanta
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));

                        bool butonExternareApasat = ImGui::Button(labelButon.c_str());

                        ImGui::PopStyleColor(3);
                        
                        if (butonExternareApasat) {
                            
                            std::string numeP = listaPacienti[i]->get_nume();
                            std::string prenumeP = listaPacienti[i]->get_prenume();
                            try {

                                spitalulMeu.stergePacient(numeP, prenumeP);

                                db.stergePacientDinDB(numeP, prenumeP);
                                
                                db.salveazaTotSpitalul(
                                    spitalulMeu.getPersonal(), 
                                    spitalulMeu.getPacienti(), 
                                    spitalulMeu.getConsultatii(), 
                                    spitalulMeu.getRetete(), 
                                    spitalulMeu.getSectii()
                                );
                            } catch (const std::exception& e) {
                                if(guiLogger) {
                                    guiLogger -> onEvent("Eroare la externare: " + std::string(e.what()));
                                }
                            }

                            break;
                        }
                    }
                    ImGui::EndTable();
                }
                
                // Consulatii
                ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.4f, 1.0f), "Programare Consultatie Noua");
                
                static int indexMedicSelectat = -1;
                static int indexPacientSelectat = -1;
                static char dataConsultatie[32] = "";
                static char oraConsultatie[16] = "";

                // Selectarea medicului
                auto& listaPersonal = spitalulMeu.getPersonal();
                std::string previewMedic = (indexMedicSelectat >= 0 && indexMedicSelectat < (int)listaPersonal.size())
                    ? listaPersonal[indexMedicSelectat]->getNume() + " " + listaPersonal[indexMedicSelectat]->getPrenume()
                    : "--- Alege Medic ---";

                if (ImGui::BeginCombo("Medic", previewMedic.c_str())) {
                   for (int i = 0; i < (int)listaPersonal.size(); i++) {
                        if (listaPersonal[i]->getFunctie() == "Medic") {
                            bool isSelected = (indexMedicSelectat == i);
                            std::string numeComplet = listaPersonal[i]->getNume() + " " + listaPersonal[i]->getPrenume();
                            if (ImGui::Selectable(numeComplet.c_str(), isSelected)) {
                                indexMedicSelectat = i;
                            }
                            if (isSelected) ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                // Selectarea pacientului
                auto& listaP = spitalulMeu.getPacienti();
                std::string previewPacient = (indexPacientSelectat >= 0 && indexPacientSelectat < (int)listaP.size())
                    ? listaP[indexPacientSelectat]->get_nume() + " " + listaP[indexPacientSelectat]->get_prenume()
                    : "--- Alege Pacient ---";

                if (ImGui::BeginCombo("Pacient", previewPacient.c_str())) {
                    for (int i = 0; i < (int)listaP.size(); i++) {
                        bool isSelected = (indexPacientSelectat == i);
                        std::string numeCompletP = listaP[i]->get_nume() + " " + listaP[i]->get_prenume();
                        if (ImGui::Selectable(numeCompletP.c_str(), isSelected)) {
                            indexPacientSelectat = i;
                        }
                        if (isSelected) ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                //  Data si ora
                ImGui::InputText("Data (DD.MM.YYYY)", dataConsultatie, 32);
                ImGui::InputText("Ora (HH:MM)", oraConsultatie, 16);

                if (ImGui::Button("Programeaza", ImVec2(200, 30))) {
                    if (indexMedicSelectat >= 0 && indexPacientSelectat >= 0 && strlen(dataConsultatie) > 0 && strlen(oraConsultatie) > 0) {
                        
                        auto* medicSelectat = listaPersonal[indexMedicSelectat];
                        auto* pacientSelectat = listaP[indexPacientSelectat];

                        consultatie* cNou = new consultatie(
                            dataConsultatie, 
                            oraConsultatie, 
                            medicSelectat->getNume(), 
                            medicSelectat->getPrenume(), 
                            pacientSelectat->get_nume(), 
                            pacientSelectat->get_prenume()
                        );
                        
                        spitalulMeu.adaugaConsultatie(cNou);
                        
                        db.salveazaTotSpitalul(
                            spitalulMeu.getPersonal(), spitalulMeu.getPacienti(), 
                            spitalulMeu.getConsultatii(), spitalulMeu.getRetete(), spitalulMeu.getSectii()
                        );
                        
                        if (guiLogger) {
                            guiLogger->onEvent("Consultatie fixata: " + std::string(dataConsultatie) + " la " + std::string(oraConsultatie));
                        }

                        indexMedicSelectat = -1; indexPacientSelectat = -1;
                        memset(dataConsultatie, 0, 32); memset(oraConsultatie, 0, 16);
                    }
                }

                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("Istoric Consultatii:");
                
                static ImGuiTableFlags flagsCons = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
                
                if (ImGui::BeginTable("TabelConsultatii", 5, flagsCons)) {
                    ImGui::TableSetupColumn("Medic");
                    ImGui::TableSetupColumn("Pacient");
                    ImGui::TableSetupColumn("Data");
                    ImGui::TableSetupColumn("Ora");
                    ImGui::TableSetupColumn("Actiune");
                    ImGui::TableHeadersRow();

                    auto& listaCons = spitalulMeu.getConsultatii();
                    
                    for (size_t i = 0; i < listaCons.size(); i++) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0); 
                        ImGui::Text("Dr. %s %s", listaCons[i]->get_nume_medic().c_str(), listaCons[i]->get_prenume_medic().c_str());
                        
                        ImGui::TableSetColumnIndex(1); 
                        ImGui::Text("%s %s", listaCons[i]->get_nume_pacient().c_str(), listaCons[i]->get_prenume_pacient().c_str());
                        
                        ImGui::TableSetColumnIndex(2); 
                        ImGui::Text("%s", listaCons[i]->get_data().c_str());
                        
                        ImGui::TableSetColumnIndex(3); 
                        ImGui::Text("%s", listaCons[i]->get_ora().c_str());
                        
                        ImGui::TableSetColumnIndex(4);
                        std::string lblButon = "Finalizeaza##" + std::to_string(i);
                        
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.7f, 0.3f, 1.0f));
                        bool btnApasat = ImGui::Button(lblButon.c_str());
                        ImGui::PopStyleColor();

                        if (btnApasat) {
                            
                            std::string nume_medic = listaCons[i]->get_nume_medic();
                            std::string prenume_medic = listaCons[i]->get_prenume_medic();
                            std::string nume_pacient = listaCons[i]->get_nume_pacient();
                            std::string prenume_pacient = listaCons[i]->get_prenume_pacient();
                            std::string data = listaCons[i]->get_data();
                            std::string ora = listaCons[i]->get_ora();

                            try {
                                spitalulMeu.stergeConsultatie(nume_medic, prenume_medic, nume_pacient, prenume_pacient, data, ora);
                        
                                db.stergeConsultatieDinDB(nume_medic, prenume_medic, nume_pacient, prenume_pacient, data, ora);
                                
                                db.salveazaTotSpitalul(
                                    spitalulMeu.getPersonal(), 
                                    spitalulMeu.getPacienti(), 
                                    spitalulMeu.getConsultatii(), 
                                    spitalulMeu.getRetete(), 
                                    spitalulMeu.getSectii()
                                );

                            } catch (const std::exception& e) {
                                if (guiLogger) {
                                    guiLogger->onEvent("Eroare la finalizarea consultatiei: " + std::string(e.what()));
                                }
                            }
                            break; 
                        }
                    }
                    ImGui::EndTable();
                }

                ImGui::EndTabItem();
            }

            // Sectii si retete
            if (ImGui::BeginTabItem("Sectii & Retete")) {
                ImGui::Text("Aici vom vizualiza infrastructura spitalului si medicatia eliberata.");
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 150);
        ImGui::Separator();

        ImGui::TextColored(ImVec4(0.4f, 0.8f, 0.4f, 1.0f), "Terminal Notificari Live");
        
        ImGui::BeginChild("LogRegion", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::Text("[Sistem] Interfata grafica a fost initializata cu succes.");
        ImGui::Text("[Sistem] Asteptam conexiunea completa la baza de date...");
        ImGui::EndChild();

        ImGui::End();
        
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}