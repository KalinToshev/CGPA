#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Function to check if a character is a valid letter grade (A, B, C, etc.)
bool isValidGrade(char grade)
{
    return (grade >= 'A' && grade <= 'F') || (grade >= 'a' && grade <= 'f');
}

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
    
    //Ask user to enter grades and credit hours for each course
    for (const auto& course : courseNames)
    {
        char grade; 
        int creditHour;

        cout << "Enter grade for " << course << ": ";
        cin >> grade;

        while (!isValidGrade(grade))
        {
            cout << "Invalid grade! Please enter a valid letter grade (A, B, C, etc.): ";
            cin >> grade;
        }

        cout << "Enter credit hours for " << course << ": ";
        cin >> creditHour;

        //Store grade and credit hour
        grades.push_back(grade);
        creditHours.push_back(creditHour);
    }
    
    return 0;
}