#include "Utils.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;	
	
/**
* Función que muestra los participantes del grupo
* @param programa nombre del ejecutable
*/
void participantes();
	
/**
* Taller computacional
* @param argc cantidad de argumentos
* @param argv argumentos
* @return El código de salida del programa
*/
int main(int argc, char** argv) {
	
    int codSalida;
	if (argc == 2) {
		const string polinomio(argv[1]);
		vector<Monomio> monomios = Utils::convertir(polinomio);

		//Se muestra el polinomio Ingresado por el usuario
	    cout<<"-Polinomio: ";
		vector<Monomio>::size_type i = 0;
		//Mientras el tamaño del monomio sea mayor a "i"
		for(i=0; i< monomios.size(); i++){
			Monomio mono = monomios[i];
			cout<<mono.GetCoeficiente()<<"x**"<<mono.GetGrado()<<" ";
		}
		double resultado = Utils::newthonRaphson(monomios);

		cout<<"-Solucion(aproximada): "<<resultado<<endl;
		codSalida = EXIT_SUCCESS;
	    } else {//En caso de que el usuario ingrese erroneamente o en el formato incorrecto los argumentos se muestra el siguiente mensaje
			cout<<"Error: argumentos no validos, deben ingresarse en el formato: "<<endl;
			cout<<argv[0] << "''->_Polinomio_<-''" <<endl;
			cout<<endl;
			cout<<"Porfavor intentelo nuevamente"<<endl;
			codSalida = EXIT_FAILURE;


	    }
	    //Funcion que muestra en pantalla a los integrantes del grupo
	    participantes();
	 return codSalida;
	}




	/*Funcion que muestra a los integrantes del grupo*/
void participantes() {
   cout<<endl<< "-|=== Taller N°1 ===|-" <<endl;
   cout<<endl << "-Kevin Labra Soto";
   cout<<endl << "-Victor Toledo Cerna";
   cout<<endl << "-Virla Parra Retamal" <<endl;
   cout<<endl;
   cout<<endl;

	}

	
	
