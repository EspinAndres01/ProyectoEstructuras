#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void copyFiles(const std::string& source, const std::string& destination) {
    try {
        for (const auto& entry : fs::directory_iterator(source)) {
            fs::copy(entry.path(), destination / entry.path().filename());
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error al copiar archivos: " << e.what() << "\n";
        throw; // Relanza la excepción para manejarla en el main si es necesario
    }
}

bool validateDirectory(const std::string& directory) {
    if (fs::exists(directory)) {
        std::cout << "El directorio de instalación ya existe.\n";
        return false;
    }
    return true;
}

int main() {
    std::string destination;
    std::string source;
    
    std::cout << "Bienvenido al asistente de instalacion.\n";
    
    std::cout << "Por favor, ingrese la ruta de instalacion: ";
    std::getline(std::cin, destination);
    
    std::cout << "Por favor, ingrese la ruta del directorio de la aplicacion: ";
    std::getline(std::cin, source);

    if (!validateDirectory(destination)) {
        return 1;
    }

    try {
        fs::create_directory(destination);
        copyFiles(source, destination);
        std::cout << "Instalación completada.\n";
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error durante la instalacion: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
