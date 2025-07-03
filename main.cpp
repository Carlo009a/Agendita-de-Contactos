#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <algorithm>

using namespace std;

class Contacto {
private:
    string nombre;
    string telefono;
    string email;

public:
    Contacto() {
        nombre= "Contacto: ";
        telefono = "900000000";
        email = "contacto123@gmail.com";
    }
    
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

    void editarContacto() {
    	string nombre;
    	cout << "Nombre del contacto a editar: ";
    	getline(cin, nombre);

	    for (size_t i = 0; i < contactos.size(); i++) {
	        if (contactos[i].getNombre() == nombre) {
	            string nuevoTel, nuevoEmail;
	            cout << "Nuevo teléfono: ";
	            getline(cin, nuevoTel);
	            cout << "Nuevo email: ";
	            getline(cin, nuevoEmail);
	
	            contactos[i] = Contacto(nombre, nuevoTel, nuevoEmail);
	            cout << "Contacto actualizado!" << endl;
	            return;
	        }
	    }

    	cout << "Contacto no encontrado!" << endl;
	}
};

// Función para mostrar el menú principal
void mostrarMenu() {
    system("cls || clear"); 
    
    cout << "=== Bienvenido a tu Agenda de Contactos ===\n";
    
	// Mostrar fecha y hora actual
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);
    cout << "\nFecha y hora de entrada: " << asctime(tiempoLocal) << endl;
    
    cout << "+------------------------------+\n";
    cout << "|       AGENDA DE CONTACTOS    |\n";
    cout << "|------------------------------|\n";
    cout << "| 1. Agregar contacto          |\n";
    cout << "| 2. Buscar contacto           |\n";
    cout << "| 3. Listar contactos          |\n";
    cout << "| 4. Eliminar contacto         |\n";
    cout << "| 5. Editar contacto           |\n";
    cout << "| 6. Salir                     |\n";
    cout << "+------------------------------+\n";
    cout << "\nIngrese una opcion (1-6): ";
}

// Función para leer y validar la opción ingresada
int leerOpcion() {
    string entrada;
    getline(cin, entrada);
    
    // Verifica si es un solo carácter y es un dígito
    if (entrada.size() == 1 && isdigit(entrada[0])) {
        int valor = entrada[0] - '0';
        if (valor >= 1 && valor <= 6) {
            return valor;
        }
    }

    return -1; 
}

int main() {
    Agenda agenda;
    int opcion;

    do {
        mostrarMenu(); // Muestra el menú en consola
        opcion = leerOpcion(); // Lee y valida la opción ingresada por el usuario

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
                agenda.editarContacto();
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "\nOpcion invalida. Por favor, ingrese un numero del 1 al 6.\n";
                break;
        }
	
	    if (opcion != 6) {
            cout << "\nPresione Enter para volver al menu...";
            cin.ignore();
        }

    } while (opcion != 6);

    return 0;
}
