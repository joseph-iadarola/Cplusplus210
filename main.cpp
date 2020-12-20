/*
 *  Creator: Joseph Iadarola
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void printTableHeader(string title){
    //This function prints the header for each table since both are similar
    cout << title << "\n";
    cout << "______________________________________________________\n";
    cout << "Year  |  Year End Balance  |  Year End Earned Interest\n";
    cout <<"_______________________________________________________\n";
}

double findInterestGain(double openingBal, double deposit, double interestRate){
    //This single line function is used to reduce math being done in the print function
    return (openingBal+deposit)*(interestRate/12);
}

void printBankTables(vector<double> bankVals){
    //This function prints a formatted table and calls functions to do math
    double t_openingBalance=bankVals.front(), t_closingBalance, t_interestAmount, t_totalInterest = 0.0;

    printTableHeader("Balance and Interest Without Additional Monthly Deposit"); //prints first tables header

    cout << fixed<<std::setprecision(2); //needed to keep the printed values in dollar/cents form

    for(int i=1;i<=bankVals.back();i++){ //the last value in bankVal is the years
        t_interestAmount = t_openingBalance*(bankVals[2]); //simple math to find interest earned per year
        t_closingBalance = t_openingBalance+t_interestAmount; //needed so that t_openingBalance can be changed after print
        cout << i << "\t\t$" << t_closingBalance << "\t\t$" << t_interestAmount << endl;
        t_openingBalance = t_closingBalance; //previous closing balance is the new opening balance
    }
    cout << endl;
    //reset variables
    t_openingBalance = bankVals.front();
    t_closingBalance = 0.0;
    t_interestAmount = 0.0;
    //print next tables header
    printTableHeader("Balance and Interest With Additional Monthly Deposit");
    for(int j=1; j<=bankVals.back(); j++){ //will run the same number of times as previous loop
        for(int x = 1; x<=12; x++){ //needed since there are 12 months in a year
            //call function that has a more complex equation
            t_interestAmount = findInterestGain(t_openingBalance,bankVals[1],bankVals[2]);
            t_closingBalance = t_openingBalance + bankVals[1] + t_interestAmount;
            t_totalInterest += t_interestAmount; //records the sum of the interest made for each loop/month
            t_openingBalance = t_closingBalance; //previous closing balance is the new opening balance
        }
        cout << j << "\t\t$" << t_closingBalance << "\t\t$" << t_totalInterest << endl; //prints row for each year
        t_totalInterest = 0.0; //reset interest earned for that year
    }

}

vector<double> userInputForm(){
    //This function deals with the logic needed to get bank information from user
    double t_start=0.0, t_monthly=0.0, t_interest=0.0, t_year=0.0; //need to be initialized because of recursion
    string t_line;
    vector<double> t_bankVals; //will have four values when it is returned

    //Form Print
    cout << "************** Data Input ****************\n";
    cout << "****** Enter an integer or decimal. ******\n"; //The program will break if this instruction is not followed
    cout << "* Press Enter after entering each value. *\n";
    cout << "** Failure to follow above instructions **\n";
    cout << "**** will cause program ending error. ****\n"; //This allows for minimal error testing

    cout << "Initial Investment Amount: $";
    std::getline(cin,t_line); //getline is used each time because the compiler will cause problems if it is not
    t_start = std::stod(t_line);
    t_bankVals.push_back(t_start);

    cout << "Monthly Deposit: $";
    std::getline(cin,t_line);
    t_monthly = std::stod(t_line);
    t_bankVals.push_back(t_monthly);

    cout << "Annual Interest(%): ";
    std::getline(cin,t_line);
    t_interest = std::stod(t_line);
    t_interest/=100;            //This changes whole percentage into decimal form
    t_bankVals.push_back(t_interest);

    cout << "Number of years: ";
    std::getline(cin,t_line);
    t_year = std::stod(t_line); //Years are changed into decimal form but only the integer is used
    t_bankVals.push_back(t_year);

    cout << "Type y to continue or anything else to re-enter values: ";
    std::getline(cin, t_line);
    if(t_line=="y"){
        return t_bankVals;
    }else {
        return userInputForm(); //This will start the form over again
    }

}

void bankAppStart(){
    //This function loops program and calls functions in order
    bool again = true; //used to continue/end program loop
    string t_yes; //used at the end of while loop
    while(again){
        std::vector<double> bankVals = userInputForm(); //vector will have four values
        printBankTables(bankVals); //calls the function that prints the tables
        cout << "Type y and press enter if you would like to start over: ";
        std::getline(cin, t_yes); //getline is needed here
        if(t_yes!="y"){ //anything but y will end program
            again = false; //this will stop the loop from executing again
        }
        bankVals.~vector<double>(); //needed so that there are no problems when the loop executes again
    }
}

int main() {
    //single line main()
    bankAppStart();
    return 0;
}
