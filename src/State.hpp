#pragma once

#include <vector>
#include <string>
#include <memory>

class State{

    public :

        enum class Type{
           Start, Level1, Level2, Level3, Exit, Cutscene1, Cutscene2
        };

    public :

        static std :: shared_ptr<State> instance(){
            static std :: shared_ptr<State> inst{ new State };
	        return inst;
        }

        void pop(){ states.pop_back(); }

        void push(Type s){ states.push_back(s); }

        Type back(){ return states.back(); }

        State(State const&) = delete;

        void operator = (State const&) = delete;

        ~State(){ }

    private :

        std :: vector<Type> states;

        State(){ states.push_back(Type :: Start); }
};