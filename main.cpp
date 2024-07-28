#include <iostream>
#include <fstream>
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

        void deleteCards (){
            for ( int i = cards.size () ; i > 0 ; i -- ){
                cards.pop_back () ;
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
        virtual void setName ( string n ){
            name = n ;
        }

        virtual string getName (){
            return name ;
        }

    private :
        string name ;
};

class YellowCard : public Card {
    public :
        void setPoint ( int p ){
            point = p ;
        }

        int getPoint (){
            return point ;
        }

    private :
        int point ;
};

class PurpleCard : public Card {
    public :
        void setPriority ( int p ){
            priority = p ;
        }

        int getPriority (){
            return priority ;
        }

    private :
        int priority ;
};

class PurpleCardSuper : public PurpleCard {
    public :
        void setPoint ( int p ){
            point = p ;
        }

        int getPoint (){
            return point ;
        }

    private :
        int point ;
};

class Condottiere {
    public :
        void game (){
            setStates () ;
            setCards () ;
        }

        void setStates (){
            string name ;
            int number ;
            ifstream file ;

            file.open ( "states.txt" ) ;

            for ( int i = 0 ; i < 14 ; i ++ ){
                State temp ;

                file >> name ;
                temp.setName ( name ) ;

                file >> number ;

                for ( int j = 0 ; j < number ; j ++ ){
                    file >> name ;
                    temp.setVicinityState ( name ) ;
                }

                states.push_back ( temp ) ;
            }
            file.close () ;
        }

        void setCards (){
            string name ;
            int number , point , priority ;
            ifstream file ;

            file.open ( "cards.txt" ) ;

            for ( int i = 0 ; i < 7 ; i ++){

                file >> number ;
                file >> name ;
                file >> point ;

                for ( int j = 0 ; j < number ; j ++ ){

                    YellowCard temp ;
                    temp.setName ( name ) ;
                    temp.setPoint ( point ) ;

                    cards.push_back ( &temp ) ;
                }
            }

            for ( int i = 0 ; i < 6 ; i ++ ){

                file >> number ;
                file >> name ;
                file >> priority ;

                for ( int j = 0 ; j < number ; j ++ ){

                    PurpleCard temp ;
                    temp.setName ( name ) ;
                    temp.setPriority ( priority ) ;

                    cards.push_back ( &temp ) ;
                }
            }

            for ( int i = 0 ; i < 2 ; i ++ ){

                file >> number ;
                file >> name ;
                file >> point ;
                file >> priority ;

                for ( int j = 0 ; j < number ; j ++ ){

                    PurpleCardSuper temp ;
                    temp.setName ( name ) ;
                    temp.setPoint ( point ) ;
                    temp.setPriority ( priority ) ;

                    cards.push_back ( &temp ) ;
                }
            }
            file.close () ;
        }

    private :
        vector < State > states ;
        vector < Card* > cards ;
};

int main (){

    return 0 ;
}