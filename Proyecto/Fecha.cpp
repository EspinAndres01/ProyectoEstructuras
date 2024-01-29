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
    agregarDiaFestivo(2, 12); // Carnaval dia 1
    agregarDiaFestivo(2, 13); // Carnaval dia 2
    agregarDiaFestivo(3, 29); // Viernes Santo 
    agregarDiaFestivo(5, 3); // Dia del trabajo 
}   

Fecha::Fecha(){};
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

    // Obtener la fecha actual
    auto tpActual = std::chrono::system_clock::now();
    std::time_t tActual = std::chrono::system_clock::to_time_t(tpActual);
    std::tm tmActual = *std::localtime(&tActual);
    std::time_t tPago = tActual;

    // Verificar si la fecha actual es un día laboral y mantenerla si lo es
    if (objetoFecha.esDiaHabil(tmActual)) {
        // Si la fecha actual es laboral, establecerla como fecha de pago
        tPago = tActual;
    } else {
        // Si no es un día laboral, encontrar el próximo día hábil
        do {
            tPago += 24 * 60 * 60; // Avanzar un día
            tmActual = *std::localtime(&tPago);
        } while (!objetoFecha.esDiaHabil(tmActual));
    }

    // Crear un time_point a partir de la fecha de pago
    auto tp = std::chrono::system_clock::from_time_t(tPago);

    // Avanzar los meses
    for (int i = 0; i < mes; ++i) {
        // Avanzar al siguiente mes
        tmActual.tm_mon++; // Avanzar al siguiente mes
        if (tmActual.tm_mon >= 12) {
            tmActual.tm_mon = 0;
            tmActual.tm_year++; // Avanzar al siguiente año si es necesario
        }

        // Establecer la fecha de pago para el mes actual con el día aleatorio
        tmActual.tm_mday = diaPago;
        tPago = std::mktime(&tmActual);

        // Si el día de pago cae en fin de semana, es festivo o supera los días del mes, avanzar al siguiente día hábil
        while (!objetoFecha.esDiaHabil(*std::localtime(&tPago)) || objetoFecha.esDiaFestivo(tmActual.tm_mon + 1, tmActual.tm_mday) || tmActual.tm_mday > objetoFecha.diasEnMes(tmActual.tm_mon + 1, tmActual.tm_year + 1900)) {
            tPago += 24 * 60 * 60; // Avanzar un día
            tmActual = *std::localtime(&tPago);
        }

        // Convertir time_t actualizado a time_point
        tp = std::chrono::system_clock::from_time_t(tPago);
    }

    // Obtener la fecha final
    std::time_t finalTime = std::chrono::system_clock::to_time_t(tp);
    std::tm* finalTm = std::localtime(&finalTime);
    std::ostringstream finalDate;
    finalDate << std::put_time(finalTm, "%Y-%m-%d");
    return finalDate.str();
}
