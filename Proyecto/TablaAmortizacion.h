#pragma once
#include "NodoAmortizacion.h"
#include "Fecha.h"
#include "TablaHash.h"
class TablaAmortizacion {
private:
    NodoAmortizacion* primero;
    NodoAmortizacion* ultimo;
    static unsigned int contadorArchivos;
public:
    TablaAmortizacion();
    void generarTabla(double prestamo, double tasaInteresAnual, int numeroCuotas, const std::string& fechaInicial, int diaAleatorio,const std::string& IDUsuario);
    void mostrarTabla();
    ~TablaAmortizacion();
    void guardarTablaCSV(const std::string& nombreDirectorio);
    void guardarDatosEnArchivo(double prestamo, double tasaInteresAnual, int numeroCuotas, int diaAleatorio);
    void cargarDatosDesdeArchivo(const std::string& nombreArchivo,int op);
    void visualizarDatosEnArchivo(const std::string& nombreArchivo);
    void crearRespaldo(const std::string& nombreArchivo);
    void listarRespaldos(const std::string& nombreArchivo) ;
    void restaurarRespaldo(const std::string& nombreArchivo, const std::string& respaldoSeleccionado);
    void guardaDatoUsuariosEnArchivo(std::string ID, std::string Cedula, std::string Nombre, std::string Apellido);
    void visualizarDatosUsuarioEnArchivo(const std::string& nombreArchivoUsuarios, const std::string& nombreArchivoPrestamos);
    void validarNumeroDeCuenta(const std::string archivoUsuarios, int indiceHash, TablaHash valor);
};


