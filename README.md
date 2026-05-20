# LifeFlow-Management-System (OOP C++)

Un sistem complet de management spitalicesc dezvoltat în C++, dotat cu o interfață grafică interactivă și persistență a datelor. Aplicația modelează fluxurile reale dintr-o unitate medicală, aplicând principii solide de Programare Orientată pe Obiecte (OOP).

## Funcționalități Principale

* **Gestiune Personal:** Adăugare personal specializat (Medici, Asistenți, Rezidenți) cu atribute specifice și ajustare salarială dinamică direct din interfață.
* **Evidență Pacienți:** Sistem de internare și externare în timp real.
* **Programare Consultații:** Alocare dinamică între personalul medical și pacienții activi, utilizând meniuri contextuale, cu evidența datei și orei.
* **Persistență Date:** Sincronizare bidirecțională cu o bază de date SQLite locală (`spitalul_meu.db`).

## Tehnologii și Librării Utilizate

* **Limbaj:** C++ (Standardul C++17)
* **GUI:** [Dear ImGui](https://github.com/ocornut/imgui) (pentru interfața grafică)
* **Bază de date:** SQLite3 + wrapper-ul C++ SQLiteCpp
* **Build System:** CMake

## Design Patterns Implementate

Pentru a asigura un cod decuplat, extensibil și sigur din punct de vedere al memoriei, proiectul integrează următoarele șabloane de proiectare:

1. **Factory Method:** Utilizat pentru instanțierea inteligentă a diverselor tipuri de angajați, ascunzând complexitatea alocării dinamice a memoriei (`PersonalFactory`).
2. **Observer:** Implementat pentru sistemul de logare grafică (`GUILogger`). Obiectul principal de tip `spital` notifică automat interfața grafică la orice modificare majoră de stare (externări, programări, modificări salariale).
3. **Repository:** Încapsulează colecțiile de date (vectorii de pointeri către clasa de bază `personalSpital`, `pacient` etc.) și expune iteratori constanți sau referințe sigure pentru a preveni modificarea accidentală din afara claselor de gestiune.

## Instrucțiuni de Compilare și Rulare

Proiectul folosește CMake pentru gestionarea build-ului. Asigură-te că ai instalat un compilator C++ valid (ex: MinGW/GCC) pe sistemul tău.

1. Clonează sau descarcă arhiva proiectului.
2. Deschide un terminal în folderul rădăcină (unde se află `CMakeLists.txt`).
3. Generează fișierele de build:

   ```bash
   cmake -B build -S .
   ```
4. Compilează proiectul:

   ```
   cmake --build build
   ```
5. Rulează executabilul:

   ```
   .\build\oop.exe
   ```
