#include <iostream>
#include <vector>
#include <string>
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
        void setName ( string n ){
            name = n ;
        }

        string getName (){
            return name ;
        }

        void setColor ( string c ){
            color = c ;
        }

        string getColor (){
            return color ;
        }

        void setStates ( State s ){
            states.push_back (s) ;
        }

        int numberOfStates (){
            return states.size () ;
        }

        bool checkStates (){
            if ( states.size () == 5 ){
                return true ;
            }
            else {
                int counter = 0 ;

                for ( int i = 0 ; i < states.size () ; i ++ ){
                    for ( int j = 0 ; j < states.size () ; j ++ ){
                        if ( states [i].getVicinityState ( states [j].getName () ) == true ){
                            counter ++ ;
                        }
                    }

                    if ( counter == 2 ){
                        return true ;
                    }
                    else {
                        counter = 0 ;
                    }
                }
                return false ;
            }
        }

        void setCards ( vector < Card >& temp ){
            for ( int i = 0 ; i < temp.size () ; i ++ ){
                cards.push_back ( temp [i] ) ;
            }
        }

        void getCards ( vector < Card >& temp ){
            for ( int i = 0 ; i < cards.size () ; i ++ ){
                temp [i] = cards [i] ;
            }
        }

        bool checkCards (){
            if ( cards.size () == 0 ){
                return true ;
            }
            else {
                return false ;
            }
        }

        void deleteCard ( Card c ){
            for ( int i = 0 ; i < cards.size () ; i ++ ){
                if ( cards [i].getName () == c.getName () ){
                    auto it = cards.begin () + i ;
                    cards.erase ( it ) ;
                    break ;
                }
            }
        }

    private :
        string name ;
        string color ;
        vector < State > states ;
        vector < Card > cards ;
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