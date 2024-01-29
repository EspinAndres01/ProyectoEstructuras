#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "TablaAmortizacion.h"
#include "Fecha.h"
#include "validarValores.h"
#include <fstream>
#include "WebOpener.h"
#include "Datos.h"
#include "validacionCedula.h"
#include "validacionID.h"
#include "Cedula.h"
#include "validacionNombresyApellidos.h"

bool crearCuenta(std::string& IDUsuario);

TablaAmortizacion tabla;
Fecha fecha;
Cedula cedulaValidator;
Datos informacion;

void mostrarMenu(int opcion) {
    system("cls");
    std::cout << "\n--------------GENERADOR DE PRESTAMO-----------------\n";
    std::cout << "\nSeleccione una opcion:\n\n";
    std::cout << (opcion == 1 ? "> " : "  ") << "1. Crear cliente.\n";
    std::cout << (opcion == 2 ? "> " : "  ") << "2. Crear cuenta y Generar prestamo.\n";
    std::cout << (opcion == 3 ? "> " : "  ") << "3. Recuperar informacion del archivo y generar tabla.\n";
    std::cout << (opcion == 4 ? "> " : "  ") << "4. Generar Backup\n";
    std::cout << (opcion == 5 ? "> " : "  ") << "5. Lista de respaldos\n";
    std::cout << (opcion == 6 ? "> " : "  ") << "6. Equipo de desarrollo\n";
    std::cout << (opcion == 7 ? "> " : "  ") << "7. Ayuda\n";
    std::cout << (opcion == 8 ? "> " : "  ") << "8. Salir\n";
}

void pausa() {
    std::cout << "\nPresione Enter para continuar...\n";
    while (_getch() != 13); 
}


void realizarOpcion1() {
    std::string IDUsuario;
    if (crearCuenta(IDUsuario)){
        system("cls");
        std::cout << "---------------GENERADOR DE PRESTAMOS-------------------\n";
        std::cout << "\n--------------TABLA DE AMORTIZACION-------------------\n";
        double prestamo = ingresarMontoValidado();
        double tasaInteresAnual = ingresarTasaInteresValidada();
        int numeroCuotas = ingresarNumeroCuotasValidado();

        int diaAleatorio = fecha.obtenerDiaAleatorio();

        tabla.guardarDatosEnArchivo(prestamo, tasaInteresAnual, numeroCuotas, diaAleatorio);
        tabla.generarTabla(prestamo, tasaInteresAnual, numeroCuotas, "-", diaAleatorio, IDUsuario);
        tabla.mostrarTabla();
        std::cout << "\nLos valores se han guardado exitosamente en 'datos_prestamo.txt'." << std::endl;

        pausa();

    }else{
        std::cout << "No se ha creado la cuenta. No es posible generar el préstamo." << std::endl;
        pausa();
    }
    
}

void realizarOpcion2() {
    system("cls");
    tabla.visualizarDatosEnArchivo("datos_prestamo.txt");

    int indice;
    do {
        indice = ingresar_enteros("\nIngrese el elemento que quiere recuperar (debe ser un número positivo): ");
    } while (indice <= 0);

    tabla.cargarDatosDesdeArchivo("datos_prestamo.txt", indice);
    tabla.mostrarTabla();

    pausa();
}

void realizarOpcion3() {
    system("cls");
    tabla.crearRespaldo("datos_prestamo.txt");
    tabla.crearRespaldo("datos_usuarios.txt");
    pausa();
}
/*
void realizarOpcion4() {
    system("cls");
    tabla.listarRespaldos("datos_prestamo.txt");
    std::string archivoRespaldo;
    std::cout << "Ingrese el nombre del archivo que desea restaurar: ";
    std::cin >> archivoRespaldo;
    tabla.restaurarRespaldo("datos_prestamo.txt", archivoRespaldo);
    pausa();
}
*/

void realizarOpcion4() {
    system("cls");

    tabla.listarRespaldos("datos_usuarios.txt");
    std::string archivoRespaldoUsuario;
    std::cout << "Ingrese el nombre del archivo de respaldo para 'datos_usuario' sin el .txt: ";
    std::cin >> archivoRespaldoUsuario;

    // Restaurar el respaldo para 'datos_usuario.txt'
    tabla.restaurarRespaldo("datos_usuarios.txt", archivoRespaldoUsuario);

    tabla.listarRespaldos("datos_prestamo.txt");
    std::string archivoRespaldoPrestamo;
    std::cout << "Ingrese el nombre del archivo de respaldo para 'datos_prestamo' sin el .txt: ";
    std::cin >> archivoRespaldoPrestamo;

    // Restaurar el respaldo para 'datos_prestamo.txt'
    tabla.restaurarRespaldo("datos_prestamo.txt", archivoRespaldoPrestamo);

    pausa();
}

