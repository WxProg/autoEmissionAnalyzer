/* ================================================================
PROGRAM Simulate Craps

        AUTHOR: <Antwon Bryce>
        FSU MAIL NAME: <acb19d>
        RECITATION SECTION NUMBER: <03>
        RECITATION INSTRUCTOR NAME: <Samuel Ostlund>
        Course Information: <COP 3014>
        Project Number: <4>
        Due Date: <Wednesday 10, 2021>
        PLATFORM: Windows OS / CLion IDE

SUMMARY

This program will be used to simulate the dice rolling game known as Craps.
Within this program, the game is played by two players following a set of rules.

INPUT

There is no input for this program.

OUTPUT

Prints out each wager and player along with the bet that is placed
as well as the roll of the dice.

ASSUMPTIONS
- Assume that 20 wagers occur.
- Assume that each player starts out with a balance of $1000.
- Assume when player 1 is rolling, he always bets $100 on each wager.

 */
/* ================================================================ */

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

double DrawNum (int max);
void displayPlayerInfo(int player, double bet, double & totalBalance, int wager);
bool RollDice(int player, int count, const int MAX);
bool RollDiceMulti(int player,int point, const  int MAX);
int GetPlayerBet(int player, const double balance, const double initialBalance);
void AdjustWages(int activePlayer, double & p1Balance, double & p2Balance, double bet, bool winner);


int main()
{
    /* declare all constants */
    int playerTurn = 1;                                       /* determine the active player */
    const int player1 = 1, player2 = 2;                       /* declaring player 1 and player 2 */
    const  int MAX = 6;                                       /* Maximum number for each die*/
    double p1Balance = 1000, p2Balance = 1000;                /* Gives player1 and player 2 current balance */
    const double p1InitBalance = 1000 , p2InitBalance = 1000; /* Gives initial balance for each player. modified */
    bool winner = true;                                       /* set true if there's a winner */

    cout
            << "======================================================" << endl;
    cout
            << "       Welcome to the Craps Game! " << endl;
    cout
            << "======================================================" << endl;

    /* run all 20  wagers */
    for(int i = 1; i <= 20; i++){

        double & balance  = (playerTurn == 1) ? p1Balance : p2Balance;
        const double initBalance  = (playerTurn == 1) ? p1InitBalance : p2InitBalance;

        double playerBet = GetPlayerBet(playerTurn, balance, initBalance );

        displayPlayerInfo(playerTurn, playerBet, balance, i );

        winner = RollDice(playerTurn, i, MAX);

        AdjustWages(playerTurn, p1Balance, p2Balance, playerBet, winner);

        /* call roll dice; */
        if(!winner){
            /* changing a player */
            playerTurn = (playerTurn == player1)?player2 : player1;
        }
    }
    cout    << "======================================================" << endl;
    cout
            << "      Thanks for playing the Craps game!  " << endl;
    cout
            << "======================================================" << endl;
    return 0;
}
    /* displaying the current wager */
void displayPlayerInfo(int player, double bet, double & totalBalance, int wager){
    cout << "Wager " << wager << ": Bet is $"<< bet << endl;
    cout << "\tPlayer " << player << " is rolling the dice" << endl;
}
    /* roll dice for the player once */
bool RollDice(int player, int count, const int MAX){
    const int NATURAL7 = 7;
    const int NATURAL11 = 11;

    double point = DrawNum(MAX) + DrawNum(MAX);

    /* change the count  when a new player is chosen */
    if((point == NATURAL7) || (point == NATURAL11)){

        cout<<"\t The roll is "<< point << ". Player "<< player << " wins." <<endl;
        return true;

    }else if((point == 2) || (point == 12) || (point == 3)){
        cout<<"\t The roll is "<< point <<endl;
        cout << "\tThat is craps! Player "<< player << " loses.." <<endl;
        return false;
    } else{

        cout << "\tThe roll is a "<< point <<".  The point is "<< point <<". Player " << player <<" rolls again." <<endl;
        return RollDiceMulti(player, point, MAX);
    }

}
    /* roll dice for player multiple times */
bool RollDiceMulti(int player,int point, const  int MAX){
    int newRoll = 0;

    while(newRoll != point && newRoll != 7 ){

        newRoll = DrawNum(MAX) + DrawNum(MAX);
        cout << "\tThe roll is a "<< newRoll <<".  The point is "<< point <<". Player " << player <<" rolls again." <<endl;

    }

    return newRoll == point;

}
    /* adjust the player wages */
void AdjustWages(int activePlayer, double & p1Balance, double & p2Balance, double bet, bool winner){

    if(winner){
        double & balanceToIncrease = (activePlayer == 1)? p1Balance : p2Balance;
        double & balanceToDecrease = (activePlayer == 1)? p2Balance : p1Balance;

        balanceToIncrease+=bet;
        balanceToDecrease-=bet;

    }else{
        double & balanceToIncrease = (activePlayer == 1)? p2Balance : p1Balance;
        double & balanceToDecrease = (activePlayer == 1)? p1Balance : p2Balance;

        balanceToIncrease+=bet;
        balanceToDecrease-=bet;
    }

    cout << "\nCurrently, Player 1 has $" << p1Balance <<" and Player 2 has $" << p2Balance <<"." << endl;
    cout << "*****************************************************" << endl;
}


    /* gets players bet */
int GetPlayerBet(int player, const double balance, const double initialBalance){

    const double p1Bet = 100;
    const double p2HighBet = 150;
    const double p2LowBet = 50;

    if(player == 1){

        return p1Bet;

    }else{
        /* base on the initial bet p2 will choose either a low or high bet */
        if(balance > initialBalance){
            return p2HighBet;
        }else{
            return p2LowBet;
        }
    }

}
/****************************************************/
/*    function drawNum, taken from the lottery Game*/
/****************************************************/
double DrawNum (int max) {
    /* function drawNum */

    double x = RAND_MAX + 1.0;        /* x and y are both auxiliary */
    int y;                            /* variables used to do the */
    /* calculation */

    y = static_cast<int> (1 + rand() * (max / x));
    return (y);                       /* y contains the result */

}    /* function drawNum */


