#include "iostream.h"
#include "string.h"
#include "stdlib.h"
#define bool int
#define true 1
#define false 0

class Context;

class BoolExp {
public:
	BoolExp() {}
	~BoolExp() {}
	virtual bool evaluar(Context &) = 0;
};

class VarExp;

class Context {
	char n[10][20];
	bool b[10];
	int ind;
public:
	Context();
	void asignar(VarExp *p, bool b);
	bool buscar(char *nombre);
};

class VarExp : public BoolExp {
	char nombre[20];
public:
	VarExp(char nombre[]) {
		strcpy(this->nombre, nombre);
	}
	
	~VarExp() {
	}

	bool evaluar(Context &contexto) {
		return contexto.buscar(nombre);
	}

	void devNombre(char aux[]) {
		strcpy(aux, nombre);
	}
};

Context::Context() {
	int i;
	for(i=0; i <10; i++) {
		strcpy(n[i], "?");
	}
	ind = 0;
}

void Context::asignar(VarExp *p, bool b) {
	char aux[20];
	p->devNombre(aux);
	strcpy(n[ind], aux);
	this->b[ind] = b;
	ind++;
}

bool Context::buscar(char *nombre) {
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

class Constante : public BoolExp {
	bool b;
public:
	Constante(bool b) {
		this->b = b;
	}
	
	~Constante() {
	}
	
	bool evaluar(Context &contexto) {
		return b;
	}
};

class AndExp : public BoolExp {
	BoolExp *op1;
	BoolExp *op2;
public:
	AndExp(BoolExp *op1, BoolExp *op2) {
		this->op1 = op1;
		this->op2 = op2;
	}

	~AndExp() {
	}

	bool evaluar(Context &contexto) {
		return op1->evaluar(contexto) && op2->evaluar(contexto);
	}
};

class OrExp : public BoolExp {
	BoolExp *op1;
	BoolExp *op2;
public:
	OrExp(BoolExp *op1, BoolExp *op2) {
		this->op1 = op1;
		this->op2 = op2;
	}

	~OrExp() {
	}

	bool evaluar(Context &contexto) {
		return op1->evaluar(contexto) || op2->evaluar(contexto);
	}
};

class NotExp : public BoolExp {
	BoolExp *op1;
public:
	NotExp(BoolExp *op1) {
		this->op1 = op1;
	}

	~NotExp() {
	}

	bool evaluar(Context &contexto) {
		return !op1->evaluar(contexto);
	}
};

void main() {
	VarExp *x = new VarExp("x");
	VarExp *y = new VarExp("y");

	Constante *t = new Constante(true);
	AndExp *p = new AndExp(t, x);
	NotExp *q = new NotExp(x);
	AndExp *r = new AndExp(y, q);

	BoolExp *e;
	Context contexto;

	contexto.asignar(x, false);
	contexto.asignar(y, true);

	//e = new OrExp( new AndExp( new Constante(true), x), new AndExp(y, new NotExp(x) ) );
	e = new OrExp(p, r);

	bool result = e->evaluar(contexto);

	if(result)
		cout<< "true" << endl;
	else
		cout<< "false" << endl;

	delete t;
	delete p;
	delete q;
	delete r;
	delete x;
	delete y;
}