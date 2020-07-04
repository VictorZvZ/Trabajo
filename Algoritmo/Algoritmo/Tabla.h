#pragma once
#include"AVL.h"
#include"Lista.h"
#include <iomanip>
#include <sstream>
#include<fstream>
#include <vector>
template <typename T>
class TablaBase {
	Lista<T>** listita;
	vector<Lista<T>**> auxiliares;
	ArbolBalanceado<Lista<T>*, string>* arbolito;
	int numColum;
	int numfil;
	int numaux;
	vector<int> filaux;
	T* nomColum;
public:
	TablaBase(int columnas) {
		listita = new Lista<T>*;
		numColum = columnas;
		numfil = 0;
		numaux = 0;
		nomColum = new T[columnas];
		auto k1 = [](Lista<T>* a) { return a->obtenerPos(0); };
		arbolito = new ArbolBalanceado<Lista<T>*, string>(k1);
	}
	~TablaBase() {}
	void CabeceraFila() {
		string nombres;
		for (int i = 0; i < numColum; ++i) {
			cout << "Nombre de la columna: " << i + 1 << ": "; cin >> nombres;
			nomColum[i] = nombres;
		}
	}
	void agregarDatos() {
		listita[numfil] = new Lista<T>(numColum);
		string datos;
		for (int i = 0; i < numColum; ++i) {
			cout << "Datos para: " << nomColum[i] << ": "; cin >> datos;
			listita[numfil]->pos(datos, i);
		}
		numfil++;
	}


	void Indexacion() {
		auto k1 = [](Lista<T>* a) { return a->obtenerPos(0); };
		ArbolBalanceado<Lista<T>*, string>* aux = new ArbolBalanceado<Lista<T>*, string>(k1);
		for (int i = 0; i < numfil; ++i) {
			aux->Ingresar(listita[i]);
		}
		arbolito = aux;

		int au = numColum;
		auto print = [&](Lista<T>* a) {
			for (int i = 0; i < au; ++i) {
				cout << a->obtenerPos(i) << " ";
			}
			cout << endl;
		};

		for (int i = 0; i < numColum; ++i) {
			cout << nomColum[i] << " ";
		}
		cout << endl;
		arbolito->inOrder(print);
	}
	void ObtenerColumna() {
		string seleccion;
		cout << "Ingrese el nombre de la columna que desea seleccionar: ";
		cin >> seleccion;
		int nColumna;
		for (int i = 0; i < numColum; ++i) {
			if (seleccion == nomColum[i]) nColumna = i;
		}
		cout << nomColum[nColumna] << endl;
		for (int i = 0; i < numfil; ++i) {
			cout << listita[i]->obtenerPos(nColumna) << endl;
		}
	}

