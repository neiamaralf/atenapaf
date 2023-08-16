#ifndef palavraH
#define palavraH


#include <string.h>
#include "tipos.h"
#include "listas.h"

class Palavra{
 public:
		Palavra *ant,*prx;
		char *cstr;
  Palavra(){cstr=0;}
	Palavra::Palavra(char *conteudo);
		~Palavra(){if(cstr)delete []cstr;}
		void apagaezera();
		int comoint();
		void append(Palavra &pal);
		void append(const char *c);
		void append(int i);
		void append(double d);
		char *c_str(){return cstr;}
		int length(){return strlen(cstr);};
		NDOUBLE comodouble();
		Palavra& operator +(Palavra &p2);
		Palavra& operator +(char *c);
		Palavra& operator +(char c);
		Palavra& operator +(int n);
		Palavra& operator =(const char *c); 
  Palavra& operator =(int n);
		Palavra& operator =(Palavra &p);
  int operator ==(char *c);
		
};

class LstPalavras:public Lista<Palavra>{
public:
	void novo(char *string){
		novoptr();
	 *ult=string;
	}

	static void copia(LstPalavras *dest,LstPalavras *org){
  Palavra *wrd;
		dest->limpa();
		for(wrd=org->prm;wrd;wrd=wrd->prx){
			dest->novo(wrd->cstr);
		}
	}

	void addchar(Palavra *dest,char c){
		*dest=*dest+c;
	}
};
#endif

