/***********************************************************************
 * Module:  Datos.h
 * Author:  kibok
 * Modified: domingo, 7 de enero de 2024 12:45:27
 * Purpose: Declaration of the class Datos
 ***********************************************************************/
#include <iostream>
#include <string>
#if !defined(__Class_Diagram_1_Datos_h)
#define __Class_Diagram_1_Datos_h

class Datos
{
public:
   // Constructor
   Datos(std::string id, std::string ced, std::string nom, std::string apell)
        : ID(id), cedula(ced), nombre(nom), apellido(apell) {}
   std::string getID(void);
   void setID(std::string newID);
   std::string getCedula(void);
   void setCedula(std::string newCedula);
   std::string getNombre(void);
   void setNombre(std::string newNombre);
   std::string getApellido(void);
   void setApellido(std::string newApellido);
   Datos();
   ~Datos();
   void setDatos(std::string newID, std::string newCedula, std::string newNombre, std::string newApellido) {
        setID(newID);
        setCedula(newCedula);
        setNombre(newNombre);
        setApellido(newApellido);
   }

   // Comparación de objetos Datos basado en el ID
    bool operator==(const Datos& other) const {
        return ID == other.ID;
    }
    // Sobrecarga del operador de inserción <<
    friend std::ostream& operator<<(std::ostream& os, const Datos& datos) {
        os << "ID: " << datos.ID << ", Cedula: " << datos.cedula << ", Nombre: " << datos.nombre << ", Apellido: " << datos.apellido;
        return os;
    }

protected:
private:
   std::string ID;
   std::string cedula;
   std::string nombre;
   std::string apellido;


};

#endif