#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "State.h"
using namespace std;

class Automaton{
    public:
        Automaton(State _s);
        bool tokenAnalyzer(string word);
    public:
        // Estado inicial
        State S;
};

// Constructor default
Automaton::Automaton(State _s){
    S = _s;
};

// tokenAnalyzer imprime los tokens y su tipo, ifs acomodan los tokens en lineas correctamente.
bool Automaton::tokenAnalyzer(string word){
bool result = false;
  if(word.length()==0){
    return false;
  }

  // Estado actual 
  State prevState = S;
  string newsymbol;

  for(int i=0; i<word.length(); i++){  
      string symbol = word.substr(i,1);

      // Estado nuevo al que se llegara con la transicion.
    
      State nextState = prevState.getNextState(symbol);

      // Ignora espacios aunque sean parte del DFA.

      if(nextState.name == "Inicial"){
        continue;
      }

      // Ifs post procesan distintos casos de prueba.

      if(nextState.name == "Parentesis que abre" || nextState.name == "Parentesis que cierra" || nextState.name ==                 "Asignacion" || nextState.name == "Suma" || nextState.name == "Multiplicacion" || nextState.name == "Division" ){

        if(nextState.isDeathState){cout << "Syntax Error, continuing" << endl; break;};
        cout << newsymbol << "             "<< prevState.name << endl;
        newsymbol = symbol;
        prevState = nextState;
        if(word.length()-1 == i){
        cout << newsymbol << "             "<< prevState.name << endl;
        }
        continue;
      }
      if(nextState.name == "Entero" & prevState.name == "Resta"){
        if(nextState.isDeathState){cout << "Syntax Error, continuing" << endl; break;};
        newsymbol += symbol;
        prevState = nextState;
        if(word.length()-1 == i){
        cout << newsymbol << "             "<< prevState.name << endl;
        }
        continue;
      }
      if(nextState.name == "Real" & prevState.name == "Entero"){
        if(nextState.isDeathState){cout << "Syntax Error, continuing" << endl; break;};
        newsymbol += symbol;
        prevState = nextState;
        if(word.length()-1 == i){
        cout << newsymbol << "             "<< prevState.name << endl;
        }
        continue;
      }
      if(nextState.name == prevState.name || prevState.name == "Inicial"){
        if(nextState.isDeathState){cout << "Syntax Error, continuing" << endl; break;};
        newsymbol += symbol;
        prevState = nextState;
        if(word.length()-1 == i){
        cout << newsymbol << "             "<< prevState.name << endl;
        }
        continue;
      }else{
        cout << newsymbol << "             "<< prevState.name << endl;
        newsymbol = symbol;
        prevState = nextState;
        if(word.length()-1 == i){
        cout << newsymbol << "             "<< prevState.name << endl;
      }
    }
  }
    return true;
}

#endif