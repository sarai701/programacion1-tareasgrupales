//Priscila Sarai Guzmán Calgua
#ifndef BANCO_H
#define BANCO_H

#include <iostream>
#include <string>
#include "Empleados.h"
#include "Cliente.h"
#include "Proveedores.h"
#include "Contabilidad.h"
#include "Auditoria.h"

using namespace std;

//Clase Banco
//Maneja la autenticación del usuario y la ejecución del menú principal.

class Banco {
private:
    const string usuarioCorrecto = "admin";  // Usuario predefinido
    const string contrasenaCorrecta = "1234"; // Contraseña predefinida

public:
    //Autentica al usuario pidiendo credenciales.
    //Permite 3 intentos antes de bloquear el acceso.
    //@return true si la autenticación es exitosa, false en caso contrario.
    bool autenticarUsuario();

    //Muestra el menú principal del sistema bancario.
    //Solo se accede si la autenticación es exitosa.
    void mostrarMenu();
};

#endif
