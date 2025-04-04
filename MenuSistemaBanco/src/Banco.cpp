//Priscila Sarai Guzmán Calgua
#include "Banco.h"

using namespace std;

//Solicita usuario y contraseña al usuario.
//Permite 3 intentos antes de bloquear el acceso.
//@return true si las credenciales son correctas, false si se agotan los intentos.
bool Banco::autenticarUsuario() {
    string usuario, contrasena;
    int intentos = 3;

    while (intentos > 0) {
        cout << "\n===== AUTENTICACION =====\n";
        cout << "Usuario: ";
        cin >> usuario;
        cout << "Contraseña: ";
        cin >> contrasena;

        if (usuario == usuarioCorrecto && contrasena == contrasenaCorrecta) {
            cout << "Autenticacion exitosa. Bienvenido!\n";
            return true;
        } else {
            intentos--;
            cout << "Usuario o contraseña incorrectos. Intentos restantes: " << intentos << "\n";
        }
    }

    cout << "Acceso bloqueado. Intentelo más tarde.\n";
    return false;
}

//Muestra el menú de opciones del sistema bancario.
//Se ejecuta en un bucle hasta que el usuario elija salir.
void Banco::mostrarMenu() {
    if (!autenticarUsuario()) return;  // Si falla la autenticación, se cierra el programa

    int opcion;
    Empleado empleado;
    Cliente cliente;
    Proveedor proveedor;
    Contabilidad contabilidad;
    Auditoria auditoria;

    do {
        cout << "\n===== MENU SISTEMA BANCARIO =====\n";
        cout << "1. Gestionar Nominas\n";
        cout << "2. Realizar Pagos de Servicios\n";
        cout << "3. Consultar Saldo y Movimientos\n";
        cout << "4. Registrar Proveedores y Facturas\n";
        cout << "5. Generar Reportes Financieros\n";
        cout << "6. Auditoria de Transacciones\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                empleado.gestionarNomina();
                break;
            case 2:
                cliente.realizarPago();
                break;
            case 3:
                cliente.consultarSaldo();
                break;
            case 4:
                proveedor.registrarFactura();
                break;
            case 5:
                contabilidad.generarReporte();
                break;
            case 6:
                auditoria.revisarTransacciones();
                break;
            case 7:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida, intente nuevamente.\n";
        }
    } while (opcion != 7);
}
