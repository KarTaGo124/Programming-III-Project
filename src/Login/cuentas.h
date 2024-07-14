#ifndef CUENTAS_H
#define CUENTAS_H

#include <string>

using namespace std;

class Cuenta {
private:
    string correo;
    string contrasenia;

public:
    Cuenta(const string &email, const string &password);

    void setCorreo(const string &email);
    void setContrasenia(const string &password);

    string getCorreo() const;
    string getContrasenia() const;
};

#endif // CUENTAS_H