void realizarOpcion6() {
    system("cls");
    std::cout << "Saliendo del programa." << std::endl;

    pausa();
    exit(0);
}
void realizarOpcion5() {
    system("cls");
    std::cout << "Seleccione una opción:\n\n";
    std::cout << "  1. Ayuda\n";
    std::cout << "  2. Saliendo del programa\n\n";

    char opcionAyuda;
    std::cout << "Ingrese la opción: ";
    std::cin >> opcionAyuda;

    if (opcionAyuda == '1') {
        // Llamada a la nueva función para abrir una página web
        WebOpener::abrirPaginaWeb("doxy/html/index.html");
        std::cout << "\nSe abrió la página de ayuda en el navegador.\n";
    } else if (opcionAyuda == '2') {
        std::cout << "Saliendo del programa.\n";
        pausa();
        exit(0);
    } else {
        std::cout << "Opción no válida.\n";
    }

    pausa();
}
void mostrarImagenGrupoDesarrollo() {
    system("cls");
    const std::string rutaArchivoImagen = "gupo.txt";

    std::ifstream archivoImagen(rutaArchivoImagen);
    if (!archivoImagen.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        pausa();
        return;
    }

    std::string linea;
    while (getline(archivoImagen, linea)) {
        std::cout << linea << std::endl;
    }

    if (archivoImagen.eof()) {
        std::cout << "\t\t     GRUPO DE DESARROLLO" << std::endl;
    } else if (archivoImagen.fail()) {
        std::cout << "Error al leer el archivo." << std::endl;
    } else if (archivoImagen.bad()) {
        std::cout << "Error crítico al abrir el archivo." << std::endl;
    }

    archivoImagen.close();
    pausa();
}


bool crearCuenta(std::string& IDUsuario) {
    system("cls");
    std::string cedulaIngresada = ingresarCedula("Ingrese la cedula de ciudadania: ");
    
    if (cedulaValidator.validarCedulaEcuatoriana(cedulaIngresada)) {
        std::string nuevoID = generarNumeroCuenta();
        std::string nombre = ingresarNombreApellidoMayusculas("\nIngrese el nombre: ");
        std::string apellido = ingresarNombreApellidoMayusculas("\nIngrese el apellido: ");
        informacion.setDatos(nuevoID, cedulaIngresada, nombre, apellido);
        
        // Guardar los datos en el archivo y obtener el ID
        tabla.guardaDatoUsuariosEnArchivo(nuevoID, cedulaIngresada, nombre, apellido);
        
        std::cout << "\n\n CLIENTE CREADO" << std::endl;
        std::cout << "\nID: " << informacion.getID() << std::endl;
        std::cout << "Cedula: " << informacion.getCedula() << std::endl;
        std::cout << "Nombre: " << informacion.getNombre() << std::endl;
        std::cout << "Apellido: " << informacion.getApellido() << std::endl;
        
        IDUsuario = nuevoID;  // Actualizar el IDUsuario con el nuevo ID
        return true;  // Indicar que la cuenta se creó con éxito
    } else {
        std::cout << "\nLa cedula ingresada NO es valida.\n" << std::endl;
        return false;  // Indicar que hubo un error al crear la cuenta
    }
}

void mostrarDatosDeUsuarioYPrestamo() {
    system("cls");
    tabla.visualizarDatosUsuarioEnArchivo("datos_prestamo.txt","datos_usuarios.txt");
    int indice=ingresar_enteros("\nIngrese el elemento que quiere recuperar");
    tabla.cargarDatosDesdeArchivo("datos_prestamo.txt",indice);
    tabla.mostrarTabla();

    pausa();
}

int main() {
    int opcion = 1;
    char key;

    do {
        mostrarMenu(opcion);
        key = _getch();

        switch (key) {
            case 72: // Flecha arriba
                if (opcion > 1) opcion--;
                break;
            case 80: // Flecha abajo
                if (opcion < 8) opcion++;
                break;
            case 13: // Enter
                if (opcion == 1) {
                    break;
                    
                } else if (opcion == 2) {
                    realizarOpcion1();
                    
                } else if (opcion == 3) {
                    //realizarOpcion2();
                    mostrarDatosDeUsuarioYPrestamo();
                } else if(opcion==4){
                    realizarOpcion3();
                    
                } else if(opcion==5){
                    realizarOpcion4();
                    
                } else if(opcion==6){
                    mostrarImagenGrupoDesarrollo();
                    
                } else if(opcion==7){
                    realizarOpcion5();
                    
                } else if(opcion==8){
                    realizarOpcion6();
                }
                break;
            default:
                break;
        }
    } while (true);

    return 0;
}
