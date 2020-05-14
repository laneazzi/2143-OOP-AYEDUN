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
//          This the main program to use all the files.
//
// Usage:
//        To run and instruct the program
//
// Files:           main.cpp
//                  Cards.hpp
//                  poker_game.hpp
//                  termio.h
/////////////////////////////////////////////////////////////////////////////////

#include "poker_game.hpp"
#include <iomanip>

int main(){

    Term::IO io;
    Game a;
    Deck B(52);
    Hand player1(26);
    Hand player2(26);
    bool cont = true;
    for(int i=0;i<50;i++){
        B.Shuffle();
        break;
        io << Term::sleep(1000); 
    }

   B.Split(player1, player2);
   player1.Shuffle();
   
 
   player2.Shuffle();

while(cont){
  io << "Cards: " << player1.Size() << "     Cards: " << player2.Size() <<"\n";
   CardContainer i(player1.Play(), player2.Play());
    
   i.Print(2, false);
    io<<"Player 1        Player 2\n";

    a.Distribute(a.Compare(i.Get(0), i.Get(1)), player1, player2, i);
     
    if(player1.Size() == 0 || player2.Size() == 0){
     cont = a.End(player1.Size(), player2.Size());
    }
 io << Term::sleep(1000); 
}
    return 0;
}