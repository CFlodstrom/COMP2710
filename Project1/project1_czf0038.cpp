//Chris Flodstrom
//Project1.cpp
//This project is a repayment calculator that accounts for interest.
// This output will display the total amount of months it would take to pay off
// the balance, payment, the interest rate, the interest, and principal
//
// I worked alongside David Morris and Jonathan Blackburn. They were able to
// assist me with formatting issues in my table and an issue where my while statement wouldnt
// fully execute past the first month of output.
// I also used StackOverflow to refresh my knowledge about do while and while loops.


#include <iostream>
using namespace std;

int main()
{
    double loan = 0;
    double interestRate = 0;
    double interestRateC =0;
    double monthlyPaid = 0;
    int currentMonth = 0;
    double currInt = 0;
    double interestTotal = 0;
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    do {
    cout << "\nLoan Amount: ";
    cin >> loan;
    }
        while (loan < 1);
    
    do{
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    }
        while (interestRate <= 1);
        interestRate /= 12;
        interestRateC = interestRate / 100;
    
    do {
    cout << "Monthly Payments: " ;
    cin >> monthlyPaid;
    }
        while (monthlyPaid < interestRateC * loan);
            cout << endl;
            cout << "*****************************************************************\n"
                 << "\tAmortization Table\n"
                 << "*****************************************************************\n"
                 << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
    
    while (loan > 0) {
        if (currentMonth == 0) {
            cout << currentMonth++ << "\t$" << loan;
                if (loan < 1000) cout << "\t";
                cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
        }
        else {
            currInt = interestRateC * loan;
            interestTotal += currInt;
            if (loan > monthlyPaid) {
            loan -= (monthlyPaid - currInt);
            }
                else {
                    monthlyPaid = loan + currInt;
                    loan = 0;
            }
            
            cout << currentMonth++ <<"\t$" << loan;
                if (loan < 1000) cout << "\t";
                cout << "\t$" << monthlyPaid << "\t" << interestRate << "\t$" << currInt;
                cout << "\t\t$" << monthlyPaid - currInt << "\n";
        }
        }
        cout << "*****************************************************************\n";
        cout << "\nIt takes " << --currentMonth << " month to pay off "
             << "the loan. \n"<< "Total interest paid is: $" << interestTotal;
        cout << endl << endl;
        return 0;
}
