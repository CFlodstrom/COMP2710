// Chris Flodstrom
// Project2_czf0038.cpp
// This project simulates a duel with the a strategy of shooting the
// most accurate opponent still alive. This program uses random numbers
// with probablities given.
//
// Compile with the standard g++
//
// David Morris assisted me with implementing a while loop
// and also assisted me with debugging my program: strategy 2 was printing
// the same results as strategy 1, which was a simple variable naming mistake that I couldnt find.
// I also used Piazza to assist me with the assert() on shooting functions

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

/*
 * Input: A_alive indicates Aaron is alive true for alive, false for dead
 * B_alive indicates Bob is alive
 * C_alive indicates Charlie is alive
 * Return: true if at least two are alive otherwise return false
 */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);

/*
 * call by reference
 * Strategy 1: Everyone shoots to kill the highest accuracy player alive
 * Input: B_alive indicates Bob is alive or dead
 *        C_alive indicates Aaron is alive or dead
 
 * Return: Change B_alive into false if Bob is killed
 *          Change C_alive into false if Charlie is killed
 */
void Aaron_shoots1(bool& B_alive, bool& C_alive);

/*
 * call by reference
 * Input A_ alive indicates Aaron is alive or dead
 * C_alive indicates Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed
 *         Change C_alive into false if Charlie is killed
 */
void Bob_shoots(bool& A_alive, bool& C_alive);

/*
 * Call by reference
 * Input: A_alive indicates Aaron is alive or dead
 *       B_alive indicates Bob is alive or dead
 * Return: Change A_alive into false if Aaron is killed
 *         Change B_alive into false if Bob is killed
 */
void Charlie_shoots(bool& A_alive, bool& B_alive);

/*
 * Call by reference
 * Strategy 2: Aaron intentionally misses if both are alive
 * Input B_alive indicates Bob is alive or dead
 *       C_alive indicates Aaron is alive or dead
 * Return: Change B_alive into false if Bob is killed
 *         Change C_alive into false if Charlie is killed
 */
void Aaron_shoots2(bool& B_alive, bool& C_alive);

//Simple method to implement pause function in linux
void Press_any_key(void);

//Test Prototypes
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

// Variables
const double Acc_A = 1.0/3.0;
const double Acc_B = 0.5;
const double Acc_C = 1.0;
const double Tot_Run =  10000;

int main() {
    
    //Initializes Random number generator's seed and calls test functions
    int aWins1 = 0;
    int aWins2 = 0;
    int bWins = 0;
    int cWins = 0;
    bool a_Living;
    bool b_Living;
    bool c_Living;
    
    cout<<"*** Welcome to Chris's Duel Simulator ***\n";
    srand(time(0));
    test_at_least_two_alive();
    Press_any_key();
    test_Aaron_shoots1();
    Press_any_key();
    test_Bob_shoots();
    Press_any_key();
    test_Charlie_shoots();
    Press_any_key();
    test_Aaron_shoots2();
    Press_any_key();
    
    //Starts strategy 1 and runs 10,000 times
    cout<< "Ready to test strategy 1 (run 10000 times):\n";
    Press_any_key();
    for(int i = 0; i < Tot_Run; i++) {
        a_Living = true;
        b_Living = true;
        c_Living = true;
            while (at_least_two_alive(a_Living, b_Living, c_Living)) {
                if(a_Living) {
                    Aaron_shoots1(b_Living, c_Living);
                }
                if(b_Living) {
                    Bob_shoots(a_Living, c_Living);
                }
                if(c_Living) {
                    Charlie_shoots(a_Living, b_Living);
                }
            }
        if(a_Living == true) {
            aWins1++;
        }
        if(b_Living == true) {
            bWins++;
        }
        if(c_Living == true) {
            cWins++;
        }
    }

cout << "Aaron won " <<aWins1 <<"/10000 duels or " <<static_cast<double>(aWins1)/ Tot_Run * 100 <<"%\n"
<<"Bob won " <<bWins<<"/10000 duels or " <<static_cast<double>(bWins)/ Tot_Run * 100 <<"%\n"
<<"Charlie won " <<cWins<<"/10000 duels or " <<static_cast<double>(cWins) / Tot_Run * 100 <<"%\n"
<<endl;
    
    bWins = 0;
    cWins = 0;
    cout<< "Ready to test strategy 2 (run 10000 times): \n";
    Press_any_key();
    for(int i = 0; i < Tot_Run; i++) {
        a_Living = true;
        b_Living = true;
        c_Living = true;
        while(at_least_two_alive(a_Living, b_Living, c_Living)) {
            if(a_Living) {
                Aaron_shoots2(b_Living, c_Living);
            }
            if(b_Living) {
                Bob_shoots(a_Living, c_Living);
            }
            if(c_Living) {
                Charlie_shoots(a_Living, b_Living);
            }
        }
        if(a_Living == true) {
            aWins2++;
        }
        if(b_Living == true) {
            bWins++;
        }
        if(c_Living == true) {
            cWins++;
        }
    }
    
cout << "Aaron won " <<aWins2 <<"/10000 duels or " <<static_cast<double>(aWins2)/ Tot_Run * 100 <<"%\n"
    <<"Bob won " <<bWins<<"/10000 duels or " <<static_cast<double>(bWins)/ Tot_Run * 100 <<"%\n"
    <<"Charlie won " <<cWins<<"/10000 duels or " <<static_cast<double>(cWins) / Tot_Run * 100 <<"%\n"
    <<endl;
    
if(aWins2 >= aWins1) {
    cout<<"Strategy 2 is better than strategy 1.\n:";
}
else {
    cout<<"Strategy 1 is better than strategy 2.\n";
}
return 0;
}

