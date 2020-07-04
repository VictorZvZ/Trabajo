#pragma once
#include"AVL.h"
#include"Lista.h"
#include"Tabla.h"

class Gestora
{
	TablaBase<string>* tablita;
	int columnas;
public:
	Gestora() {}
	~Gestora() {}

	void TABLA() {
		cout << "Cantidad de columnas: "; cin >> columnas;
		tablita = new TablaBase<string>(columnas);
		tablita->CabeceraFila();
	}
	void Insertar() {
		tablita->agregarDatos();
	}
	void Indexar() {
		tablita->Indexacion();
	}
	void Seleccion() {
		tablita->ObtenerColumna();
	}
	void Filtracion() {
		tablita->Filtracion();
	}
	void Ordenamiento() {
		tablita->ordenamiento();
	}
	void MostrarTabla() {
		tablita->Exportacion();
	}
	void exportar() {
		tablita->Archivo();
	}
};