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
bool isValidGrade(char grade);

//Function to check if credit hours are valid (greater than zero and within maximum limit)
bool isValidCreditHours(int creditHours);

//Function to input course names
vector<string> inputCourseNames();

//Function to input grade and credit hours for a course
pair<char, int> inputGradeAndCreditHours(const string& courseName);

//Function to calculate the CGPA
double calculateCGPA(const vector<char>& grades, const vector<int>& creditHours);

int main() 
{
    //Input course names
    vector<string> courseNames = inputCourseNames();

    //Input grades and credit hours for each course
    vector<char> grades;
    vector<int> creditHours;

    for (const auto& course : courseNames) 
    {
        pair<char, int> gradeAndCreditHours = inputGradeAndCreditHours(course);
        grades.push_back(gradeAndCreditHours.first);
        creditHours.push_back(gradeAndCreditHours.second);
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

bool isValidGrade(char grade) 
{
    //Convert grade to uppercase
    grade = toupper(grade);

    return (grade >= 'A' && grade <= 'F');
}

bool isValidCreditHours(int creditHours) 
{
    return creditHours > 0 && creditHours <= MAX_CREDIT_HOURS;
}

vector<string> inputCourseNames() 
{
    vector<string> courseNames;
    char continueAdding;

    do 
    {
        string courseName;
        cout << "Enter course name: ";
        getline(cin, courseName);
        courseNames.push_back(courseName);

        do 
        {
            cout << "Do you want to add another course? (y/n): ";
            cin >> continueAdding;

            if (tolower(continueAdding) != 'y' && tolower(continueAdding) != 'n') 
                cout << "Invalid input! Please enter 'y' for yes or 'n' for no." << endl;

        } 
        while (tolower(continueAdding) != 'y' && tolower(continueAdding) != 'n');

        //Ignore newline character from previous input
        cin.ignore();
    } 
    while (tolower(continueAdding) == 'y');

    return courseNames;
}

pair<char, int> inputGradeAndCreditHours(const string& courseName) 
{
    char grade;
    int creditHours;

    cout << "Enter grade for " << courseName << ": ";
    cin >> grade;

    while (!isValidGrade(grade)) 
    {
        cout << "Invalid grade! Please enter a valid letter grade (A, B, C, etc.): ";
        cin >> grade;
    }

    do 
    {
        cout << "Enter credit hours for " << courseName << ": ";
        cin >> creditHours;

        if (!isValidCreditHours(creditHours)) 
            cout << "Invalid input! Credit hours must be greater than zero and less than or equal to " << MAX_CREDIT_HOURS << "." << endl;

    } 
    while (!isValidCreditHours(creditHours));

    return make_pair(grade, creditHours);
}

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