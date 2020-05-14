///////////////////////////////////////////////////////////////////////////////
//                   
// Name:             Olanrewaju Ayedun
// Email:            lanreayedunjr@gmail.com
// Label:            PO1
// Title:            Game of War
// Course:           CMPS 2143
// Semester:         Spring 2020
//
// Description:
//          Implementation file for playingcard
//
// Usage:
//        To build and define the cards used for this game of peace
//
// Files:           main.cpp
//                  Cards.hpp
//                  poker_game.hpp
//                  termio.h
/////////////////////////////////////////////////////////////////////////////////
#include "termio.h"
#include <algorithm> // std::random_shuffle
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
 * Struct ForeColor
 * 
 * Description:
 *      struct that holds data about foreground card color
 * 
 * Public Methods:
 *      ForeColor()-contstructor
 * 
 * 
 * Usage: 
 *     -For card color
 *      
 */
struct ForeColor{
    string base;
    string black;
    string red;
    string yellow;
    string green;
    string blue;
    string cyan;
    string magenta;
    string white;
 /**
     * Public : ForeColor()
     * 
     * Description:
     *      constructor to initializes all colors
     * 
     * Params:
     *      - none
     * 
     * Returns:
     *      - nothing
     */
    ForeColor(){
        base = "&00";
        black = "&10";
        red = "&20";
        yellow = "&30";
        green = "&40";
        blue = "&50";
        cyan = "&60";
        magenta = "&70";
        white = "&80";
    }
};
/**
 * Struct BackColor
 * 
 * Description:
 *      struct to hold card bckgrnd color
 * 
 * Public Methods:
 *      BackColor()-contstructor
 * 
 * 
 * Usage: 
 *     -For card color
 *      
 */
struct BackColor{
    string base;
    string black;
    string red;
    string yellow;
    string green;
    string blue;
    string cyan;
    string magenta;
    string white;
/**
     * Public : BackColor()
     * 
     * Description:
     *      constructor to initialize all colors
     * 
     * Params:
     *      - none
     * 
     * Returns:
     *      - nada
     */
    BackColor(){
        base = "&10";
        black = "&11";
        red = "&12";
        yellow = "&13";
        green = "&14";
        blue = "&15";
        cyan = "&16";
        magenta = "&17";
        white = "&18";
    }
};
/**
 * class Card
 * 
 * Description:
 *      Class for all cards used in the game. Yup, you guessed it.
 * Private
 *  string rank
    string suit
    int suitNum;  
    int rank;        
    int number;      
    int value;       
    string suitChar; 
    string rankChar;
    string color
 * Public Methods:
 *      
 *   Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string color);       // set foreground color of card
    void setBackgroundColor(string color);      // set background color of card
    void setColors(string fore,string back);      // set fore and back
    void setCharacterColor(string color);        // set symbol color 
    void setNumberColor(string color);          // set number color
    void setColors(string fore, string back, string symbol, string number);
    void baseColors();
 *      
 * 
 * Usage: 
 * 
 *     - The backbone of Cards used in the game and also the skeleton?
 *      
 */
class Card {
private:
    const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const string suit[4] = {"♠", "♦", "♣", "♥"};
    int suitNum;     // value 0-3 : num index of suit
    int rank;        // 0-13      : num value of rank
    int number;      // 1-52      : unique value determines card
    int value;       // 1-14      : numeric value to compare cards
    string suitChar; // "♠", "♦", "♣", "♥"
    string rankChar; // Ace, 1 ,2 ,3 ... Q, K
    string color;    // 


public:
    friend ostream;

    Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string color);       // set foreground color of card
    void setBackgroundColor(string color);      // set background color of card
    void setColors(string fore,string back);      // set fore and back
    void setCharacterColor(string color);        // set symbol color 
    void setNumberColor(string color);          // set number color
    void setColors(string fore, string back, string symbol, string number);
    void baseColors();

};


/**
     * Public : Card
     *
     * Description:
     *      Instance of a card in a deck. Its all coming together now.
     *
     * Params:
     *      int 0 - 51 to signify a card.
     *
     * Returns:
     *      Nothing
     */
