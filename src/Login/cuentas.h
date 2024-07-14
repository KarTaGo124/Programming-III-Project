#ifndef CUENTAS_H
#define CUENTAS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Memento {
private:
    string correo;
    string contrasenia;

public:
    Memento(const string &email, const string &password);
    string getCorreo() const;
    string getContrasenia() const;
};

class Cuenta {
private:
    string correo;
    string contrasenia;
    vector<Memento*> estados;

public:
    Cuenta(const string &email, const string &password);
    ~Cuenta();
    void setCorreo(const string &email);
    void setContrasenia(const string &password);
    string getCorreo() const;
    string getContrasenia() const;
    void guardarEstado();
    void restaurarEstado(int indice);
    vector<Memento*> getEstados() const;
};

#endif // CUENTAS_H
