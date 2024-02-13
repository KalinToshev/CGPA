#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

//Function to check if a character is a valid letter grade (A, B, C, etc.)
bool isValidGrade(char grade)
{
    return (grade >= 'A' && grade <= 'F') || (grade >= 'a' && grade <= 'f');
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

    //Calculate and display CGPA
    double cgpa = calculateCGPA(grades, creditHours);
    cout << "Your CGPA is: " << fixed << setprecision(2) << cgpa << endl;

    return 0;
}