#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int courses;
    float grade[50], credit[50];
    float totalCredits = 0;
    float totalGradePoints = 0;
    float GPA, CGPA;

    cout << "Enter number of courses: ";
    cin >> courses;

    while (cin.fail() || courses <= 0 || courses > 50)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid input! Enter courses between 1 and 50: ";
        cin >> courses;
    }

    for (int i = 0; i < courses; i++)
    {
        cout << "\nEnter grade for course " << i + 1 << ": ";
        cin >> grade[i];

        while (cin.fail() || grade[i] < 0 || grade[i] > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid grade! Enter grade between 0 and 4: ";
            cin >> grade[i];
        }

        cout << "Enter credit hours: ";
        cin >> credit[i];

        while (cin.fail() || credit[i] <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid credit hours! Enter a positive number: ";
            cin >> credit[i];
        }

        totalCredits += credit[i];
        totalGradePoints += grade[i] * credit[i];
    }

    GPA = totalGradePoints / totalCredits;
    CGPA = GPA;

    cout << fixed << setprecision(2);

    cout << "\n-------- Course Details --------\n";

    for (int i = 0; i < courses; i++)
    {
        cout << "Course " << i + 1
            << " | Grade: " << grade[i]
            << " | Credit Hours: " << credit[i] << endl;
    }

    cout << "\nTotal Credit Hours: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << "\nSemester GPA: " << GPA;
    cout << "\nOverall CGPA: " << CGPA;

    return 0;
}
