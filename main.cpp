#include "httplib.h"

#include "src/main.cpp"
#include <iostream>
unordered_map<string, string> parse_urlencoded(const string& body) {
    unordered_map<string, string> params;
    size_t start = 0;
    bool iterar=true;

    while (iterar) {
        size_t key_start = body.find('"', start) + 1;
        size_t key_end = body.find('"', key_start);
        string key = body.substr(key_start, key_end - key_start);

        size_t value_start = body.find('"', key_end + 1) + 1;
        size_t value_end = body.find('"', value_start);
        string value = body.substr(value_start, value_end - value_start);

        params[key] = value;
        if(start>value_end){
            iterar=false;
            break;
        }
        start = value_end + 1;
    }

    return params;
};
bool validate_user(Cuenta* cuenta,ProxyAutenticacion proxy,GestorCuentas* cuentas,string correo,string contrasenia){
    if (proxy.autenticar(correo, contrasenia)) {
                    cuenta = cuentas->obtenerCuenta(correo);
                    GestorArchivos::obtenerInstancia()->cargarCuenta(*cuenta); // Cargar datos de la cuenta
                return true;
                } else {
                    return false;
                }
};
bool register_user(Cuenta *cuenta,ProxyAutenticacion proxy,GestorCuentas* cuentas,string correo,string contrasenia){
    if (cuentas->obtenerCuenta(correo) == nullptr) {
                    if (cuentas->agregarCuenta(correo, contrasenia)) {
                        cuenta = cuentas->obtenerCuenta(correo);
                        proxy.agregarCuenta(cuenta);
                        GestorArchivos::obtenerInstancia()->guardarCuenta(*cuenta); // Guardar la nueva cuenta
                        return true;
                    } 
                    else {
                        return false;
                    }
}
else{return false;}

};


int main() {
    httplib::Server svr;
    GestorCuentas *cuentas = GestorCuentas::obtenerInstancia();
    GestorArchivos::obtenerInstancia()->cargarCuentas(*cuentas); // Cargar todas las cuentas al inicio
    ProxyAutenticacion proxy;
    const auto &todasLasCuentas = cuentas->obtenerTodasLasCuentas();
    for (const auto &pair : todasLasCuentas) {
        proxy.agregarCuenta(pair.second);
    }
    
    Cuenta *cuenta = nullptr;
    Streaming streaming;
    cout<<"iniciando carga";
    streaming.loadMovies("data/data.csv");
    cout<<"carga terminada";
    // Endpoint para obtener todas las películas
    svr.Post("/api/login", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:5173"); // Reemplaza con la URL de tu frontend en React
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Credentials", "true");

        // Parsear el cuerpo de la solicitud como `application/x-www-form-urlencoded`
        auto params = parse_urlencoded(req.body);
        string username = params["username"];
        string password = params["password"];

        if (validate_user(cuenta,proxy,cuentas,username, password)) {
            res.set_content("{\"status\":\"success\", \"message\":\"Login successful\"}", "application/json");
        } else {
            res.status = 401; // Unauthorized
            res.set_content("{\"status\":\"error\", \"message\":\"Invalid username or password\"}", "application/json");
        }
    });
    svr.Post("/api/register", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:5173"); // Reemplaza con la URL de tu frontend en React
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Credentials", "true");

        // Parsear el cuerpo de la solicitud como `application/x-www-form-urlencoded`
        auto params = parse_urlencoded(req.body);
        string username = params["username"];
        string password = params["password"];

        if (register_user(cuenta,proxy,cuentas,username, password)) {
            res.set_content("{\"status\":\"success\", \"message\":\"register successful\"}", "application/json");
        } else {
            res.status = 401; // Unauthorized
            res.set_content("{\"status\":\"error\", \"message\":\"correo ya registrado\"}", "application/json");
        }
    });

    svr.Post("/api/movies", [&](const httplib::Request& req, httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin", "http://localhost:5173"); // Reemplaza con la URL de tu frontend en React
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Access-Control-Allow-Credentials", "true");

    auto params = parse_urlencoded(req.body);
    string busqueda = params["username"];
    string count = params["count"];
    string response_json = "[";
    auto idEncontrados = streaming.buscarPorSubcadena(busqueda);
    for (int i = 0; i < stoi(count) && i < idEncontrados.size(); i++) {
        if (i > 0) response_json += ",";
        response_json += "{\"id\":";
        response_json += to_string(idEncontrados[i].first);
        response_json += ",\"title\":\"";
        response_json += streaming.peliculas.at(idEncontrados[i].first).getTitulo() + "\"}";
    }
    response_json += "]";

    res.set_content(response_json, "application/json");
    return true;
    });
    svr.Get("/api/see-later", [&](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:5173"); // Reemplaza con la URL de tu frontend en React
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Credentials", "true"); // Habilita CORS para este endpoint específico
        string response_json = "[{\"id\":1,\"title\":\"Movie 1\"}]"; // Simulación de datos
        res.set_content(response_json, "application/json");
        return true;
    });
    svr.Get("/api/like", [&](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:5173"); // Reemplaza con la URL de tu frontend en React
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Credentials", "true");
        string response_json = "[{\"id\":1,\"title\":\"Movie 1\"}]"; // Simulación de datos
        res.set_content(response_json, "application/json");
        return true;
    });

    // Manejo explícito de OPTIONS para CORS
    svr.Options("/.*", [&](const httplib::Request& /*req*/, httplib::Response& res) {
      res.set_header("Access-Control-Allow-Origin", "http://localhost:5173"); // Reemplaza con la URL de tu frontend en React
      res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
      res.set_header("Access-Control-Allow-Headers", "Content-Type");
      res.set_header("Access-Control-Allow-Credentials", "true");
        res.status = 200;
        return true;
    });

    // Configuración del servidor para escuchar en localhost:8080
    svr.listen("localhost", 8080);

    std::cout << "Server started at http://localhost:8080" << std::endl;

    return 0;
}
