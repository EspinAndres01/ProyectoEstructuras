#include "Fecha.h"
#include <chrono>
#include <iomanip>
#include <sstream>



Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {
    // Días festivos en Ecuador
    agregarDiaFestivo(1, 1);  // Año Nuevo
    agregarDiaFestivo(5, 24); // Batalla de Pichincha
    agregarDiaFestivo(8, 10); // Primer Grito de Independencia
    agregarDiaFestivo(10, 9); // Independencia de Guayaquil
    agregarDiaFestivo(11, 2); // Día de los Difuntos
    agregarDiaFestivo(11, 3); // Independencia de Cuenca
    agregarDiaFestivo(12, 25); // Navidad
    agregarDiaFestivo(12, 31); // Año Viejo
}
int Fecha::diaAleatorio = 0;
int Fecha::getAleatorio(){
    return diaAleatorio;
}
bool Fecha::validarFecha() {
    if (anio < 0 || mes < 1 || mes > 12 || dia < 1 || dia > diasEnMes(mes, anio))
        return false;

    return true;
}

bool Fecha::esAnioBisiesto(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Fecha::diasEnMes(int mes, int anio) {
    if (mes == 2) {
        return esAnioBisiesto(anio) ? 29 : 28;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    } else {
        return 31;
    }
}

bool Fecha::esDiaFestivo(int m, int d) {
    for (auto& festivo : diasFestivos) {
        if (festivo.first == m && festivo.second == d)
            return true;
    }
    return false;
}

void Fecha::agregarDiaFestivo(int m, int d) {
    if (!esDiaFestivo(m, d))
        diasFestivos.push_back(std::make_pair(m, d));
}
bool Fecha::esDiaHabil(const std::tm& fecha) {
    int mes = fecha.tm_mon + 1; // tm_mon va de 0 a 11
    int dia = fecha.tm_mday;

    // Verifica si es fin de semana (sábado o domingo)
    if (fecha.tm_wday == 0 || fecha.tm_wday == 6) {
        return false;
    }

    // Verifica si es un día festivo
    if (esDiaFestivo(mes, dia)) {
        return false;
    }

    return true;
}
/*
std::string Fecha::generarFechaPago(const std::string& fechaInicial, int mes) {
    std::tm tm = {};
    std::istringstream ss(fechaInicial);
    ss >> std::get_time(&tm, "%Y-%m-%d");

    // Crear un objeto Fecha para acceder a la función díasEnMes
    Fecha objetoFecha(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Obtener la fecha actual
    std::time_t t = std::time(nullptr);
    std::tm tmActual = *std::localtime(&t);
    tmActual.tm_hour = 0;
    tmActual.tm_min = 0;
    tmActual.tm_sec = 0;
    tmActual.tm_mday = objetoFecha.diasEnMes(tmActual.tm_mon + 1, tmActual.tm_year + 1900);
    std::time_t tActual = std::mktime(&tmActual);

    auto tp = std::chrono::system_clock::from_time_t(tActual);

    // Asumiendo que un mes tiene 30 días
    for (int i = 0; i < mes; ++i) {
        tp += std::chrono::hours(24); // Avanzar un día
        std::time_t newTime = std::chrono::system_clock::to_time_t(tp);
        std::tm newTm = *std::localtime(&newTime);
        while (!objetoFecha.esDiaHabil(newTm)) {
            tp += std::chrono::hours(24); // Si es fin de semana o día festivo, avanzar al siguiente día hábil
            newTime = std::chrono::system_clock::to_time_t(tp);
            newTm = *std::localtime(&newTime);
        }
    }

    // Agregar un mes de gracia antes del primer pago
    tp += std::chrono::hours(24 * 30);

    std::time_t newTime = std::chrono::system_clock::to_time_t(tp);
    std::tm newTm = *std::localtime(&newTime);
    std::ostringstream newDate;
    newDate << std::put_time(&newTm, "%Y-%m-%d");
    return newDate.str();
}
*/

int Fecha::obtenerDiaAleatorio() {
    // Generar un número aleatorio entre 1 y 31 (días en un mes) una vez
    if (diaAleatorio == 0) {
        srand(time(nullptr)); // Inicializar la semilla de rand con el tiempo actual
        diaAleatorio = rand() % 31 + 1;
    }
    return diaAleatorio;
}

std::string Fecha::generarFechaPago(const std::string& fechaInicial, int mes) {
    std::tm tm = {};
    std::istringstream ss(fechaInicial);
    ss >> std::get_time(&tm, "%Y-%m-%d");

    // Crear un objeto Fecha para acceder a la función díasEnMes
    Fecha objetoFecha(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Obtener el día de pago aleatorio una vez y almacenarlo
    int diaPago = objetoFecha.obtenerDiaAleatorio();
    std::cout << diaPago << " "; // Solo para verificar que se obtiene el mismo día aleatorio

    // Asumir que un mes tiene 30 días y avanzar los meses
    auto tp = std::chrono::system_clock::now(); // Declarar la variable tp aquí
    for (int i = 0; i < mes; ++i) {
        // Establecer la fecha de pago para el mes actual con el día aleatorio
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm tmPago = *std::localtime(&t);
        tmPago.tm_hour = 0;
        tmPago.tm_min = 0;
        tmPago.tm_sec = 0;
        tmPago.tm_mday = diaPago;
        std::time_t tPago = std::mktime(&tmPago);

        // Crear un time_point a partir de la fecha de pago
        tp = std::chrono::system_clock::from_time_t(tPago);

        // Si el día de pago cae en fin de semana o es festivo, avanzar al siguiente día hábil
        while (!objetoFecha.esDiaHabil(*std::localtime(&tPago))) {
            tPago += 24 * 60 * 60; // Avanzar un día
        }

        // Convertir time_t actualizado a time_point
        tp = std::chrono::system_clock::from_time_t(tPago);

        // Avanzar un mes
        tp += std::chrono::hours(24 * objetoFecha.diasEnMes((tp.time_since_epoch().count() + i) % 12 + 1, 0));
    }

    // Obtener la fecha final
    std::time_t finalTime = std::chrono::system_clock::to_time_t(tp);
    std::tm* finalTm = std::localtime(&finalTime);
    std::ostringstream finalDate;
    finalDate << std::put_time(finalTm, "%Y-%m-%d");
    return finalDate.str();
}