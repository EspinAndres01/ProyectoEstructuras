/***********************************************************************
 * Module:  Menu.h
 * Author:  kibok
 * Modified: s�bado, 2 de diciembre de 2023 19:44:59
 * Purpose: Declaration of the class Menu
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Menu_h)
#define __Class_Diagram_1_Menu_h

#include <iostream>
#include <vector>

class Menu
{
public:
   Menu(const std::string& titulo);
   void mostrar(const std::vector<std::string>& opciones, int opcionSeleccionada);
   int obtenerOpcion(const std::vector<std::string>& opciones);
   void manejarOpcion(int opcion, const std::vector<std::string>& opciones);
   void iniciar(const std::vector<std::string>& opciones);
   ~Menu();

protected:
private:
   std::string titulo;


};

#endif