#include "iostream.h"
#include "string.h"
#include "stdlib.h"

class Variable;

class Contexto {
	char n[10][20];
	int b[10];
	int ind;
public:
	Contexto() {
		int i;
		for(i=0; i <10; i++)
			strcpy(n[i], "?");
		ind = 0;
	}

	void asignar(Variable *p, int b);
	int getValor(char *nombre);
};

//----------------------------------------------------------------------------------------//

class E {
public:
	E() {}
	~E() {}
	virtual int getValor(Contexto &) = 0;
};

//----------------------------------------------------------------------------------------//

class T : public E {
public:
	T() {}
	~T() {}
};

class Suma : public E {
	E *op1;
	T *op2;
public:
	Suma(E *op1, T *op2) {
		this->op1 = op1;
		this->op2 = op2;
	}

	~Suma() {
	}

	int getValor(Contexto &contexto) {
		return op1->getValor(contexto) + op2->getValor(contexto);
	}
};

class Resta : public E {
	E *op1;
	T *op2;
public:
	Resta(E *op1, T *op2) {
		this->op1 = op1;
		this->op2 = op2;
	}

	~Resta() {
	}

	int getValor(Contexto &contexto) {
		return op1->getValor(contexto) - op2->getValor(contexto);
	}
};

//----------------------------------------------------------------------------------------//

class A : public T {
public:
	A() {}
	~A() {}
};

class Multiplica : public T {
	T *op1;
	A *op2;
public:
	Multiplica(T *op1, A *op2) {
		this->op1 = op1;
		this->op2 = op2;
	}

	~Multiplica() {
	}

	int getValor(Contexto &contexto) {
		return op1->getValor(contexto) * op2->getValor(contexto);
	}
};

class Divide : public T {
	T *op1;
	A *op2;
public:
	Divide(T *op1, A *op2) {
		this->op1 = op1;
		this->op2 = op2;
	}

	~Divide() {
	}

	int getValor(Contexto &contexto) {
		return op1->getValor(contexto) / op2->getValor(contexto);
	}
};

//----------------------------------------------------------------------------------------//

class Constante : public A {
	int b;
public:
	Constante(int b) {
		this->b = b;
	}
	
	~Constante() {
	}
	
	int getValor(Contexto &contexto) {
		return b;
	}
};

class Variable : public A {
	char nombre[20];
public:
	Variable(char nombre[]) {
		strcpy(this->nombre, nombre);
	}
	
	~Variable() {
	}

	int getValor(Contexto &contexto) {
		return contexto.getValor(nombre);
	}

	void getNombre(char aux[]) {
		strcpy(aux, nombre);
	}
};

//----------------------------------------------------------------------------------------//

void Contexto::asignar(Variable *p, int b) {
	char aux[20];
	p->getNombre(aux);
	strcpy(n[ind], aux);
	this->b[ind] = b;
	ind++;
}

int Contexto::getValor(char *nombre) {
	int i;
	for(i=0; (strcmp(n[i], "?") != 0) && (strcmp(n[i], nombre) != 0); i++) {
		// ;
	}
	if(strcmp(n[i], "?") == 0) {
		cout<< "Error!. No existe variable.";
		exit(1);
	}

	return b[i];
}

//----------------------------------------------------------------------------------------//

void main() {
	Contexto contexto;

	// Declaracion de Variables
	Variable *x = new Variable("x");
	Variable *y = new Variable("y");

	// Asignacion de variables
	contexto.asignar(x, 8);
	contexto.asignar(y, 4);

	// Declaracion de constantes
	Constante *constante = new Constante(2);

	// Operacion compuesta (constante * x) + (y / constante)
	E *operacion = new Suma(new Multiplica(constante, x), new Divide(y, constante));

	// Operaciones de E
	E *eSuma = new Suma(x, y);
	E *eResta = new Resta(x, y);

	// Operaciones de T
	T *tMultiplica = new Multiplica(x, y);
	T *tDivide = new Divide(x, y);

	cout<< "Valor Variable x = " << contexto.getValor("x") << endl;
	cout<< "Valor Variable y = " << contexto.getValor("y") << endl;
	cout<< "Valor Constante = " << constante->getValor(contexto) << endl;
	cout<< endl;

	cout<< "Suma: " << eSuma->getValor(contexto) << endl;
	cout<< "Resta: " << eResta->getValor(contexto) << endl;
	cout<< "Multiplicacion: " << tMultiplica->getValor(contexto) << endl;
	cout<< "Division: " << tDivide->getValor(contexto) << endl;
	cout<< "Operacion compuesta: " << operacion->getValor(contexto) << endl;

	delete x;
	delete y;
}
