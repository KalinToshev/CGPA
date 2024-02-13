#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ios>

using namespace std;

//Set a maximum value for credit hours
const int MAX_CREDIT_HOURS = 1000;

//Function to check if a character is a valid letter grade (A, B, C, etc.)
bool isValidGrade(char grade) 
{
    //Convert grade to uppercase
    grade = toupper(grade);

    return (grade >= 'A' && grade <= 'F');
}


//Function to calculate the CGPA
double calculateCGPA(const vector<char>& grades, const vector<int>& creditHours)
{
    double totalGradePoints = 0;
    int totalCreditHours = 0;

    //Calculate total grade points and total credit hours
    for (size_t i = 0; i < grades.size(); i++)
    {
        //Convert letter grade to grade points (assuming 4-points scale)
        double gradePoints = 4.0 - (toupper(grades[i]) - 'A');
        totalGradePoints += gradePoints * creditHours[i];
        totalCreditHours += creditHours[i];
    }

    //Calculate CGPA
    return totalGradePoints / totalCreditHours;
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
        bool isValidInput = false;

        cout << "Enter grade for " << course << ": ";
        cin >> grade;

        while (!isValidGrade(grade))
        {
            cout << "Invalid grade! Please enter a valid letter grade (A, B, C, etc.): ";
            cin >> grade;
        }

        //Ask user to enter credit hours for each course, with error handling
        do
        {
            cout << "Enter credit hours for " << course << ": ";
            if (!(cin >> creditHour))
            {
                cout << "Invalid input! Please enter a valid numeric value for credit hours." << endl;
                cin.clear();

                //Clear input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (creditHour <= 0)
            {
                cout << "Invalid input! Credit hours must be greater than zero." << endl;
            }
            else if (creditHour > MAX_CREDIT_HOURS)
            {
                cout << "Invalid input! Credit hours cannot exceed " << MAX_CREDIT_HOURS << "." << endl;
            }
            else
            {
                isValidInput = true;
            }
        } while (!isValidInput);
        

        //Store grade and credit hour
        grades.push_back(grade);
        creditHours.push_back(creditHour);
    }

    //Check if there are no courses entered
    if (courseNames.empty()) 
    {
        cout << "No courses entered. CGPA calculation cannot proceed." << endl;
    } 
    else 
    {
    //Calculate and display CGPA
    double cgpa = calculateCGPA(grades, creditHours);
    cout << "Your CGPA is: " << fixed << setprecision(2) << cgpa << endl;
    }

    return 0;
}