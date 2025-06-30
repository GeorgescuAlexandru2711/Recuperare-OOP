#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Clasa abstractă Animal
class Animal {
public:
    virtual void sunet() const = 0;
    virtual void descriere() const = 0;
    virtual ~Animal() {}
};

// Clasa Mamifer derivată din Animal
class Mamifer : public Animal {
public:
    void sunet() const override {
        cout << "Mamiferul scoate un sunet specific: Roooar!\n";
    }
    void descriere() const override {
        cout << "Acesta este un mamifer.\n";
    }
};

// Clasa Pasare derivată din Animal
class Pasare : public Animal {
public:
    void sunet() const override {
        cout << "Pasarea ciripeste: Cip Cip!\n";
    }
    void descriere() const override {
        cout << "Aceasta este o pasare.\n";
    }
};

// Clasa Reptila derivată din Animal
class Reptila : public Animal {
public:
    void sunet() const override {
        cout << "Reptila scoate un sunet sasaitor: Ssssss!\n";
    }
    void descriere() const override {
        cout << "Aceasta este o reptila.\n";
    }
};

// Clasa Cusca care contine un animal si un ID
class Cusca {
private:
    int id;
    shared_ptr<Animal> animal;
public:
    Cusca(int id_, shared_ptr<Animal> animal_) : id(id_), animal(animal_) {}

    friend ostream& operator<<(ostream& out, const Cusca& c) {
        out << "Cusca ID: " << c.id << "\n";
        c.animal->descriere();
        c.animal->sunet();
        return out;
    }
};

// Clasa template Zoo care gestionează un vector de cuști
template <typename T>
class Zoo {
private:
    vector<T> custi;
public:
    void adaugaCusca(const T& c) {
        custi.push_back(c);
    }

    void afiseazaZoo() const {
        for (const auto& c : custi) {
            cout << c << "\n";
        }
    }
};

// Funcția principală pentru testare
int main() {
    // Creăm animale
    shared_ptr<Animal> mamifer = make_shared<Mamifer>();
    shared_ptr<Animal> pasare = make_shared<Pasare>();
    shared_ptr<Animal> reptila = make_shared<Reptila>();

    // Creăm cuști
    Cusca c1(1, mamifer);
    Cusca c2(2, pasare);
    Cusca c3(3, reptila);

    // Creăm o grădină zoologică
    Zoo<Cusca> zoo;
    zoo.adaugaCusca(c1);
    zoo.adaugaCusca(c2);
    zoo.adaugaCusca(c3);

    // Afișăm conținutul grădinii zoologice
    zoo.afiseazaZoo();

    return 0;
}