//Implementation of functions. Look above for documentation them.
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    if(A_alive && B_alive) {
        return true;
    }
    if(A_alive && C_alive) {
        return true;
    }
    if(B_alive && C_alive) {
        return true;
    }
    return false;
}

void test_at_least_two_alive(void) {
    cout<<"Unit Testing 1: Function - at_least_two_alive()\n";
    cout<<"\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true,true,true));
    cout<<"\tCase passed ...\n";
    cout<<"\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout<<("\tCase passed...\n");
    cout<<"\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true,false,true));
    cout<<"\tCase passed ...\n";
    cout<<"\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true,true,false));
    cout<<"\tCase passed ...\n";
    cout<<"\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false,false,true));
    cout<<"\tCase passed ...\n";
    cout<<"\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false,true,false));
    cout<<"\tCase passed ...\n";
    cout<<"\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true,false,false));
    cout<<"\tCase passed ...\n";
    cout<<"\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false,false,false));
    cout<<"\tCase passed ...\n";
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    int target = rand
    () % 3;
    if(target == 1) {
        if(C_alive == true) {
            C_alive = false;
        }
        else {
            B_alive = false;
        }
    }
}

void test_Aaron_shoots1(void) {
    cout<<"Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    bool bob_a, charlie_a = true;
    cout<<"\tCase 1: Bob alive, Charlie alive\n";
    cout<<"\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);
    bob_a = false;
    charlie_a = true;
    cout<<"\tCase 2: Bob dead, Charlie alive\n"
    <<"\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);
    bob_a = true;
    charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
    << "\t\t Aaron is shooting at Bob\n";
    Aaron_shoots1(bob_a, charlie_a);
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
    int target = rand() % 2;
    if(target == 1) {
        if(C_alive == true) {
            C_alive = false;
        }
        else {
            A_alive = false;
        }
    }
}

void test_Bob_shoots(void) {
    bool a_Living, c_Living = true;
    cout<< "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    cout<< "\tCase 1: Aaron alive, Charlie alive\n";
    cout<< "\t\tBob is shooting at Charlie\n";
    Bob_shoots(a_Living, c_Living);
    cout<<"\tCase 2: Aaron dead, Charlie alive\n";
    cout<<"\t\tBob is shooting at Charlie\n";
    c_Living = false;
    Bob_shoots(a_Living, c_Living);
    cout<<"\tCase 3: Aaron alive, Charlie dead\n";
    cout<<"\t\tBob is shooting at Aaron\n";
    c_Living = true;
    a_Living = false;
    Bob_shoots(a_Living, c_Living);
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
    int target = rand() % 1;
    if(target <= Acc_C && B_alive == true) {
        B_alive = false;
    }
    else {
        A_alive = false;
    }
}

void test_Charlie_shoots(void) {
    bool a_Living, b_Living = true;
    cout<<"Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    cout<<"\tCase 1: Aaron alive, Bob alive\n";
    cout<<"\t\tCharlie is shooting at Bob\n";
    Bob_shoots(a_Living, b_Living);
    cout<<"\tCase 2: Aaron dead, Bob alive\n";
    cout<<"\t\tCharlie is shooting at Bob\n";
    cout<<"\tCase 3: Aaron alive, Bob dead\n";
    cout<<"\t\tCharlie is shooting at Aaron\n";
    a_Living = false;
    Bob_shoots(a_Living, b_Living);
}
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    int target = rand() % 3;
    if(B_alive && C_alive) return;
    if(target == 1) {
            if(C_alive == true) {
                C_alive = false;
            }
            else {
                B_alive = false;
            }
        }
    }

void test_Aaron_shoots2(void) {
    bool b_Living, c_Living = true;
    cout<<"Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    cout<<"\tCase 1: Bob alive, Charlie alive\n";
    cout<<"\t\tAaron intentionally misses his first shot\n";
    cout<<"\t\tBoth Bob and Charlie are alive.\n";
    Aaron_shoots2(b_Living, c_Living);
    cout<<"\tCase 2: Bob dead, Charlie alive\n";
    cout<<"\t\tAaron is shooting at Charlie\n";
    c_Living = false;
    Aaron_shoots2(b_Living, c_Living);
    cout<<"\tCase 3: Bob alive, Charlie dead\n";
    cout<<"\t\tAaron is shooting at Bob\n";
    c_Living = true;
    b_Living = false;
    Aaron_shoots2(b_Living, c_Living);
}

void Press_any_key(void) {
    cout<<"Press any key to continue...";
    cin.ignore().get();
}

