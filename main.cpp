#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <algorithm>
#include <random>

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

        void getStates ( vector < State >& temp ){
            for ( int i = 0 ; i < states.size () ; i ++ ){
                temp.push_back ( states [i] ) ;
            }
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

        void setCard ( Card temp ){
            cards.push_back ( temp ) ;
        }

        void getCards ( vector < Card >& temp ){
            for ( int i = 0 ; i < cards.size () ; i ++ ){
                temp.push_back ( cards [i] ) ;
            }
        }

        int getSizeOfCards (){
            return cards.size () ;
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

class Condottiere {
    public :
        void game (){
            setStates () ;
            setCards () ;
            setInformation () ;

            while ( checkWinner () == false ){
                
                shuffleCards () ;
                peaceAndWarBadges () ;
                luckyAndUnluckyNumbers () ;

                while ( checkPlayersHands () == false ){

                    for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                        if ( ( warBadgeHolder + i ) < numberOfPlayers ){
                            display ( warBadgeHolder + i ) ;
                        }
                        else {
                            display ( ( warBadgeHolder + i ) - numberOfPlayers ) ;
                        }
                    }
                }
            }
        }

        void setStates (){
            string name ;
            int number ;
            ifstream file ;

            file.open ( "states.txt" ) ;

            for ( int i = 0 ; i < 15 ; i ++ ){
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

                    cards.push_back ( temp ) ;
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

                    cards.push_back ( temp ) ;
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

                    cards.push_back ( temp ) ;
                }
            }

            file.close () ;
        }

        void setInformation (){
            HANDLE color ;
	        color = GetStdHandle ( STD_OUTPUT_HANDLE ) ;

            while ( true ){
            
                cout << "Enter the number of players ( must be between 3 and 6 ) : " ;
                cin >> numberOfPlayers ;
                cout << "\n" ;

                if ( numberOfPlayers >= 3 && numberOfPlayers <= 6 ){
                    system ( "cls" ) ;
                    break ;
                }
                else {
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ; 
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }
            }

            cardsPlayed.resize ( numberOfPlayers ) ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                pass.push_back (0) ;
            }

            int age ;
            int tempAge ;
            string name ;
            string selectedColor ;
            Player tempPlayer ;
            vector < string > colors = { "purple" , "yellow" , "blue" , "green" , "red" , "orange" } ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){

                cout << "Enter the name of player (" << i+1 << ") : " ;
                cin >> name ;
                cout << "\n" ;
                tempPlayer.setName ( name ) ;

                while ( true ){

                    cout << "Enter the age of player (" << i+1 << ") : " ;
                    cin >> age ;
                    cout << "\n" ;

                    if ( age <= 0 ){
                        SetConsoleTextAttribute ( color , 4 ) ;
                        cout << "Error!\n" ;
                        SetConsoleTextAttribute ( color , 7 ) ;

                        continue ;
                    }
                    else {
                        break ;
                    }
                }

                if ( i == 0 ){
                    tempAge = age ;
                    warBadgeHolder = 0 ;
                }

                if ( tempAge > age ){
                    tempAge = age ;
                    warBadgeHolder = i ;
                }

                while ( true ){
                    
                    cout << "Enter the color of player (" << i+1 << ")( " ;

                    for ( int j = 0 ; j < colors.size () ; j ++ ){

                        if ( colors [j] == "purple" ){
                            SetConsoleTextAttribute ( color , 13 ) ;
                            cout << "purple " ;
                        }
                        else if ( colors [j] == "yellow" ){
                            SetConsoleTextAttribute ( color , 14 ) ;
                            cout << "yellow " ;
                        }
                        else if ( colors [j] == "blue" ){
                            SetConsoleTextAttribute ( color , 11 ) ;
                            cout << "blue " ;
                        }
                        else if ( colors [j] == "green" ){
                            SetConsoleTextAttribute ( color , 10 ) ;
                            cout << "green " ;
                        }
                        else if ( colors [j] == "red" ){
                            SetConsoleTextAttribute ( color , 12 ) ;
                            cout << "red " ;
                        }
                        else if ( colors [j] == "orange" ){
                            SetConsoleTextAttribute ( color , 6 ) ;
                            cout << "orange " ;
                        }

                        SetConsoleTextAttribute ( color , 7 ) ;
                    }
                    cout << ") : " ;
                    cin >> selectedColor ;
                    cout << "\n" ;

                    if (   selectedColor != "purple" && selectedColor != "yellow" && selectedColor != "blue" 
                        && selectedColor != "green"  && selectedColor != "red"    && selectedColor != "orange" ){
                        
                        SetConsoleTextAttribute ( color , 4 ) ;
                        cout << "Error!\n" ;
                        SetConsoleTextAttribute ( color , 7 ) ;

                        continue ;
                    }
                    else {
                        break ;
                    }
                }
                tempPlayer.setColor ( selectedColor ) ;
                
                for ( int j = 0 ; j < colors.size () ; j ++ ){
                    if ( colors [j] == selectedColor ){
                        colors.erase ( colors.begin () + j ) ;
                        break ;
                    }
                }

                players.push_back ( tempPlayer ) ;
                system ( "cls" ) ;
            }
        }

        void shuffleCards (){
            random_device rd;
            mt19937 g ( rd () ) ;

            shuffle ( cards.begin () , cards.end () , g ) ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                for ( int j = 0 ; j < 10 ; j ++ ){
                    players [i].setCard ( cards [j] ) ;
                }
                for ( int k = 0 ; k < players [i].numberOfStates () ; k ++ ){
                    players [i].setCard ( cards [ 10 + k ] ) ;
                }

                for ( int s = 0 ; s < ( 10 + players [i].numberOfStates () ) ; s ++ ){
                    cards.erase ( cards.begin () ) ;
                }
            }
        }

        bool checkWinner (){
            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                if ( players [i].checkStates () == true ){
                    return true ;
                }
            }
            return false ;
        }

        bool checkPlayersHands (){
            int counter = 0 ;
            int temp = -1 ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                if ( players [i].checkCards () == false ){
                    counter ++ ;
                    temp = i ;
                }
            }

            if ( counter == 0 ){
                return true ;
            }
            else if ( counter == 1 ){
                players [ temp ].getCards ( cards ) ;
                players [ temp ].deleteCards () ;

                return true ;
            }
            else if ( counter > 1 ){
                return false ;
            }
        }

        void peaceAndWarBadges (){
            HANDLE color ;
	        color = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
            bool flag = false ;

            if ( peaceBadgeHolder != -1 ){
                while ( true ){

                    cout << players [ peaceBadgeHolder ].getName () << " choose a state for peace badge ( " ;

                    for ( int i = 0 ; i < states.size () ; i ++ ){
                        if ( i == 0 ){
                            cout << states [i].getName () ;
                        }
                        else if ( i == ( states.size () - 1 ) ){
                            cout << " / " << states [i].getName () << " ) : " ;
                        }
                        else {
                            cout << " / " << states [i].getName () ;
                        }
                    }
                    cin >> peaceBadge ;
                    cout << "\n" ;

                    for ( int i = 0 ; i < states.size () ; i ++ ){
                        if ( states [i].getName () == peaceBadge ){
                            flag = true ;
                            break ;
                        }
                    }

                    if ( flag == false ){
                        SetConsoleTextAttribute ( color , 4 ) ;
                        cout << "Error!\n" ;
                        SetConsoleTextAttribute ( color , 7 ) ;

                        continue ;
                    }
                    else {
                        flag = false ;
                        break ;
                    }
                }
            }

            while ( true ){

                cout << players [ warBadgeHolder ].getName () << " choose a state for war badge ( " ;

                for ( int i = 0 ; i < states.size () ; i ++ ){
                    if ( i == 0 ){
                        cout << states [i].getName () ;
                    }
                    else if ( i == ( states.size () - 1 ) ){
                        cout << " / " << states [i].getName () << " ) : " ;
                    }
                    else {
                        cout << " / " << states [i].getName () ;
                    }
                }
                cin >> warBadge ;
                cout << "\n" ;

                for ( int i = 0 ; i < states.size () ; i ++ ){
                    if ( states [i].getName () == warBadge ){
                        flag = true ;
                        break ;
                    }
                }

                if ( flag == false ){
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }
                else {
                    break ;
                }
            }
        }

        void luckyAndUnluckyNumbers (){
            HANDLE color ;
	        color = GetStdHandle ( STD_OUTPUT_HANDLE ) ;

            while ( true ){
                cout << players [ warBadgeHolder ].getName () << " enter lucky number ( must be between 10 and 99 ) : " ;
                cin >> luckyNumber ;
                cout << "\n" ;

                if ( luckyNumber < 10 || luckyNumber > 99 ){
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }
                else {
                    break ;
                }
            }

            while ( true ){
                cout << players [ warBadgeHolder ].getName () << " enter unlucky number ( must be between 10 and 99 ) : " ;
                cin >> unluckyNumber ;
                cout << "\n" ;

                if ( unluckyNumber < 10 || unluckyNumber > 99 ){
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }
                else {
                    break ;
                }
            }
        }

        void display ( int p ){
            HANDLE color ;
	        color = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
            string input ;

            while ( true ){
                cout << players [p].getName () << " are you ready ? ( yes or no ) : " ;
                cin >> input ;
                cout << "\n" ;

                if ( input != "yes" && input != "no" ){
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }

                if ( input == "no" ){
                    continue ;
                }

                system ( "cls" ) ;

                for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                    cout << players [i].getName () << " : " ;

                    for ( int j = 0 ; j < cardsPlayed [i].size () ; j ++ ){
                        cout << cardsPlayed [i][j].getName () << " / " ;
                    }

                    cout << "\n" ;
                }

                cout << "________________________________________\n" ;

                 for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                    cout << players [i].getName () << " : " ;

                    vector < State > temp ;
                    players [i].getStates ( temp ) ;

                    for ( int j = 0 ; j < players [i].numberOfStates () ; j ++ ){
                        cout << temp [j].getName () << " / " ;
                    }

                    cout << "\n" ;
                }

                cout << "________________________________________\n" ;

                cout << warBadge << "\n" ;

                vector < Card > temp ;
                players [p].getCards ( temp ) ;

                for ( int i = 0 ; i < temp.size () ; i ++ ){
                    cout << temp [i].getName () << " / " ;
                }

                cout << "\n" ;

                while ( true ){
                    cin >> input ;
                    cout << "\n" ;

                    if ( input == "pass" ){
                        pass [p] = 1 ;
                        break ;
                    }
                    else {
                        bool flag = false ;
                        
                        for ( int i = 0 ; i < temp.size () ; i ++ ){
                            if ( temp [i].getName () == input ){
                                flag = true ;
                                setChoice ( p , temp [i] ) ;
                            }
                        }

                        if ( flag == true ){
                            break ;
                        }
                        else {
                            SetConsoleTextAttribute ( color , 4 ) ;
                            cout << "Error!\n" ;
                            SetConsoleTextAttribute ( color , 7 ) ;

                            continue ;
                        }
                    }
                }
                system ( "cls" ) ;
                break ;
            }
        }

        void setChoice ( int p , Card c ){
            players [p].deleteCard (c) ;
            cardsPlayed [p].push_back (c) ;
        }

    private :
        int numberOfPlayers ;
        int warBadgeHolder = -1 ;
        int peaceBadgeHolder = -1 ;
        int luckyNumber ;
        int unluckyNumber ;
        string warBadge ;
        string peaceBadge ;
        vector < State > states ;
        vector < Card > cards ;
        vector < Player > players ;
        vector < vector < Card > > cardsPlayed ;
        vector < int > pass ;
};

int main (){

    Condottiere c ;
    c.game () ;

    return 0 ;
}