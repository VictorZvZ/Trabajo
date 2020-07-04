#pragma once
#include"Gestora.h"

void menucito(Gestora* TABLA) {
	int opcion;
	cout << "1. Creacion de la tabla" << endl;
	cout << "2. Inserccion de datos a la tabla" << endl;
	cout << "3. Indexaccion de los datos ingresados" << endl;
	cout << "4. Seleccion de la columna de datos" << endl;
	cout << "5. Filtracion de los datos ingresados" << endl;
	cout << "6. Ordenamiento de los datos ingresados" << endl;
	cout << "7. Mostrar la tabla" << endl;
	cout << "8. Exportar a archivo" << endl;
	cout << "Elija una opcion: ";
	while (1) {
		cin >> opcion;
		switch (opcion) {
		case 1:
			TABLA->TABLA();
			break;
		case 2:
			TABLA->Insertar();
			break;
		case 3:
			TABLA->Indexar();
			break;
		case 4:
			TABLA->Seleccion();
			break;
		case 5:
			TABLA->Filtracion();
			break;
		case 6:
			TABLA->Ordenamiento();
			break;
		case 7:
			TABLA->MostrarTabla();
			break;
		case 8:
			TABLA->exportar();
			break;
		default:break;
		}
	}
};