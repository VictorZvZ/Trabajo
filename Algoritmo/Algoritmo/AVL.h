#pragma once
#include <iostream>
#include <functional>
#include<algorithm> 
#include<string>
using namespace std;
using namespace System;

template<typename T, typename R = T>
class ArbolBalanceado {
	struct Nodo {
		T elemento;
		Nodo* izquierda;
		Nodo* derecha;
		int altura;

		Nodo(T a) : elemento(a), altura(0), izquierda(nullptr), derecha(nullptr) {}
	};

	Nodo* root;
	function<R(T)> constante;
	int longitud;

public:
	ArbolBalanceado(function<R(T)>key = [](T a) {return a}) : constante(key), root(nullptr), longitud(0) {}
	ArbolBalanceado() {}

	void Ingresar(T a) {
		Ingresar(root, a);
	}
	void Ingresar(Nodo*& a, T k) {
		if (a == nullptr) {
			a = new Nodo(k);
			longitud++;
		}
		else {
			if (constante(k) < constante(a->elemento)) {
				Ingresar(a->izquierda, k);
			}
			else {
				Ingresar(a->derecha, k);
			}
			Balance(a);
		}
	}
	void inOrder(function<void(T)>procces) {
		inOrder(root, procces);
	}
	int Altura(Nodo* a) {
		return a == nullptr ? -1 : a->altura;
	}

	void NuevaAltura(Nodo* a) {
		if (a != nullptr) {
			int h1 = Altura(a->izquierda);
			int h2 = Altura(a->derecha);

			a->altura = std::max(h1, h2) + 1;
		}
	}
	void raizIzquierda(Nodo*& a) {
		Nodo* aux = a->derecha;
		a->derecha = aux->izquierda;
		NuevaAltura(a);
		aux->izquierda = a;
		NuevaAltura(aux);
		a = aux;
	}

	void raizDerecha(Nodo*& a) {
		Nodo* aux = a->izquierda;
		a->izquierda = aux->derecha;
		NuevaAltura(a);
		aux->derecha = a;
		NuevaAltura(aux);
		a = aux;
	}

	void Balance(Nodo*& a) {
		int h1 = Altura(a->izquierda);
		int h2 = Altura(a->derecha);

		if (h2 - h1 < -1) {
			h1 = Altura(a->izquierda->izquierda);
			h2 = Altura(a->izquierda->derecha);
			if (h2 > h1) {
				raizIzquierda(a->izquierda);
			}
			raizDerecha(a->derecha);
		}
		else if (h2 - h1 > 1) {
			h1 = Altura(a->derecha->izquierda);
			h2 = Altura(a->derecha->derecha);
			if (h1 > h2) {
				raizDerecha(a->derecha);
			}
			raizIzquierda(a);
		}
		else {
			NuevaAltura(a);
		}
	}

	void inOrder(Nodo* a, function<void(T)>process) {
		if (a != nullptr) {
			inOrder(a->izquierda, process);
			process(a->elemento);
			inOrder(a->derecha, process);
		}
	}

};