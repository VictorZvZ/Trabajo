#pragma once
#include "AVL.h"
template <typename T>

class Lista {
	struct Nodo {
		T elemento;
		Nodo* next;

		Nodo(T a = "", Nodo* b = nullptr) :elemento(a), next(b) {}
	};
	Nodo* inicio;
	int longitud;
public:
	Lista(int columnas) :inicio(nullptr), longitud(columnas) {}
	~Lista() {
		Nodo* aux = inicio;
		while (aux != nullptr) {
			aux = inicio;
			inicio = inicio->next;
			delete aux;
		}

	}
	void start(T a) {
		Nodo* nuevo = new Nodo(a, inicio);
		if (nuevo != nullptr) {
			inicio = nuevo;
		}
	}

	void pos(T a, int b) {
		if (b > longitud) {
			return;
		}
		if (b == 0) {
			start(a);
		}
		else {
			Nodo* aux = inicio;
			for (int i = 1; i < b; ++i) {
				aux = aux->next;
			}
			Nodo* nuevo = new Nodo(a, aux->next);
			if (nuevo != nullptr) {
				aux->next = nuevo;
			}
		}
	}
	void end(T a) {
		Posicion(a, longitud);
	}
	void modInicial(T a) {
		if (longitud > 0) {
			inicio->elemento = a;
		}
	}
	void modPos(T a, int b) {
		if (b >= 0 && b < longitud) {
			Nodo* aux = inicio;
			for (int i = 0; i < b; ++i) {
				aux = aux->next;
			}
			aux = elemento = a;
		}
	}
	void modFinal(T a) {
		modPos(a, longitud - 1);
	}
	T obtenerPos(int a) {
		if (a >= 0 && a < longitud) {
			Nodo* aux = inicio;
			for (int i = 0; i < a; ++i) {
				aux = aux->next;
			}
			return aux->elemento;
		}
		else {
			return " ";
		}
	}
	T obtenerI() {
		return obtenerPos(0);
	}
	T obtenerF() {
		return obtenerPos(longitud - 1);
	}
};