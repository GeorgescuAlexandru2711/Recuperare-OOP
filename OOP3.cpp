#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Clasa de bază abstractă Document
class Document {
public:
    virtual void citeste() = 0;
    virtual void afiseaza() const = 0;
    virtual ~Document() {}
};

// Clasa Carte derivată din Document
class Carte : public Document {
private:
    string titlu;
    string autor;
    int nrPagini;
public:
    Carte(const string& titlu_ = "", const string& autor_ = "", int nrPagini_ = 0)
        : titlu(titlu_), autor(autor_), nrPagini(nrPagini_) {
    }

    void citeste() override {
        cout << "Introdu titlul cartii: ";
        getline(cin, titlu);
        cout << "Introdu autorul: ";
        getline(cin, autor);
        cout << "Introdu numarul de pagini: ";
        cin >> nrPagini;
        cin.ignore();
    }

    void afiseaza() const override {
        cout << "Carte - Titlu: " << titlu
            << ", Autor: " << autor
            << ", Numar pagini: " << nrPagini << "\n";
    }
};

// Clasa Revista derivată din Document
class Revista : public Document {
private:
    string titlu;
    int nrEditie;
public:
    Revista(const string& titlu_ = "", int nrEditie_ = 0)
        : titlu(titlu_), nrEditie(nrEditie_) {
    }

    void citeste() override {
        cout << "Introdu titlul revistei: ";
        getline(cin, titlu);
        cout << "Introdu numarul editiei: ";
        cin >> nrEditie;
        cin.ignore();
    }

    void afiseaza() const override {
        cout << "Revista - Titlu: " << titlu
            << ", Editia nr.: " << nrEditie << "\n";
    }
};

// Clasa Ziar derivată din Document
class Ziar : public Document {
private:
    string titlu;
    string dataAparitie;
public:
    Ziar(const string& titlu_ = "", const string& dataAparitie_ = "")
        : titlu(titlu_), dataAparitie(dataAparitie_) {
    }

    void citeste() override {
        cout << "Introdu titlul ziarului: ";
        getline(cin, titlu);
        cout << "Introdu data aparitiei: ";
        getline(cin, dataAparitie);
    }

    void afiseaza() const override {
        cout << "Ziar - Titlu: " << titlu
            << ", Data aparitiei: " << dataAparitie << "\n";
    }
};

// Clasa Bibliotecar care gestionează lista de documente
class Bibliotecar {
private:
    vector<shared_ptr<Document>> listaDocumente;
public:
    void adaugaDocument(shared_ptr<Document> doc) {
        listaDocumente.push_back(doc);
    }

    void afiseazaDocumente() const {
        cout << "Lista documente:\n";
        for (const auto& doc : listaDocumente) {
            doc->afiseaza();
        }
    }

    shared_ptr<Document> operator[](size_t index) const {
        if (index >= listaDocumente.size()) {
            throw out_of_range("Index invalid!");
        }
        return listaDocumente[index];
    }
};

// Template Arhiva<T> cu shared_ptr pentru consistență
template <typename T>
class Arhiva {
private:
    vector<shared_ptr<T>> documente;
public:
    void adauga(shared_ptr<T> doc) {
        documente.push_back(doc);
    }

    void afiseazaTot() const {
        cout << "Continutul arhivei:\n";
        for (const auto& doc : documente) {
            doc->afiseaza();
        }
    }
};

// Funcția principală de test
int main() {
    Bibliotecar bibliotecar;

    // Creăm documente fictive și le adăugăm
    shared_ptr<Document> c1 = make_shared<Carte>("Umbra Codrilor", "Lavinia Petrescu", 412);
    shared_ptr<Document> r1 = make_shared<Revista>("Stiinta Azi", 15);
    shared_ptr<Document> z1 = make_shared<Ziar>("Gazeta Aurora", "29.06.2025");

    bibliotecar.adaugaDocument(c1);
    bibliotecar.adaugaDocument(r1);
    bibliotecar.adaugaDocument(z1);

    cout << "\nDocumente din biblioteca:\n";
    bibliotecar.afiseazaDocumente();

    // Testăm operatorul []
    cout << "\nAccesam documentul cu index 1:\n";
    bibliotecar[1]->afiseaza();

    // Folosim template-ul Arhiva<T>
    Arhiva<Carte> arhivaCarti;
    shared_ptr<Carte> carte1 = make_shared<Carte>("Drumul Stelelor", "Victor Marin", 230);
    arhivaCarti.adauga(carte1);

    cout << "\nArhiva cu carti:\n";
    arhivaCarti.afiseazaTot();

    return 0;
}
