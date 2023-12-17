#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#if !defined(__Class_Diagram_1_Fecha_h)
#define __Class_Diagram_1_Fecha_h

class Fecha
{
private:
    int dia;
    int mes;
    int anio;
    std::vector<std::pair<int, int>> diasFestivos;
    static int diaAleatorio; 

public:
    Fecha(int d, int m, int a);
    Fecha();
    bool validarFecha();
    static std::string generarFechaPago(const std::string& fechaInicial, int mes);
    bool esDiaHabil(const std::tm& fecha);
    bool esAnioBisiesto(int anio);
    int diasEnMes(int mes, int anio);
    bool esDiaFestivo(int m, int d);
    void agregarDiaFestivo(int m, int d);
    int obtenerDiaAleatorio();
    int getAleatorio();
    
};

#endif
