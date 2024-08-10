#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std ;

class State {
    public :
        void setName ( string n ){
            name = n ;
        }

        string getName (){
            return name ;
        }

        void setVicinity ( string s ){
            vicinity.push_back (s) ;
        }

        bool checkVicinity ( string s ){
            for ( int i = 0 ; i < vicinity.size () ; i ++ ){
                if ( vicinity [i] == s ){
                    return true ;
                }
            }
            return false ;
        }

    private :
        string name ;
        vector < string > vicinity ;
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
        virtual void setPriority ( int p ){
            priority = p ;
        }

        virtual int getPriority (){
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

        void setState ( State s ){
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
                        if ( states [i].checkVicinity ( states [j].getName () ) == true ){
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

        void deleteCard ( Card c ){
            for ( int i = 0 ; i < cards.size () ; i ++ ){
                if ( cards [i].getName () == c.getName () ){
                    cards.erase ( cards.begin () + i ) ;
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
        void newGame (){
            setStates () ;
            setCards () ;
            setInformation () ;

            game () ;
        }

        void continueGame ( int g ){

            ifstream file ;

            switch ( g ){
                case 1 : file.open ( "savedGame1.txt" ) ;
                    break;
                case 2 : file.open ( "savedGame2.txt" ) ;
                    break;
                case 3 : file.open ( "savedGame3.txt" ) ;
                    break;
                case 4 : file.open ( "savedGame4.txt" ) ;
                    break;
                case 5 : file.open ( "savedGame5.txt" ) ;
                    break;
            }

            setStates () ;
            setCards () ;

            file >> numberOfPlayers  ;
            file >> warBadgeHolder   ;
            file >> peaceBadgeHolder ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                string name ;
                string color ;
                Player temp ;

                file >> name ;
                file >> color ;

                temp.setName ( name ) ;
                temp.setColor ( color ) ;

                players.push_back ( temp ) ;
            }

            int numberOfStates ;
            vector < State > tempState ;

            file >> numberOfStates   ;

            for ( int i = 0 ; i < numberOfStates ; i ++ ){
                string stateName ;
                file >> stateName ;

                for ( int j = 0 ; j < 15 ; j ++ ){
                    if ( states [j].getName () == stateName ){
                        tempState.push_back ( states [j] ) ;
                        break ;
                    }
                }
            }

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                int number ;
                file >> number ;

                for ( int j = 0 ; j < number ; j ++ ){
                    string stateName ;
                    file >> stateName ;

                    for ( int j = 0 ; j < 15 ; j ++ ){
                        if ( states [j].getName () == stateName ){
                            players [i].setState ( states [j] ) ;
                            break ;
                        }
                    }
                }
            }

            for ( int i = 15 ; i > 0 ; i -- ){
                states.pop_back () ;
            }
            for ( int i = 0 ; i < numberOfStates ; i ++ ){
                states.push_back ( tempState [i] ) ;
            }

            file.close () ;

            game () ;
        }

        void game (){
            while ( checkTheEndOfTheGame () == false ){
                
                shuffleCards () ;
                peaceAndWarBadges () ;
                luckyAndUnluckyNumbers () ;

                while ( checkTheEndOfTheWar () == false ){
                    bool flag = false ;

                    for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                        int temp ;

                        if ( ( warBadgeHolder + i ) < numberOfPlayers ){
                            temp = ( warBadgeHolder + i ) ;

                            if ( players [ temp ].getSizeOfCards () > 0 && pass [ temp ] == 0 ){
                                display ( temp ) ;
                                
                                if ( cardsPlayed [ temp ][ cardsPlayed [ temp ].size () - 1 ].getName () == "parchamDar" ){
                                    flag = true ;
                                }
                            }
                        }
                        else {
                            temp = ( ( warBadgeHolder + i ) - numberOfPlayers ) ;

                            if ( players [ temp ].getSizeOfCards () > 0 && pass [ temp ] == 0 ){
                                display ( temp ) ;
                                
                                if ( cardsPlayed [ temp ][ cardsPlayed [ temp ].size () - 1 ].getName () == "parchamDar" ){
                                    flag = true ;
                                }
                            }
                        }

                        if ( flag == true ){
                            break ;
                        }
                    }
                    if ( flag == true ){
                        break ;
                    }
                }
                vector < double > points ;

                for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                    points.push_back ( scoreCalculation (i) ) ;
                    
                    if ( fmod ( points [i] , unluckyNumber ) ==  0){
                        points [i] = 0 ;
                    }
                    if ( fmod ( points [i] , luckyNumber ) ==  0){
                        points [i] *= 2 ;
                    }
                }

                if ( findWarBadgeHolderWithShirZan () == true ){
                    int temp = findStateWinner ( points ) ;
                }
                else {
                    int temp = findStateWinner ( points ) ;

                    if ( temp > -1 ){
                        warBadgeHolder = temp ;
                    }
                }
                clearGame () ;
            }
            int temp = findWinner () ;

            if ( temp == -1 ){
                cout << "we do not have winner !\n" ;
            }
            else if ( temp >= 0 ){
                cout << players [ temp ].getName () << " win !\n" ;
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
                    temp.setVicinity ( name ) ;
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

                    if ( selectedColor == "purple" || selectedColor == "yellow" || selectedColor == "blue" ||
                         selectedColor == "green"  || selectedColor == "red"    || selectedColor == "orange" ){
                        tempPlayer.setColor ( selectedColor ) ;
                        break ;
                    }
                    else {    
                        SetConsoleTextAttribute ( color , 4 ) ;
                        cout << "Error!\n" ;
                        SetConsoleTextAttribute ( color , 7 ) ;

                        continue ;
                    }
                }
                
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

        bool checkTheEndOfTheGame (){
            if ( states.size () == 0 ){
                return true ;
            }
            else {
                for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                    if ( players [i].checkStates () == true ){
                        return true ;
                    }
                }
                return false ;
            }
        }

        void shuffleCards (){
            random_device rd;
            mt19937 g ( rd () ) ;

            shuffle ( cards.begin () , cards.end () , g ) ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                for ( int j = 0 ; j < 10 ; j ++ ){
                    players [i].setCard ( cards [0] ) ;
                    cards.erase ( cards.begin () ) ;
                }
                for ( int k = 0 ; k < players [i].numberOfStates () ; k ++ ){
                    players [i].setCard ( cards [0] ) ;
                    cards.erase ( cards.begin () ) ;
                }
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
                        cout << states [i].getName () << " | " ;
                    }
                    cout << ") : " ;
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
                    if ( states [i].getName () != peaceBadge ){
                        cout << states [i].getName () << " | " ;
                    }
                }
                cout << ") : " ;
                cin >> warBadge ;
                cout << "\n" ;

                if ( warBadge == peaceBadge ){
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }

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
            system ( "cls" ) ;
        }

