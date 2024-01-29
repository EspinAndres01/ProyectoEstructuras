#include <iostream>
#include <string>
#include <iomanip> // Para usar std::setw y std::setfill

// Función para generar un nuevo ID
std::string generarID() {
    static int contador = 0; // Variable estática para llevar la cuenta de los registros

    // Crear el formato del ID con ceros a la izquierda (L + 4 dígitos)
    std::string ID = "L" + std::to_string(contador);
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << contador;
    ID = "L" + ss.str();

    contador++; // Incrementar el contador para el próximo registro
    return ID;
}

// Función para generar y mostrar múltiples IDs
void generarYMostrarIDs(int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        std::string nuevoID = generarID();
        std::cout << "Nuevo ID generado: " << nuevoID << std::endl;
    }
}

// Función para generar un nuevo número de cuenta
std::string generarNumeroCuenta() {
    static int contador = 0; // Variable estática para llevar la cuenta de las cuentas generadas

    // Crear el formato del número de cuenta (CCCC-BB-SS-NNNNNNNN)
    std::string numeroCuenta = "";
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << contador; // Código de cliente
    numeroCuenta += ss.str() + "-";

    ss.str(""); // Limpiar el stringstream
    ss << std::setw(2) << std::setfill('0') << contador % 100; // Código de banco
    numeroCuenta += ss.str() + "-";

    ss.str(""); // Limpiar el stringstream
    ss << std::setw(2) << std::setfill('0') << (contador / 100) % 100; // Código de sucursal
    numeroCuenta += ss.str() + "-";

    ss.str(""); // Limpiar el stringstream
    ss << std::setw(8) << std::setfill('0') << contador * 10; // Número de cuenta
    numeroCuenta += ss.str();

    contador++; // Incrementar el contador para el próximo número de cuenta
    return numeroCuenta;
}

// Función para generar y mostrar múltiples números de cuenta
void generarYMostrarNumerosCuenta(int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        std::string nuevoNumeroCuenta = generarNumeroCuenta();
        std::cout << "Nuevo número de cuenta generado: " << nuevoNumeroCuenta << std::endl;
    }
}