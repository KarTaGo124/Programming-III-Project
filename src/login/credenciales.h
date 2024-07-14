#ifndef CREDENCIALES_H
#define CREDENCIALES_H

#include <unordered_map>
#include <string>
#include "cuentas.h"

using namespace std;

class Autenticacion {
public:
    virtual bool autenticar(const string &correo, const string &contrasenia) const = 0;
    virtual void agregarCuenta(Cuenta* cuenta) = 0;
    virtual ~Autenticacion() = default;
};

class AutenticacionReal : public Autenticacion {
private:
    unordered_map<string, string> usuarios;

public:
    bool autenticar(const string &correo, const string &contrasenia) const override;
    void agregarCuenta(Cuenta* cuenta) override;
};

class ProxyAutenticacion : public Autenticacion {
private:
    AutenticacionReal autenticacionReal;

public:
    bool autenticar(const string &correo, const string &contrasenia) const override;
    void agregarCuenta(Cuenta* cuenta) override;
};

#endif // CREDENCIALES_H