#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Clasa abstractă Produs cu metoda clone inclusă
class Produs {
public:
    virtual double getPret() const = 0;
    virtual void descriere() const = 0;
    virtual shared_ptr<Produs> clone() const = 0;
    virtual ~Produs() {}
};

// Clasa derivată Mancare
class Mancare : public Produs {
private:
    string denumire;
    double pret;
    bool vegetarian;
public:
    Mancare(string denumire_, double pret_, bool vegetarian_)
        : denumire(denumire_), pret(pret_), vegetarian(vegetarian_) {
    }

    double getPret() const override {
        return pret;
    }

    void descriere() const override {
        cout << "Mancare: " << denumire << ", Pret: " << pret
            << ", Vegetarian: " << (vegetarian ? "Da" : "Nu") << "\n";
    }

    shared_ptr<Produs> clone() const override {
        return make_shared<Mancare>(*this);
    }
};

// Clasa derivată Bautura
class Bautura : public Produs {
private:
    string denumire;
    double pret;
    bool alcoolica;
public:
    Bautura(string denumire_, double pret_, bool alcoolica_)
        : denumire(denumire_), pret(pret_), alcoolica(alcoolica_) {
    }

    double getPret() const override {
        return pret;
    }

    void descriere() const override {
        cout << "Bautura: " << denumire << ", Pret: " << pret
            << ", Alcoolica: " << (alcoolica ? "Da" : "Nu") << "\n";
    }

    shared_ptr<Produs> clone() const override {
        return make_shared<Bautura>(*this);
    }
};

// Clasa Comanda
class Comanda {
private:
    vector<shared_ptr<Produs>> produse;
public:
    void adaugaProdus(shared_ptr<Produs> p) {
        produse.push_back(p);
    }

    void adaugaProdus(const Produs& p) {
        produse.push_back(p.clone());
    }

    const vector<shared_ptr<Produs>>& getProduse() const {
        return produse;
    }

    void afiseazaComanda() const {
        cout << "Detalii comanda:\n";
        for (const auto& p : produse) {
            p->descriere();
        }
    }

    // Supraincarcare operator +
    Comanda operator+(const Comanda& alta) const {
        Comanda rezultat = *this;
        for (const auto& p : alta.produse) {
            rezultat.adaugaProdus(*p);
        }
        return rezultat;
    }
};

// Template pentru calculul prețului total
template <typename T>
class CalculatorPret {
private:
    const T& produse;
public:
    CalculatorPret(const T& produse_) : produse(produse_) {}

    double calculeazaTotal() const {
        double total = 0;
        for (const auto& p : produse) {
            total += p->getPret();
        }
        return total;
    }
};

// Funcție principală de test
int main() {
    // Creăm produse
    shared_ptr<Produs> pizza = make_shared<Mancare>("Pizza Margherita", 35.5, true);
    shared_ptr<Produs> burger = make_shared<Mancare>("Burger Vita", 45.0, false);
    shared_ptr<Produs> cola = make_shared<Bautura>("Coca-Cola", 8.0, false);
    shared_ptr<Produs> bere = make_shared<Bautura>("Bere", 12.5, true);

    // Creăm comenzi
    Comanda comanda1;
    comanda1.adaugaProdus(pizza);
    comanda1.adaugaProdus(cola);

    Comanda comanda2;
    comanda2.adaugaProdus(burger);
    comanda2.adaugaProdus(bere);

    cout << "Comanda 1:\n";
    comanda1.afiseazaComanda();
    cout << "\nComanda 2:\n";
    comanda2.afiseazaComanda();

    // Combinăm comenzile
    Comanda comandaFinala = comanda1 + comanda2;
    cout << "\nComanda Finala (combinata):\n";
    comandaFinala.afiseazaComanda();

    // Calculăm prețul total
    CalculatorPret<vector<shared_ptr<Produs>>> calculator(comandaFinala.getProduse());
    cout << "\nTotal de plata: " << calculator.calculeazaTotal() << " RON\n";

    return 0;
}
