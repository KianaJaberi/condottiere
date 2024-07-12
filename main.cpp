#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std ;

class State {
    public :
        void setName ( string n ){
            name = n ;
        }

        string getName (){
            return name ;
        }

        void setVicinityState ( string s ){
            vicinityStates [ name ].push_back (s) ;
        }

        bool getVicinityState ( string s ){
            for ( int i = 0 ; i < vicinityStates [name].size () ; i ++ ){
                if ( s == vicinityStates [name][i]){
                    return true ;
                }
            }
            return false ;
        }

        void setStatus (){
            status = true ;
        }

        bool getStatus (){
            return status ;
        }

    private :
        string name ;
        unordered_map < string , vector <string> > vicinityStates ;
        bool status = false ;
};

class Player {
    public :

    private :
};

class Card {
    public :

    private :
};

class YellowCards : public Card {
    public :

    private :
};

class PurpleCards : public Card {
    public :

    private :
};

class Condottiere {
    public :

    private :
};

int main (){

    return 0 ;
}