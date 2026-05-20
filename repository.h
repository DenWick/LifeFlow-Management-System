#pragma once
#include <vector>
#include <algorithm>

template <typename T>
class repository {
private:
    std::vector<T*> elemente;
public:
    void adauga(T* element) {
        elemente.push_back(element);
    }

    const std::vector<T*>& getToate() const {
        return elemente;
    }

    void goleste() {
        elemente.clear();
    }

    void elimina(T* element) {
        auto it = std::find(elemente.begin(), elemente.end(), element);
        if (it != elemente.end()) {
            delete *it;
            elemente.erase(it);
        }
    }

       ~repository() {
        for (auto* el : elemente) {
            delete el;
        }
        elemente.clear();
    }
};