#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> courseNames;
    vector<char> grades;
    vector<int> creditHours;
    char continueAdding;

    //Ask user to enter course names
    do
    {
        string courseName;
        cout << "Enter course name: ";
        getline(cin, courseName);
        courseNames.push_back(courseName);

        cout << "Do you want to add another course? (y/n): ";
        cin >> continueAdding;

        //Ignore newline character from previous input
        cin.ignore();
    } while (tolower(continueAdding) == 'y');
    

    return 0;
}