/*
 * Chris Flodstrom	(czf0038)
 * project4_czf0038
 * 7 November 2019
 * Compile using g++
 *
 * Description: allows players to create their trivia questions and answers. Multiple questions should be organized and
 * managed using a linked data structure. The program asks a question to the player, input the player’s answer, and check if the
 * player’s answer matches the actual answer. If so, award the player the award points for that
 * question. If the player enters the wrong answer the program should display the correct answer.
 *
 * Used assistance from David Morris to help with my configured LinkedLists
 * Consulted stack overflow for error message which was for missing return statement.
 */

//library imports
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <sstream>
using namespace std;

//linked list that holds a trivia question, answer, and point amount
//also trivia node structure
struct TriviaNode {
    string ques;
    string ans;
    int point;
    
    //pointer to other trivia node
    TriviaNode* next;
};

//initialized list for TriviaNode which includes a question, answer, point value, and node
TriviaNode* LinkedList();
TriviaNode* addNode(string ques, string ans, int point, TriviaNode* node); //ques is question, ans is answer

int askQuestion(TriviaNode* node, int number);

TriviaNode* Triviagame = LinkedList();
int finalScore = 0;

//Returns three questions below with answer and point value no matter how many questions the user creates
TriviaNode* LinkedList() {
    TriviaNode* question1 = new TriviaNode;
    TriviaNode* question2 = new TriviaNode;
    TriviaNode* question3 = new TriviaNode;
    
    //Question 1 with the highest point value
    question1->ques = "How long was the shortest war on record? (Hint: how many minutes)";
    question1->ans = "38";
    question1->point = 100;
    question1->next = question2;
    
    //question 2 with second highest point value
    question2->ques = "What was the Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    question2->ans = "Bank of Italy";
    question2->point = 50;
    question2->next = question3;
    
    //question 3 with third highest point value
    question3->ques = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
    question3->ans = "Wii Sports";
    question3->point = 20;
    question3->next = NULL;
    return question1;
}

//adds node using same layout of questions/answers/and point values
TriviaNode* addNode(string ques, string ans, int point, TriviaNode* node) {
    //new node for trivia
    TriviaNode* tail = new TriviaNode;
    tail->ques = ques;
    tail->ans = ans;
    tail->point = point;
    tail->next = NULL;
    TriviaNode* temp = node;
    
    //moves node to the end
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = tail;
    return(0);
}

//puts data into the node
int askQuestion(TriviaNode* node, int number) {
    TriviaNode* temp = node;
    int count = 1;
    while (temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    
    //empty list
    if (number < 1) {
        cout << "Warning - The number of trivia to be asked must be equal to or larger than 1.\n";
        return 1;
    }
    
    else if (number > count) {
        cout << "Warning - There are only " << count << " trivia in the list.\n";
        return 1;
    }
    
    //checks if answers to questions are right
    for (int i = 1; i <= number; i++) {
        string input;
        cout << "Question: " << node->ques << "\nAnswer: ";
        getline(cin, input);
        
        if (node->ans == input) {
            cout << "Your answer is correct. You recieve " << node->point << " points.\n";
            finalScore += node->point;
        }
        
        else {
            cout << "Your answer is wrong. The correct answer is: " << node->ans << "\n";
        }
        
        node = node->next;
        cout << "Your total points: " << finalScore << "\n\n";
    }
    return 0;
}

/* ******************************** TESTING *********************************** */
#ifdef UNIT_TESTING
int main() {
    int x;
    cout << "\n*** This is a debug version ***\n";
    
    cout << "Unit Test Case 1: Ask 0 questions. Will give warning message.\n";
    x = askQuestion(Triviagame, 0);
    if (x == 0) {
        cout << "Case 1 passed...\n\n";
    } else {
        cout << "\n";
    }
    
    cout << "Unit Test Case 2.1: Ask 1 question. The tester enters right answer.\n";
    x = askQuestion(Triviagame, 1);
    if (x == 0) {
        cout << "Case 2.1 passed...\n\n";
    } else {
        cout << "\n";
    }
    
    cout << "Unit Test Case 2.2: Ask 1 question with wrong answer.\n";
    x = askQuestion(Triviagame, 1);
    if (x == 0) {
        cout << "Case 2.2 passed...\n\n";
    } else {
        cout << "\n";
    }
    
    cout << "Unit Test Case 3.1: Ask 3 questions  with right answers.\n";
    x = askQuestion(Triviagame, 3);
    if (x == 0) {
        cout << "Case 3.1 passed...\n\n";
    } else {
        cout << "\n";
    }
    
    cout << "Unit Test Case 3.2: Ask 3 questions with wrong answers.\n";
    x = askQuestion(Triviagame, 3);
    if (x == 0) {
        cout << "Case 3.2 passed...\n\n";
    } else {
        cout << "\n";
    }
    
    cout << "Unit Test Case 4: Ask 5 questions program gives warning message.\n";
    x = askQuestion(Triviagame, 5);
    if (x == 0) {
        cout << "Case 4 passed...\n\n";
    } else {
        cout << "\n";
    }
    
    cout << "\n*** End of the Debug Version ***\n";
    
    /* ***************************** ENDS TESTING *************************************** */
}
#else
int main() {
    int number = 3;
    string cont;
    cout << "\n*** Welcome to Chris's trivia quiz game ***\n";
    
    //data added to linkedlist
    do  {
        string question;
        string answer;
        string score;
        
        cout << "Enter a question: ";
        getline(cin, question);
        
        cout << "Enter an answer: ";
        getline(cin, answer);
        
        cout << "Enter award points: ";
        getline(cin, score);
        
        stringstream geek(score);
        int sc = 0;
        geek >> sc;
        
        //continue?
        cout << "Continue? (Yes/No): ";
        getline(cin, cont);
        addNode(question, answer, sc, Triviagame);
        number++;
    }
    
    while (cont == "Yes");
    cout << "\n";
    askQuestion(Triviagame, number);
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
    return(0);
}
#endif