        void luckyAndUnluckyNumbers (){
            HANDLE color ;
	        color = GetStdHandle ( STD_OUTPUT_HANDLE ) ;

            while ( true ){
                cout << players [ warBadgeHolder ].getName () << " enter lucky number ( must be between 10 and 99 ) : " ;
                cin >> luckyNumber ;
                cout << "\n" ;

                if ( luckyNumber >= 10 && luckyNumber <= 99 ){
                    break ;
                }
                else {
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }
            }

            while ( true ){
                cout << players [ warBadgeHolder ].getName () << " enter unlucky number ( must be between 10 and 99 ) : " ;
                cin >> unluckyNumber ;
                cout << "\n" ;

                if ( unluckyNumber >= 10 && unluckyNumber <= 99 ){
                    break ;
                }
                else {
                    SetConsoleTextAttribute ( color , 4 ) ;
                    cout << "Error!\n" ;
                    SetConsoleTextAttribute ( color , 7 ) ;

                    continue ;
                }
            }
            system ( "cls" ) ;
        }

        bool checkTheEndOfTheWar (){
            int counter = 0 ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                if ( pass [i] == 1 ){
                    counter ++ ;
                }
            }

            if ( counter == numberOfPlayers ){
                return true ;
            }
            else {
                counter = 0 ;

                for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                    if ( players [i].getSizeOfCards () == 0 ){
                        counter ++ ;
                    }
                }

