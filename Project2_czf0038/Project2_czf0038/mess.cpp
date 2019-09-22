// Chris Flodstrom
// mess.cpp
//
//

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
const double ACCURACY_AARON = 1.0/3.0;
const double ACCURACY_BOB = 0.5;
const double ACCURACY_CHARLIE = 1.0;
const double TOTAL_RUNS =  10000;



int main() {
    
    //Initializes Random number generator's seed and calls test functions
    bool aaron_Alive;
    bool bob_Alive;
    bool charlie_Alive;
    int aaronWins1 = 0;
    int aaronWins2 = 0;
    int bobWins = 0;
    int charlieWins = 0;
    
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
    
    cout<< "Ready to test strategy 1 (run 10000):\n";
    Press_any_key();
    
    for(int i = 0; i < TOTAL_RUNS; i++) {
        aaron_Alive = true;
        bob_Alive = true;
        charlie_Alive = true;
        while (at_least_two_alive(aaron_Alive, bob_Alive, charlie_Alive)) {
            if(aaron_Alive) {
                Aaron_shoots1(bob_Alive, charlie_Alive);
            }
            if(bob_Alive) {
                Bob_shoots(aaron_Alive, charlie_Alive);
            }
            if(charlie_Alive) {
                Charlie_shoots(aaron_Alive, bob_Alive);
            }
        }
        if(aaron_Alive == true) {
            aaronWins1 ++;
        }
        if(bob_Alive == true) {
            bobWins++;
        }
        if(charlie_Alive == true) {
            charlieWins++;
        }
    }
    
    
    cout << "Aaron won " <<aaronWins1 <<"/100000 duels or " <<static_cast<double>(aaronWins1)/ TOTAL_RUNS * 100 <<"%\n"
    <<"Bob won " <<bobWins<<"/10000 duels or " <<static_cast<double>(bobWins)/ TOTAL_RUNS * 100 <<"%\n"
    <<"Charlie won" <<charlieWins<<"/100000 duels or " <<static_cast<double>(charlieWins) / TOTAL_RUNS * 100 <<"%\n"
    <<endl;
    
    bobWins = 0;
    charlieWins = 0;
    cout<< "Ready to test strategy 2 (run 10000 times): \n";
    
    Press_any_key();
    for(int i = 0; i < TOTAL_RUNS; i++) {
        aaron_Alive = true;
        bob_Alive = true;
        charlie_Alive = true;
        
        while(at_least_two_alive(aaron_Alive, bob_Alive, charlie_Alive)) {
            if(aaron_Alive) {
                Aaron_shoots2(bob_Alive, charlie_Alive);
            }
            if(bob_Alive) {
                Bob_shoots(aaron_Alive, charlie_Alive);
            }
            if(charlie_Alive) {
                Charlie_shoots(aaron_Alive, bob_Alive);
            }
        }
        if(aaron_Alive == true) {
            aaronWins2++;
        }
        if(bob_Alive == true) {
            bobWins++;
        }
        if(charlie_Alive == true) {
            charlieWins++;
        }
    }
    
    cout << "Aaron won " <<aaronWins1 <<"/100000 duels or " <<static_cast<double>(aaronWins1)/ TOTAL_RUNS * 100 <<"%\n"
    <<"Bob won " <<bobWins<<"/10000 duels or " <<static_cast<double>(bobWins)/ TOTAL_RUNS * 100 <<"%\n"
    <<"Charlie won" <<charlieWins<<"/100000 duels or " <<static_cast<double>(charlieWins) / TOTAL_RUNS * 100 <<"%\n"
    <<endl;
    
    if(aaronWins2 >= aaronWins1) {
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
    
    cout<<"\tCase1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true,true,true));
    cout<<"\tCase passed ...\n";
    
    cout<<"\tCase2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout<<("\tCase passed...\n");
    
    cout<<"\tCase3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true,false,true));
    cout<<"\tCase passed ...\n";
    
    cout<<"\tCase4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true,true,false));
    cout<<"\tCase passed ...\n";
    
    cout<<"\tCase5: Aaron dead, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(false,false,true));
    cout<<"\tCase passed ...\n";
    
    cout<<"\tCase6: Aaron dead, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(false,true,false));
    cout<<"\tCase passed ...\n";
    
    cout<<"\tCase7: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true,false,false));
    cout<<"\tCase passed ...\n";
    
    cout<<"\tCase8: Aaron dead, Bob dead, Charlie dead\n";
    assert(true == at_least_two_alive(false,false,false));
    cout<<"\tCase passed ...\n";
}

void Aaron_shoots(bool& B_alive, bool& C_alive) {
    int target = rand() % 3;
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
    bool aaron_a, bob_a, charlie_a = true;
    cout<<"\tCase1: Bob alive, Charlie alive\n";
    cout<<"\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);
    
    bob_a = false;
    charlie_a = true;
    cout<<"\tCase2: Bob dead, Charlie alive\n"
    <<"\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_a, charlie_a);
    
    bob_a = true;
    charlie_a = false;
    cout << "\tCase3: Bob alive, charlie dead\n"
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
    bool Aaron_alive, Bob_alive, Charlie_alive = true;
    cout<< "Unit testing 3: function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    cout<< "\tCase1: Aaron alive, Charlie alive\n";
    cout<< "\t\tBob is shooting at Charlie\n";
    Bob_shoots(Aaron_alive, Charlie_alive);
    
    cout<<"\tCase2: Aaron alive, Charlie dead\n";
    cout<<"\t\tBob is shooting at Charlie\n";
    Charlie_alive = false;
    Bob_shoots(Aaron_alive, Charlie_alive);
    
    cout<<"\tCase 3: Aaron dead, Charlie alive\n";
    cout<<"\t\tBob is shooting at Aaron\n";
    Charlie_alive = true;
    Aaron_alive = false;
    Bob_shoots(Aaron_alive, Charlie_alive);
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
    int target = rand() % 1;
    
    if(target <= ACCURACY_CHARLIE && B_alive == true) {
        B_alive = false;
    }
    else {
        A_alive = false;
    }
}

void test_Charlie_shoots(void) {
    bool Aaron_alive, Bob_alive, Charlie_alive = true;
    
    cout<<"Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    cout<<"\tCase1: Aaron alive, Bob alive\n";
    cout<<"\t\tCharlie is shooting at Bob\n";
    Bob_shoots(Aaron_alive, Bob_alive);
    
    cout<<"\tCase1: Aaron alive, Bob alive\n";
    cout<<"\t\tCharlie is shooting at Bob\n";
    Aaron_alive = false;
    Bob_shoots(Aaron_alive, Bob_alive);
}
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    int target = rand() % 3;
    
    if(target == 1) {
        if(!(B_alive && C_alive)) {
            if(C_alive == true) {
                C_alive = false;
            }
            else {
                B_alive = false;
            }
        }
    }
}

void test_Aaron_shoots2(void) {
    bool Aaron_alive, Bob_alive, Charlie_alive = true;
    
    cout<<"Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    cout<<"\tCase 2: Bob alive, Charlie alive\n";
    cout<<"\t\tAaron intentionally misses his first shot\n";
    cout<<"\t\tBoth Bob and Charlie are alive.\n";
    Aaron_shoots2(Bob_alive, Charlie_alive);
    cout<<"\tCase 2: Bob dead, Charlie alive\n";
    cout<<"\t\tAaron is shooting at Charlie\n";
    Charlie_alive = false;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    cout<<"\tCase 3: Bob alive, Charlie dead\n";
    cout<<"\t\tAround is shooting at Charlie\n";
    Charlie_alive = true;
    Bob_alive = false;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    
}
void Press_any_key(void) {
    cout<<"Press any key to continue...";
    cin.ignore().get();
}

