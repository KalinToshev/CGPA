#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

//Constants for messages
const string ENTER_COURSE_NAME_MESSAGE = "Enter course name: ";
const string CONTINUE_ADDING_COURSE_MESSAGE = "Do you want to add another course? (y/n): ";
const string INVALID_YES_NO_INPUT_MESSAGE = "Invalid input! Please enter 'y' for yes or 'n' for no.";
const string ENTER_GRADE_MESSAGE = "Enter grade for ";
const string INVALID_GRADE_INPUT_MESSAGE = "Invalid grade! Please enter a valid letter grade (A, B, C, etc.): ";
const string ENTER_CREDIT_HOURS_MESSAGE = "Enter credit hours for ";
const string INVALID_CREDIT_HOURS_INPUT_MESSAGE = "Invalid input! Credit hours must be greater than zero and less than or equal to 1000.";
const string NO_COURSES_ENTERED = "No courses entered. CGPA calculation cannot proceed.";

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
        cout << NO_COURSES_ENTERED << endl;
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
        cout << ENTER_COURSE_NAME_MESSAGE;
        getline(cin, courseName);
        courseNames.push_back(courseName);

        do 
        {
            cout << CONTINUE_ADDING_COURSE_MESSAGE;
            cin >> continueAdding;

            if (tolower(continueAdding) != 'y' && tolower(continueAdding) != 'n') 
                cout << INVALID_YES_NO_INPUT_MESSAGE << endl;

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

    cout << ENTER_GRADE_MESSAGE << courseName << ": ";
    cin >> grade;

    while (!isValidGrade(grade)) 
    {
        cout << INVALID_GRADE_INPUT_MESSAGE;
        cin >> grade;
    }

    do 
    {
        cout << ENTER_CREDIT_HOURS_MESSAGE << courseName << ": ";
        cin >> creditHours;

        if (!isValidCreditHours(creditHours)) 
            cout << INVALID_CREDIT_HOURS_INPUT_MESSAGE << endl;

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