                if ( counter == numberOfPlayers ){
                    return true ;
                }
                else {
                    return false ;
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
                else {
                    break ;
                }
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

            for ( int i = 0 ; i < players [p].getSizeOfCards () ; i ++ ){
                cout << temp [i].getName () << " / " ;
            }

            cout << "\n" ;

            while ( true ){
                cout << players [p].getName () << " : " ;
                cin >> input ;
                cout << "\n" ;

                if ( input == "save" ){
                    int inputI ;

                    while ( true ){
                        cout << "1 , 2 , 3 , 4 or 5 ? \n" ;
                        cin >> inputI ;
                        cout << "\n" ;

                        if ( inputI < 1 || inputI > 5 ){
                            cout << "Error !\n" ;

                            continue ;
                        }
                        else {
                            saveGame ( inputI ) ;
                            break ;
                        }
                    }
                    break ;
                }
                else if ( input == "help" ){
                    help () ;
                    continue ;
                }
                else if ( input == "pass" ){
                    pass [p] = 1 ;
                    break ;
                }
                else {
                    bool flag = false ;
                    
                    for ( int i = 0 ; i < players [p].getSizeOfCards () ; i ++ ){
                        if ( temp [i].getName () == input ){
                            flag = true ;
                            players [p].deleteCard ( temp [i] ) ;
                            cardsPlayed [p].push_back ( temp [i] ) ;

                            if ( input == "rishSefid" ){
                                peaceBadgeHolder = p ;
                                setRishSefid () ;
                            }
                            else if ( input == "matarsak" ){
                                setMatarsak (p) ;
                            }
                            else if ( input == "bahar" || input == "zemestan" ){
                                status = input ;
                            }

                            break ;
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
        }

        void setRishSefid (){
            string cardName = findTheMostValuableCards () ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                for ( int j = 0 ; j < cardsPlayed [i].size () ; j ++ ){

                    if ( cardsPlayed[i][j].getName () == cardName ){
                        cards.push_back ( cardsPlayed[i][j] ) ;
                        cardsPlayed[i].erase ( cardsPlayed[i].begin () + j ) ;
                    }
                }
            }
        }

        string findTheMostValuableCards (){
            int theMostValuableCard = 0 ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                for ( int j = 0 ; j < cardsPlayed [i].size () ; j ++ ){

                    if ( cardsPlayed [i][j].getName () == "s10" ){
                        theMostValuableCard = 10 ;
                    }
                    else if ( cardsPlayed [i][j].getName () == "s6" ){
                        if ( theMostValuableCard < 6 ){
                            theMostValuableCard = 6 ;
                        }
                    }
                    else if ( cardsPlayed [i][j].getName () == "s5" ){
                        if ( theMostValuableCard < 5 ){
                            theMostValuableCard = 5 ;
                        }
                    }
                    else if ( cardsPlayed [i][j].getName () == "s4" ){
                        if ( theMostValuableCard < 4 ){
                            theMostValuableCard = 4 ;
                        }
                    }
                    else if ( cardsPlayed [i][j].getName () == "s3" ){
                        if ( theMostValuableCard < 3 ){
                            theMostValuableCard = 3 ;
                        }
                    }
                    else if ( cardsPlayed [i][j].getName () == "s2" ){
                        if ( theMostValuableCard < 2 ){
                            theMostValuableCard = 2 ;
                        }
                    }
                    else if ( cardsPlayed [i][j].getName () == "s1" ){
                        if ( theMostValuableCard < 1 ){
                            theMostValuableCard = 1 ;
                        }
                    }
                }
            }

            if ( theMostValuableCard == 10 ){
                return "s10" ;
            }
            else if ( theMostValuableCard == 6 ){
                return "s6" ;
            }
            else if ( theMostValuableCard == 5 ){
                return "s5" ;
            }
            else if ( theMostValuableCard == 4 ){
                return "s4" ;
            }
            else if ( theMostValuableCard == 3 ){
                return "s3" ;
            }
            else if ( theMostValuableCard == 2 ){
                return "s2" ;
            }
            else if ( theMostValuableCard == 1 ){
                return "s1" ;
            }
        }

        void setMatarsak ( int p ){
            HANDLE color ;
	        color = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
            string input ;
            bool flag = false ;

            cout << players [p].getName () << " you can get a yellow card\n" ;

            for ( int i = 0 ; i < cardsPlayed [p].size () ; i ++ ){
                if (cardsPlayed[p][i].getName() == "s1" || cardsPlayed[p][i].getName() == "s2" || cardsPlayed[p][i].getName() == "s3" ||
                    cardsPlayed[p][i].getName() == "s4" || cardsPlayed[p][i].getName() == "s5" || cardsPlayed[p][i].getName() == "s6" ||
                    cardsPlayed[p][i].getName() == "s10" ){

                    cout << cardsPlayed [p][i].getName () << " / " ;
                    flag = true ;
                }
            }

            if ( flag == false ){
                SetConsoleTextAttribute ( color , 4 ) ;
                cout << "you do not have yellow card !\n" ;
                SetConsoleTextAttribute ( color , 7 ) ;
            }
            else {
                flag = false ;

                while ( true ){
                    
                    cin >> input ;
                    cout << "\n" ;

                    if (input == "s1"||input == "s2"||input == "s3"||input == "s4"||input == "s5"||input == "s6"||input == "s10" ){
                        
                        for ( int i = 0 ; i < cardsPlayed [p].size () ; i ++ ){

                            if ( cardsPlayed [p][i].getName () == input ){
                                players [p].setCard ( cardsPlayed [p][i] ) ;
                                cardsPlayed [p].erase ( cardsPlayed [p].begin () + i ) ;

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
                    else {
                        SetConsoleTextAttribute ( color , 4 ) ;
                        cout << "Error!\n" ; 
                        SetConsoleTextAttribute ( color , 7 ) ;

                        continue ;
                    }
                }
            }
        }

        double scoreCalculation ( int p ){
            double score = 0 ;
            int numberOfTablZan = 0 ;

            if ( status == "bahar" ){

                string theMostValuableCard = findTheMostValuableCards () ;

                for ( int i = 0 ; i < cardsPlayed [p].size () ; i ++ ){
                    
                    if ( cardsPlayed [p][i].getName () == theMostValuableCard ){
                        score += 3 ;
                        break ;
                    }
                }

                status = "sull" ;
            }

            if ( status == "zemestan" ){

                for ( int i = 0 ; i < cardsPlayed [p].size () ; i ++ ){

                    if ( cardsPlayed [p][i].getName () == "s2" || cardsPlayed [p][i].getName () == "s3" ){
                        score += 1 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s4" || cardsPlayed [p][i].getName () == "s5" ){
                        score += 2 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s6" ){
                        score += 3 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s10" ){
                        score += 5 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "shirDokht" ){
                        score += 10 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "tablZan" ){
                        numberOfTablZan ++ ;
                    }
                }

                score *= pow ( 1.5 , numberOfTablZan ) ;
                return score ;
            }

            if ( status == "sull" ){

                for ( int i = 0 ; i < cardsPlayed [p].size () ; i ++ ){

                    if ( cardsPlayed [p][i].getName () == "s1" ){
                        score += 1 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s2" ){
                        score += 2 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s3" ){
                        score += 3 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s4" ){
                        score += 4 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s5" ){
                        score += 5 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s6" ){
                        score += 6 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "s10" ){
                        score += 10 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "shirZan" ){
                        score += 1 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "shirDokht" ){
                        score += 10 ;
                    }
                    else if ( cardsPlayed [p][i].getName () == "tablZan" ){
                        numberOfTablZan ++ ;
                    }
                }

                score *= pow ( 1.5 , numberOfTablZan ) ;
                return score ;
            }
        }

        bool findWarBadgeHolderWithShirZan (){

            vector < vector < int > > numberOfShirZans ( numberOfPlayers , vector < int > (2) ) ;
            
            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){

                numberOfShirZans [i][0] = i ;
                numberOfShirZans [i][1] = 0 ;

                for ( int j = 0 ; j < cardsPlayed [i].size () ; j ++ ){

                    if ( cardsPlayed [i][j].getName () == "shirZan" ){
                        numberOfShirZans [i][1] ++ ;
                    }
                }
            }

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                for ( int j = ( i + 1 ) ; j < numberOfPlayers ; j ++ ){

                    if ( numberOfShirZans [i][1] < numberOfShirZans [j][1] ){
                        int temp ;

                        temp = numberOfShirZans [i][0] ;
                        numberOfShirZans [i][0] = numberOfShirZans [j][0] ;
                        numberOfShirZans [j][0] = temp ;

                        temp = numberOfShirZans [i][1] ;
                        numberOfShirZans [i][1] = numberOfShirZans [j][1] ;
                        numberOfShirZans [j][1] = temp ;
                    }


                }
            }

            if ( numberOfShirZans [0][1] == 0 ){
                return false ;
            }
            else if ( numberOfShirZans [0][1] == numberOfShirZans [1][1] ){
                return false ;
            }
            else {
                warBadgeHolder = numberOfShirZans [0][0] ;
                return true ;
            }
        }

        int findStateWinner ( vector < double > points ){
            int stateWinner = 0 ;
            double theHighestScore = points [0] ;

            for ( int i = 1 ; i < numberOfPlayers ; i ++ ){

                if ( theHighestScore < points [i] ){
                    theHighestScore = points [i] ;
                    stateWinner = i ;
                }
            }

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                if ( theHighestScore == points [i] ){
                    if ( stateWinner != i ){
                        stateWinner = -1 ;
                    }
                }
            }

            if ( stateWinner > -1 ){
                
                for ( int i = 0 ; i < states.size () ; i ++ ){
                    if ( states [i].getName () == warBadge ){
                        players [ stateWinner ].setState ( states [i] ) ;
                        states.erase ( states.begin () + i ) ;
                        break ;
                    }
                }
            }
            return stateWinner ;
        }

        int findWinner (){
            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                if ( players [i].checkStates () == true ){
                    return i ;
                }
            }
            return -1 ;
        }

        void clearGame (){
            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                pass [i] = 0 ;
            }

            for ( int i = ( numberOfPlayers - 1 ) ; i > 0 ; i -- ){
                for ( int j = ( cardsPlayed.size () - 1 ) ; j > 0 ; j -- ){

                    cards.push_back ( cardsPlayed [i][j] ) ;
                    cardsPlayed [i].pop_back () ;
                }
            }

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                vector < Card > temp ;

                players [i].getCards ( temp ) ;

                for ( int j = 0 ; j < players [i].getSizeOfCards () ; j ++ ){
                    cards.push_back ( temp [j] ) ;
                }

                players [i].deleteCards () ;
            }
        }

        void saveGame ( int g ){
            ofstream file ;

            switch ( g ){
                case 1 : file.open ( "savedGame1.txt" ) ;
                    break;
                case 2 : file.open ( "savedGame2.txt" ) ;
                    break;
                case 3 : file.open ( "savedGame3.txt" ) ;
                    break;
                case 4 : file.open ( "savedGame4.txt" ) ;
                    break;
                case 5 : file.open ( "savedGame5.txt" ) ;
                    break;
            }

            file << numberOfPlayers  << "\n" ;
            file << warBadgeHolder   << "\n" ;
            file << peaceBadgeHolder << "\n" ;

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                file << players [i].getName  () << "\n" ;
                file << players [i].getColor () << "\n" ;
            }

            file << states.size () << "\n" ;

            for ( int i = 0 ; i < states.size () ; i ++ ){
                file << states [i].getName () << "\n" ;
            }

            for ( int i = 0 ; i < numberOfPlayers ; i ++ ){
                file << players [i].numberOfStates () << "\n" ;

                vector < State > temp ;
                players[i].getStates ( temp ) ;

                for ( int j = 0 ; j < players [i].numberOfStates () ; j ++ ){
                    file << temp [j].getName () << "\n" ;
                }
            }

            file.close () ;
            exit (0) ;
        }

        void help (){
            ifstream file ;

            file.open ( "help.txt" ) ;

            string line ;

            while ( getline ( file , line ) ){
                cout << line << "\n" ;
            }

            file.close () ;
            
        }

    private :
        int numberOfPlayers = 0 ;
        int luckyNumber = 0 ;
        int unluckyNumber = 0 ;
        int warBadgeHolder = -1 ;
        int peaceBadgeHolder = -1 ;
        string warBadge ;
        string peaceBadge ;
        string status = "sull" ;
        vector < State > states ;
        vector < Card > cards ;
        vector < vector < Card > > cardsPlayed ;
        vector < Player > players ;
        vector < int > pass ;
};

int main (){

    Condottiere c ;
    string inputS ;
    int inputI ;

    cout << "hello :)\n" ;
    cout << "1.new game ( new )\n2.saved game ( saved )\n" ;

    while ( true ){
        cin >> inputS ;
        cout << "\n" ;

        if ( inputS != "new" && inputS != "saved" ){
            cout << "Error !\n" ;

            continue ;
        }
        else {
            break ;
        }
    }

    if ( inputS == "new" ){
        system ( "cls" ) ;
        c.newGame () ;
    }
    else if ( inputS == "saved" ){

        while ( true ){

            cout << "1 , 2 , 3 , 4 or 5 ? \n" ;
            cin >> inputI ;
            cout << "\n" ;

            if ( inputI < 1 || inputI > 5 ){
                cout << "Error !\n" ;

                continue ;
            }
            else {
                break ;
            }
        }
        system ( "cls" ) ;
        c.continueGame ( inputI ) ;
    }

    return 0 ;
}