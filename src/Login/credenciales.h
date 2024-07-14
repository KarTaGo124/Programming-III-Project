#ifndef CREDENCIALES_H
#define CREDENCIALES_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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
    vector<Memento> estados;

public:
    Cuenta(const string &email, const string &password);

    void guardarCuenta();

    string getCorreo() const;
    string getContrasenia() const;
};

class Autenticacion {
public:
    virtual bool autenticar(const string &correo, const string &contrasenia) const = 0;
    virtual void agregarCuenta(const string &correo, const string &contrasenia) = 0;
};

class AutenticacionReal : public Autenticacion {
private:
    unordered_map<string, string> usuarios;

public:
    AutenticacionReal();

    bool autenticar(const string &correo, const string &contrasenia) const override;
    void agregarCuenta(const string &correo, const string &contrasenia) override;
};

class ProxyAutenticacion : public Autenticacion {
private:
    AutenticacionReal autenticacionReal;

public:
    bool autenticar(const string &correo, const string &contrasenia) const override;
    void agregarCuenta(const string &correo, const string &contrasenia) override;
};

#endif