Card::Card(int num) {
    number = num;
    suitNum = number / 13;
    suitChar = suit[suitNum];
    baseColors();
    rank = number % 13;
    rankChar = ranks[rank];
}


/**
     * Public : Repr
     *
     * Description:
     *      Returns a string representation of the card class with
     *      colors embedded.
     *
     * Params:
     *      None
     *
     * Returns:
     *      [string] - representation of card
     */
string Card::Repr() {
    string s = "";
    s += color + "┌──────────┐&00 \n";
    if(rank == 9){
      s += color + "│ " + suitChar + " " + rankChar + "&00      " + "|&00 \n";
    }else{
       s += color + "│ " + suitChar + " " + rankChar + "&00       " + "|&00 \n";
    }
    s += color + "|          |&00 \n";
    s += color + "|          |&00 \n";  
    if(rank == 9){
    s += color + "│    " + suitChar + " " + rankChar + "&00   " + "|&00 \n";
    }else{
      s += color + "│    " + suitChar + " " + rankChar + "&00    " + "|&00 \n";
    }
    s += color + "|          |&00 \n";
    s += color + "|          |&00 \n";  
    if(rank==9){
    s += color + "│       " + suitChar + " " + rankChar + "&00" + "|&00 \n";
    }else{
    s += color + "│       " + suitChar + " " + rankChar + "&00 " + "|&00 \n";
    }
    s += color + "└──────────┘&00 \n";
    /*if (rank != 9) {
        s += color + " ";
    }*/

    return s;
}
/**
 * Public : operator <<
 *
 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 *
 *      We don't need the scope resolution operator (Card::) since
 *      this is a "friend" of card.
 *
 * Params:
 *      [ostream&] : os
 *      [Card]     : obj
 *
 * Returns:
 *      [ostream&]
 */
ostream &operator<<(ostream &os, Card obj) {

    os << obj.Repr();

    return os;
}

/**
     * Public : operator ()
     *
     * Description:
     *      overloads the () operator to compares cards
     *
     * Params:
     *      const Card &rhs
     *          card to the rhs
     *
     * Returns:
     *      bool: compares two cards
     */
bool Card::operator()(const Card &rhs) {
    return (this->rank < rhs.rank);
}

/**
     * Public : operator >
     *
     * Description:
     *      overloads ? operator to compare cards 
     *
     * Params:
     *      const Card &rhs
     *          card to the right side
     *
     * Returns:
     *      bool: compares two cards
     */
bool Card::operator>(const Card &rhs) {
    return this->rank > rhs.rank;
}

/**
     * Public : operator <
     *
     * Description:
     *      overloads < operator to compares cards
     *
     * Params:
     *      const Card &rhs
     *          card to the right side
     *
     * Returns:
     *      bool: compares two cards
     */
bool Card::operator<(const Card &rhs) {
    return this->rank < rhs.rank;
}

/**
     * Public : operator !=
     *
     * Description:
     *      overloads the != operator to see if cards are not equal
     *
     * Params:
     *      const Card &rhs
     *          card to the rhs
     *
     * Returns:
     *      bool: if they are not equal
     */
bool Card::operator!=(const Card &rhs) {
    return this->rank != rhs.rank;
}

/**
     * Public : operator ==
     *
     * Description:
     *      overloads the == operator to see if cards are ==
     *
     * Params:
     *      const Card &rhs
     *          card to the rhs
     *
     * Returns:
     *      bool: if they are ==
     */
    
bool Card::operator==(const Card &rhs) {
    return this->rank == rhs.rank;
}

/**
     * Public : baseColors()
     *
     * Description:
     *      initializes base colors
     *
     * Params:
     *      none
     *
     * Returns:
     *      void : nada
     */
void Card::baseColors(){
    if(suitNum == 0 || suitNum == 2){
        setColors("green", "white", "green", "green");
    }else if(suitNum == 1 || suitNum == 3){
        setColors("red", "white", "red", "red");
    }
}
/**
     * Public : setColors(string main, string back, string symbol, string number)
     *
     * Description:
     *      sets every color using individual color functions
     *
     * Params:
     *          - string main
     *              foreground card color
     *          - string back
     *              background card color
     *          - string symbol
     *              suit symbol color
     *          - string number
     *              number color
     *      
     *
     * Returns:
     *      void
     */
