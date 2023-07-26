#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
using namespace std;


class State{
    public:
        State();
        State(bool isFinal, bool isDeathState, string name);
        void addTransition(string symbol, State state);
        State getNextState(string symbol);
        string debug();
    public:
        bool isFinal;
        bool isDeathState;
        string name;
        map<string, State>* transitions = new map<string, State>();
};

  
State::State(){
    isFinal = false;
    isDeathState = false;
    name = " ";
}

State::State(bool _isFinal, bool _isDeathState, string _name){
    isFinal = _isFinal;
    isDeathState = _isDeathState;
    name = _name;
}

void State::addTransition(string symbol, State state){
    transitions->insert({symbol, state});
}
 
State State::getNextState(string symbol){
    return transitions->at(symbol);
}

string State::debug(){
    return "isFinal= " + std::to_string(isFinal) + ", IsDeath= " + std::to_string(isDeathState) + ", name= " + name + ", transitions= " + std::to_string(transitions->size());
}


#endif