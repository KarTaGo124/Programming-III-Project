#ifndef CUENTA_H
#define CUENTA_H

#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Cuenta {
private:
    string correo;
    string contrasenia;
    unordered_set<int> verMasTarde;
    unordered_map<string, int> likes;

public:
    Cuenta(const string &email, const string &password);

    void setCorreo(const string &email);

    void setContrasenia(const string &password);

    string getCorreo() const;

    string getContrasenia() const;

    unordered_set<int> &getVerMasTarde();

    unordered_map<string, int> &getLikes();

    void agregarVerMasTarde(int idPelicula);

    void agregarLike(const string &tag);

    void agregarVerAhora(const string &titulo);
};

#endif // CUENTA_H