	void Filtracion() {
		int opaux;
		cout << "Ingrese la tabla a filtrar:" << endl;
		cout << "1. Tabla Base" << endl;
		for (int i = 0; i < numaux; ++i) {
			cout << i + 2 << ". Tabla Auxiliar " << i + 1 << endl;
		}
		cout << "Escriba la opcion de la tabla: "; cin >> opaux;

		Lista<T>** auxiliar = new Lista<T>*;
		int faux = 0;

		char opcion;
		cout << "Tipo de filtros:" << endl;
		cout << "a. Mayor" << endl;
		cout << "b. Menor" << endl;
		cout << "c. Igual" << endl;
		cout << "d. Inicia con" << endl;
		cout << "e. Finaliza con" << endl;
		cout << "f. Esta contenida en" << endl;
		cout << "g. No esta contenida en" << endl;
		cout << "Escriba la opción a filtrar: "; cin >> opcion;
		switch (opcion) {
		case 'a': {
			string colu;
			int colum;
			T cantidad;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "Ingrese el elemento mayor a: "; cin >> cantidad;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);
			}
			cout << endl;
			if (opaux == 1) {
				for (int i = 0; i < numfil; ++i) {
					if (cantidad < listita[i]->obtenerPos(colum)) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(listita[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int i = 0; i < filaux[opaux - 2]; ++i) {
					if (cantidad < auxiliar2[i]->obtenerPos(colum)) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << auxiliar2[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(auxiliar2[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;

		}; break;
		case 'b': {
			string colu;
			int colum;
			T cantidad;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "Ingrese el elemento menor a: "; cin >> cantidad;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);
			}
			cout << endl;
			if (opaux == 1) {
				for (int i = 0; i < numfil; ++i) {
					if (cantidad > listita[i]->obtenerPos(colum)) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(listita[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int i = 0; i < filaux[opaux - 2]; ++i) {
					if (cantidad > auxiliar2[i]->obtenerPos(colum)) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << auxiliar2[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(auxiliar2[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;

		}; break;
		case 'c': {
			string colu;
			int colum;
			T cantidad;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "Ingrese el elemento a buscar: "; cin >> cantidad;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);
			}
			cout << endl;
			if (opaux == 1) {
				for (int i = 0; i < numfil; ++i) {
					if (cantidad == listita[i]->obtenerPos(colum)) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(listita[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int i = 0; i < filaux[opaux - 2]; ++i) {
					if (cantidad == auxiliar2[i]->obtenerPos(colum)) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << auxiliar2[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(auxiliar2[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;

		}; break;
		case 'd': {
			string colu;
			int colum;
			T letra;
			string aux;
			string aux2;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "Ingrese la letra con la que inicia: "; cin >> letra;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);

			}
			cout << endl;
			if (opaux == 1) {
				for (int i = 0; i < numfil; ++i) {
					aux = listita[i]->obtenerPos(colum);
					aux2 = aux.front();
					if (letra == aux2) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(listita[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int i = 0; i < filaux[opaux - 2]; ++i) {
					aux = auxiliar2[i]->obtenerPos(colum);
					aux2 = aux.front();
					if (letra == aux2) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << auxiliar2[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(auxiliar2[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;
		}; break;
		case 'e': {
			string colu;
			int colum;
			T letra;
			string aux;
			string aux2;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "Ingrese la letra con la que Finaliza: "; cin >> letra;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);

			}
			cout << endl;
			if (opaux == 1) {
				for (int i = 0; i < numfil; ++i) {
					aux = listita[i]->obtenerPos(colum);
					for (int i = 0; i < aux.length(); i++) {
						aux2 = aux.at(i);
					}
					if (letra == aux2) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(listita[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int i = 0; i < filaux[opaux - 2]; ++i) {
					aux = auxiliar2[i]->obtenerPos(colum);
					for (int i = 0; i < aux.length(); i++) {
						aux2 = aux.at(i);
					}
					if (letra == aux2) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << auxiliar2[i]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(auxiliar2[i]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;
		}; break;
		case 'f': {
			string colu;
			int colum;
			T buscar;
			string aux;
			string aux2;
			string b;
			int v = 0, cont = 0;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "Esta contenida en "; cin >> buscar;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);

			}
			cout << endl;
			b = buscar;
			if (opaux == 1) {
				for (int k = 0; k < numfil; ++k) {
					aux = listita[k]->obtenerPos(colum);
					aux2 = aux;
					for (int i = 0; i < aux2.length(); i++) {
						if (v != b.length()) {
							if (aux2.at(i) == b.at(v)) {
								if (v == 0) {
									cont = i;
									v++;
								}
								if (v != 0) {
									if (i == cont + 1) {
										cont = i;
										v++;
										if (buscar.length() == v) {
											auxiliar[faux] = new Lista<T>(numColum);
											for (int j = 0; j < numColum; ++j) {
												cout << setw(15) << listita[k]->obtenerPos(j) << "|" << setw(15);
												auxiliar[faux]->pos(listita[k]->obtenerPos(j), j);
											}
											faux++;
											cout << endl;
										}
									}
								}
							}
						}
					}
					v = 0; cont = 0;
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int k = 0; k < filaux[opaux - 2]; ++k) {
					aux = auxiliar2[k]->obtenerPos(colum);
					aux2 = aux;
					for (int i = 0; i < aux2.length(); i++) {
						if (v != b.length()) {
							if (aux2.at(i) == b.at(v)) {
								if (v == 0) {
									cont = i;
									v++;
								}
								if (v != 0) {
									if (i == cont + 1) {
										cont = i;
										v++;
										if (buscar.length() == v) {
											auxiliar[faux] = new Lista<T>(numColum);
											for (int j = 0; j < numColum; ++j) {
												cout << setw(15) << auxiliar2[k]->obtenerPos(j) << "|" << setw(15);
												auxiliar[faux]->pos(auxiliar2[k]->obtenerPos(j), j);
											}
											faux++;
											cout << endl;
										}
									}
								}
							}
						}
					}
					v = 0; cont = 0;
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;
		}; break;
		case 'g': {
			string colu;
			int colum;
			T buscar;
			string aux;
			string aux2;
			string b;
			int v = 0, cont = 0;
			cout << "Ingrese la columna que quiere filtrar: "; cin >> colu;
			cout << "No esta contenida en "; cin >> buscar;
			for (int i = 0; i <= numColum; ++i) {
				if (colu == nomColum[i]) {
					colum = i;
				}
			}
			for (int i = 0; i < numColum; ++i) {
				cout << setw(15) << nomColum[i] << "|" << setw(15);

			}
			cout << endl;
			b = buscar;
			if (opaux == 1) {
				for (int k = 0; k < numfil; ++k) {
					aux = listita[k]->obtenerPos(colum);
					aux2 = aux;

					for (int i = 0; i < aux2.length(); i++)
					{

						if (v != b.length()) {
							if (aux2.at(i) == b.at(v)) {
								if (v == 0) {
									cont = i;
									v++;
								}
								if (v != 0) {
									if (i == cont + 1) {
										cont = i;
										v++;
										if (buscar.length() == v) {
											cont = 1;
										}
									}
								}
							}
						}
					}
					if (cont == 0) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << listita[k]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(listita[k]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
					cont = 0; v = 0;
				}
			}
			else if (opaux > 1 && opaux < numaux + 2) {
				Lista<T>** auxiliar2 = new Lista<T>*;
				auxiliar2 = auxiliares[opaux - 2];
				for (int k = 0; k < filaux[opaux - 2]; ++k) {
					aux = auxiliar2[k]->obtenerPos(colum);
					aux2 = aux;

					for (int i = 0; i < aux2.length(); i++)
					{

						if (v != b.length()) {
							if (aux2.at(i) == b.at(v)) {
								if (v == 0) {
									cont = i;
									v++;
								}
								if (v != 0) {
									if (i == cont + 1) {
										cont = i;
										v++;
										if (buscar.length() == v) {
											cont = 1;
										}
									}
								}
							}
						}
					}
					if (cont == 0) {
						auxiliar[faux] = new Lista<T>(numColum);
						for (int j = 0; j < numColum; ++j) {
							cout << setw(15) << auxiliar2[k]->obtenerPos(j) << "|" << setw(15);
							auxiliar[faux]->pos(auxiliar2[k]->obtenerPos(j), j);
						}
						faux++;
						cout << endl;
					}
					cont = 0; v = 0;
				}
			}
			auxiliares.push_back(auxiliar);
			filaux.push_back(faux);
			numaux++;
		}; break;
		}

	}

	void ordenamiento() {
		int op;
		cout << setw(1) << "Ordenar:\n";
		for (int i = 0; i < numColum; i++) {
			cout << i + 1 << ". " << nomColum[i] << endl;
		}
		cin >> op;

		int au = numColum;
		auto print = [&](Lista<T>* a) {
			for (int i = 0; i < au; ++i) {
				cout << setw(15) << a->obtenerPos(i) << "|" << setw(15);
			}
			cout << endl;
		};

		auto k1 = [&](Lista<T>* a) { return a->obtenerPos(op - 1); };
		ArbolBalanceado<Lista<T>*, string> *aux = new ArbolBalanceado<Lista<T>*, string>(k1);
		for (int i = 0; i < numfil; ++i) {
			aux->Ingresar(listita[i]);
		}

		for (int i = 0; i < numColum; ++i) {
			cout << setw(15) << nomColum[i] << "|" << setw(15);
		}
		cout << endl;
		aux->inOrder(print);
	}

	void Exportacion() {
		int opt;
		cout << "Ingrese tabla a mostrar:" << endl;
		cout << "1. Tabla Base" << endl;
		for (int i = 0; i < numaux; ++i) {
			cout << i + 2 << ". Tabla auxiliar " << i + 1 << endl;
		}
		cout << "Ingrese la opcion de la tabla: "; cin >> opt;

		for (int i = 0; i < numColum; ++i) {
			cout << setw(15) << nomColum[i] << "|" << setw(15);
		}
		cout << endl;
		if (opt == 1) {
			for (int i = 0; i < numfil; ++i) {
				for (int j = 0; j < numColum; ++j) {
					cout << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
				}
				cout << endl;
			}
		}
		else if (opt > 1 && opt < numaux + 2) {
			Lista<T>** auxiliar = new Lista<T>*;
			auxiliar = auxiliares[opt - 2];
			for (int i = 0; i < filaux[opt - 2]; ++i) {
				for (int j = 0; j < numColum; ++j) {
					cout << setw(15) << auxiliar[i]->obtenerPos(j) << "|" << setw(15);
				}
				cout << endl;
			}
		}
	}

	void Archivo() {
		int opaux;
		cout << "Ingrese la tabla a exportar:" << endl;
		cout << "1. Tabla Base" << endl;
		for (int i = 0; i < numaux; ++i) {
			cout << i + 2 << ". Tabla Auxiliar " << i + 1 << endl;
		}
		cout << "Escriba la opcion de la tabla: "; cin >> opaux;

		ofstream archivo;
		string nombre, extension, narchiv;
		int n;
		cout << "ingrese nombre del archivo:  ";
		cin >> nombre;
		cout << "elija extension [1].txt          [2] .csv        [3]otro" << endl;
		cin >> n;
		switch (n)
		{
		case 1: { extension = ".txt"; narchiv = nombre + extension; }; break;
		case 2: {extension = ".csv"; narchiv = nombre + extension; }; break;
		case 3: {cout << "ingrese extension:  "; cin >> extension; narchiv = nombre + extension; }; break;
		default:
			break;
		};
		archivo.open(narchiv, ios::out);

		for (int i = 0; i < numColum; ++i) {
			archivo << setw(15) << nomColum[i] << "|" << setw(15);
		}
		archivo << endl;

		if (opaux == 1) {
			for (int i = 0; i < numfil; ++i) {
				for (int j = 0; j < numColum; ++j) {
					archivo << setw(15) << listita[i]->obtenerPos(j) << "|" << setw(15);
				}
				archivo << endl;
			}
		}
		else if (opaux > 1 && opaux < numaux + 2) {
			Lista<T>** auxiliar = new Lista<T>*;
			auxiliar = auxiliares[opaux - 2];
			for (int i = 0; i < filaux[opaux - 2]; ++i) {
				for (int j = 0; j < numColum; ++j) {
					archivo << setw(15) << auxiliar[i]->obtenerPos(j) << "|" << setw(15);
				}
			}
		}
		archivo.close();

	}
};