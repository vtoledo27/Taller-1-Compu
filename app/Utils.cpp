#include "Utils.h"
#include <iostream>
#include <math.h>


using namespace std;


std::string Utils::acomodar(std::string texto) {
    /*
     * Pasamos el texto a minusculas (en caso de que se use una variable en mayúscula)
     */
    std::transform(texto.begin(), texto.end(), texto.begin(), [](unsigned char c) {
        return std::tolower(c); });

    /*
     * Truco para tokenizar negativos.
     *
     * Reemplazar el menos por un más y un menos.
     */
    std::string polinomio = std::regex_replace(texto, std::regex("-"), "+-");

    /*
     * Se eliminan los espacios al polinomio
     */
    std::string::iterator it = std::remove(polinomio.begin(), polinomio.end(), ' ');
    polinomio.erase(it, polinomio.end());

    return polinomio;
}

vector<std::string> Utils::obtener_terminos(std::string polinomioStr) {
    std::vector<std::string> elementos;
    if (!polinomioStr.empty()) {

        char* str = new char[polinomioStr.size() + 1];
        strncpy(str, polinomioStr.c_str(), polinomioStr.size());

        char* token = strtok(str, "+");
        while (token != NULL) {
            std::string elemento = token;
            elementos.push_back(elemento);
            token = strtok(NULL, "+");
        }
        delete[] str;
    }
    return elementos;
}

Monomio Utils::str2Monomio(std::string texto) {
    Monomio mono;

    if (!texto.empty()) {
        std::string str = texto;
        std::size_t pos = str.find("x");

        //        std::cout << "Texto: " << texto << " Pos: " << pos << std::endl;
        if (pos != std::string::npos) {
            /// Coeficiente
            std::string coefStr = str.substr(0, pos);
            if (coefStr.empty()) {
                mono.SetCoeficiente(1);
            } else {
                mono.SetCoeficiente(atof(coefStr.c_str()));
            }

            /// Grado
            unsigned int resto = pos + 3;
            if (str.size() >= resto) {
                std::string gradoStr = str.substr(resto, str.size() - 1);
                mono.SetGrado(atof(gradoStr.c_str()));
            } else if (str.size() > pos) {
                mono.SetGrado(1);
            } else {
                mono.SetGrado(0);
            }
        } else {
            mono.SetCoeficiente(atof(str.c_str()));
            mono.SetGrado(0);
        }
    }

    return mono;
}

vector<Monomio> Utils::convertir(std::string polinomioStr) {
    vector<Monomio> listado;
    if (!polinomioStr.empty()) {
        std::string resultado = acomodar(polinomioStr);
        vector<std::string> terminos = obtener_terminos(resultado);

        vector<int>::size_type i = 0;
        vector<Monomio> polinomio;

        for (i = 0; i < terminos.size(); i++) {
            std::string valor = terminos[i];
            Monomio monomio = str2Monomio(valor);
            polinomio.push_back(monomio);
        }

        listado = polinomio;


    }
    return listado;
}

double Utils::evaluar(vector<Monomio> polinomio, double valor) {
    double resultado;
    vector<Monomio>::size_type i;
    double suma = (double) 0;
    for (i = 0; i < polinomio.size(); i++) {
        Monomio monomio = polinomio[i];
        suma += (monomio.GetCoeficiente() * pow(valor, monomio.GetGrado()));
    }
    resultado = suma;
    return resultado;
}

vector<Monomio> Utils::derivar(vector<Monomio> polinomio)
{
       vector<Monomio> deriv;
       cout<<endl;
       cout<<"-Derivada: ";
       vector<Monomio>::size_type i;
       for(i=0; i < polinomio.size(); i++){
           Monomio monomio = polinomio[i];
           Monomio derivMon;    //Creamos un objeto de la clase Monomio para guardar la derivada del monomio

          /*Realizamos el calculo de la derivada del monomio
           * -Para el nuevo  coeficiente: Multiplicar el exponente (o grado) del monomio por su coeficiente
           * -Para el nuevo exponente (o grado): Restarle 1 al exponente actual
           */
          derivMon.SetCoeficiente(monomio.GetGrado() * monomio.GetCoeficiente());
          derivMon.SetGrado(monomio.GetGrado()-1);
          deriv.push_back(derivMon);  //agregamos la derivada calculada al vector "deriv"

          cout<<derivMon.GetCoeficiente() << "x**" << derivMon.GetGrado()<<" ";

    }
    cout<<endl;
    return deriv;
}


double Utils::newthonRaphson(std::vector<Monomio> polinomio)
{
    vector<Monomio> poliDeriv = derivar(polinomio); //llamamos a la funcion "derivar" y asignamos el valor que retorna a la variable "poliDeriv"
    double pivote = 1;
    double xn = pivote;
    double error = 0.00001;
    double resulPoli = evaluar(polinomio, xn);
    double resulDeriv = evaluar(poliDeriv, xn);

    double division = resulPoli/resulDeriv;

    //fabs()-> funcion que calcula el valor absoluto de un numero
    while(fabs(division) >=error){
    //Mientras el valor absoluto de la division sea mayor o igual al error
        resulPoli = evaluar(polinomio, xn);
        resulDeriv = evaluar (poliDeriv, xn);
        division = resulPoli/resulDeriv;
        xn = xn - division;
    }
    return xn;
}