void Card::setColors(string main, string back, string symbol, string number){
    setForegroundColor(main);       // set foreground card color
    setBackgroundColor(back);   
    setCharacterColor(symbol);        // set symbol color 
    setNumberColor(number);  
}

/**
     * Public : setNumberColor(string color)
     *
     * Description:
     *      sets number color
     *
     * Params:
     *
     *          - string color
     *              key for color
     *
     * Returns:
     *      void
     */
void Card::setNumberColor(string color){
    if(color == "base"){
        rankChar = ForeColor().base;
    }
    if(color == "black"){
        rankChar = ForeColor().black;
    }
    if(color == "red"){
        rankChar = ForeColor().red;
    }
    if(color == "yellow"){
        rankChar = ForeColor().yellow;
    }
    if(color == "green"){
        rankChar = ForeColor().green;
    }
    if(color == "blue"){
        rankChar = ForeColor().blue;
    }
    if(color == "cyan"){
        rankChar = ForeColor().cyan;
    }
    if(color == "magenta"){
        rankChar = ForeColor().magenta;
    }
    if(color == "white"){
        rankChar = ForeColor().white;
    }
}

/**
     * Public : setCharacterColor(string color)
     *
     * Description:
     *      sets Character color
     *
     * Params:
     *
     *          - string color
     *              key for color
     *
     * Returns:
     *      void
     */
void Card::setCharacterColor(string color){
    if(color == "base"){
        suitChar = ForeColor().base;
    }
    if(color == "black"){
        suitChar = ForeColor().black;
    }
    if(color == "red"){
        suitChar = ForeColor().red;
    }
    if(color == "yellow"){
        suitChar = ForeColor().yellow;
    }
    if(color == "green"){
        suitChar = ForeColor().green;
    }
    if(color == "blue"){
        suitChar = ForeColor().blue;
    }
    if(color == "cyan"){
        suitChar = ForeColor().cyan;
    }
    if(color == "magenta"){
        suitChar = ForeColor().magenta;
    }
    if(color == "white"){
        suitChar = ForeColor().white;
    }
}
/**
     * Public : setColors(string fore, string back)
     *
     * Description:
     *      sets fore and background colors
     *
     * Params:
     *
     *          - string fore
     *              foreground card color
     *          - string back
     *              background card color
     *
     * Returns:
     *      void
     */
void Card::setColors(string fore,string back){
    setBackgroundColor(back);
    setForegroundColor(fore);

}
/**
     * Public : setBackgroundColor(string color)
     *
     * Description:
     *      sets Background color
     *
     * Params:
     *
     *          - string color
     *               key for color
     *
     * Returns:
     *      void
     */
void Card::setBackgroundColor(string color){ 
    if(color == "base"){
        color = BackColor().base;
    }
    if(color == "black"){
        color = BackColor().black;
    }
    if(color == "red"){
        color = BackColor().red;
    }
    if(color == "yellow"){
        color = BackColor().yellow;
    }
    if(color == "green"){
        color = BackColor().green;
    }
    if(color == "blue"){
        color = BackColor().blue;
    }
    if(color == "cyan"){
        color = BackColor().cyan;
    }
    if(color == "magenta"){
        color = BackColor().magenta;
    }
    if(color == "white"){
        color = BackColor().white;
    }
}
/**
     * Public : setForegroundColor(string color)
     *
     * Description:
     *      sets Foreground color
     *
     * Params:
     *
     *          - string color
     *              key for color
     *
     * Returns:
     *      void 
     */
void Card::setForegroundColor(string color){
    if(color == "base"){
        color = ForeColor().base;
    }
    if(color == "black"){
        color = ForeColor().black;
    }
    if(color == "red"){
        color = ForeColor().red;
    }
    if(color == "yellow"){
        color = ForeColor().yellow;
    }
    if(color == "green"){
        color = ForeColor().green;
    }
    if(color == "blue"){
        color = ForeColor().blue;
    }
    if(color == "cyan"){
        color = ForeColor().cyan;
    }
    if(color == "magenta"){
        color = ForeColor().magenta;
    }
    if(color == "white"){
        color = ForeColor().white;
    }
}