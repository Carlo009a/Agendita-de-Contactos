#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 

using namespace std;

class Contacto {
private:
    string nombre;
    string telefono;
    string email;

public:
    Contacto() {}
    
    Contacto(string n, string t, string e) {
        nombre = n;
        telefono = t;
        email = e;
    }

    string getNombre() { return nombre; }
    string getTelefono() { return telefono; }
    string getEmail() { return email; }

    void mostrarInfo() {
        cout << "Nombre: " << nombre << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "Email: " << email << endl << endl;
    }
};

class Agenda {
private:
    vector<Contacto> contactos;
    string archivo;

    void guardarEnArchivo() {
        ofstream f(archivo.c_str());
        if (f.is_open()) {
            for (size_t i = 0; i < contactos.size(); i++) {
                f << contactos[i].getNombre() << "," 
                  << contactos[i].getTelefono() << ","
                  << contactos[i].getEmail() << endl;
            }
            f.close();
        }
    }

    void cargarDesdeArchivo() {
        ifstream f(archivo.c_str());
        if (f.is_open()) {
            string linea;
            while (getline(f, linea)) {
                size_t pos1 = linea.find(',');
                size_t pos2 = linea.find(',', pos1+1);
                
                if (pos1 != string::npos && pos2 != string::npos) {
                    string nombre = linea.substr(0, pos1);
                    string telefono = linea.substr(pos1+1, pos2-pos1-1);
                    string email = linea.substr(pos2+1);
                    
                    contactos.push_back(Contacto(nombre, telefono, email));
                }
            }
            f.close();
        }
    }

public:
    Agenda() { //Constructor
        archivo = "contactos.txt";
        cargarDesdeArchivo();
    }

    ~Agenda() { //Destructor 
        guardarEnArchivo();
    }

    void agregarContacto() {
        string n, t, e;
        cout << "Nombre: ";
        getline(cin, n);
        cout << "Telefono: ";
        getline(cin, t);
        cout << "Email: ";
        getline(cin, e);
        
        contactos.push_back(Contacto(n, t, e));
        cout << "Contacto agregado!" << endl;
    }

    void buscarContacto() {
        string nombre;
        cout << "Nombre a buscar: ";
        getline(cin, nombre);
        
        bool encontrado = false;
        for (size_t i = 0; i < contactos.size(); i++) {
            if (contactos[i].getNombre() == nombre) {
                contactos[i].mostrarInfo();
                encontrado = true;
                break;
            }
        }
        
        if (!encontrado) {
            cout << "Contacto no encontrado!" << endl;
        }
    }

    void listarContactos() {
        if (contactos.empty()) {
            cout << "No hay contactos registrados!" << endl;
            return;
        }
        
        for (size_t i = 0; i < contactos.size(); i++) {
            contactos[i].mostrarInfo();
        }
    }

    void eliminarContacto() {
        string nombre;
        cout << "Nombre a eliminar: ";
        getline(cin, nombre);
        
        bool eliminado = false;
        for (size_t i = 0; i < contactos.size(); ) {
            if (contactos[i].getNombre() == nombre) {
                contactos.erase(contactos.begin() + i);
                eliminado = true;
            } else {
                i++;
            }
        }
        
        if (eliminado) {
            cout << "Contacto eliminado!" << endl;
        } else {
            cout << "Contacto no encontrado!" << endl;
        }
    }
};

void mostrarMenu() {
    system("cls || clear"); 
    cout << "\n╔══════════════════════════════╗\n";
    cout << "║       AGENDA DE CONTACTOS    ║\n";
    cout << "╠══════════════════════════════╣\n";
    cout << "║ 1. Agregar contacto          ║\n";
    cout << "║ 2. Buscar contacto           ║\n";
    cout << "║ 3. Listar contactos          ║\n";
    cout << "║ 4. Eliminar contacto         ║\n";
    cout << "║ 5. Salir                     ║\n";
    cout << "╚══════════════════════════════╝\n";
    cout << "Ingrese una opción (1-5): ";
}

// Lee y valida que la opción sea un número entre 1 y 5
int leerOpcion() {
    string entrada;
    getline(cin, entrada);
    
    if (entrada.size() == 1 && isdigit(entrada[0])) {
        int valor = entrada[0] - '0';
        if (valor >= 1 && valor <= 5) {
            return valor;
        }
    }

    return -1; 
}

int main() {
    Agenda agenda;
    int opcion;

    do {
        mostrarMenu();
        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                agenda.agregarContacto();
                break;
            case 2:
                agenda.buscarContacto();
                break;
            case 3:
                agenda.listarContactos();
                break;
            case 4:
                agenda.eliminarContacto();
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "\nOpción inválida. Por favor ingrese un número del 1 al 5.\n";
        }

        if (opcion != 5) {
            cout << "\nPresione Enter para volver al menú...";
            cin.ignore(); 
        }

    } while (opcion != 5);

    return 0;
}
