#include <iostream>
#include <string>
#include <iomanip>
#include "DataStructure.cpp"

using namespace std;
void GenerateExam()
{
    cout << "+----------------------------------+" << endl;
    cout << "|  GERNERATING EXAM FOR STUDENTS   |" << endl;
    cout << "+----------------------------------+" << endl;
    int numberOfQuest;
    cout << "Enter NO. questions in exam: ";
    cin >> numberOfQuest;
    Chain quest;
    quest.LoadQuests("data.txt");
    quest.Shuffling();
    quest.Display(numberOfQuest);
    cout << "+----------------------------------+" << endl;
    cout << "|      GENERATING EXAM DONE!!      |" << endl;
    cout << "+----------------------------------+" << endl;
}
void AddQuestion()
{
    cout << "+----------------------------------+" << endl;
    cout << "|   ADDING QUESTIONS TO DATABASE   |" << endl;
    cout << "+----------------------------------+" << endl;
    Quest quest;
    cout << "Enter the question: ";
    getline(cin, quest.quest);
    cout << "Enter option A: ";
    getline(cin, quest.A);
    cout << "Enter option B: ";
    getline(cin, quest.B);
    cout << "Enter option C: ";
    getline(cin, quest.C);
    cout << "Enter option D: ";
    getline(cin, quest.D);
    cout << "Enter answer [A or B or C or D]: ";
    getline(cin, quest.ans);
    ofstream out;
    out.open("data.txt", ios::app | ios::out);
    out << endl;
    out << quest.quest << endl;
    out << quest.A << endl;
    out << quest.B << endl;
    out << quest.C << endl;
    out << quest.D << endl;
    out << quest.ans << endl;
    out.close();
    cout << "+----------------------------------+" << endl;
    cout << "|       DONE ADDING QUESTIONS      |" << endl;
    cout << "+----------------------------------+" << endl;
}
void ReviewResult()
{
    cout << "+----------------------------------+" << endl;
    cout << "|   REVIEW STUDENT'S EXAM RESULT   |" << endl;
    cout << "+----------------------------------+" << endl;
    ifstream in;
    in.open("checkpoint.txt");
    cout << '+' << setfill('-') << setw(90) << '+' << setfill(' ') << endl;
    cout << '|' << setw(20) << left << "Student's name"
        << '|' << setw(15) << left << "Student's ID"
        << '|' << setw(20) << left << "Time"
        << '|' << setw(15) << left << "Right answers"
        << '|' << setw(15) << left << "Result"
        << '|' << endl;
    cout << setfill('-') << setw(90) << '+' << setfill(' ') << '+' << endl;
    if (in.is_open())
    {
        string line;
        while (getline(in, line))
        {
            getline(in, line);
            cout << '|' << setw(20) << left << line;
            getline(in, line);
            cout << '|' << setw(15) << left << line;
            getline(in, line);
            cout << '|' << setw(20) << left << line;
            getline(in, line);
            cout << '|' << setw(15) << left << line;
            getline(in, line);
            cout << '|' << setw(15) << left << line << '|' << endl;
        }
    }
    else
    {
        cerr << "Error when load history of taking exam ..." << endl;
        exit(EXIT_FAILURE);
    }
    cout << setfill('-') << setw(90) << '+' << setfill(' ') << '+' << endl;
}
void TeacherOption()
{
    cout << "+----------------------------------+" << endl;
    cout << "|      CHOOSE TEACHER'S OPTION     |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "|  1. Generate a random exam.      |" << endl;
    cout << "|  2. Add a question.              |" << endl;
    cout << "|  3. Review student exam.         |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << ">> Enter your choice: ";
    int option; cin >> option;
    cin.ignore(1);
    switch (option)
    {
    case 1:
        GenerateExam();
        break;
    case 2:
        AddQuestion();
        break;
    case 3:
        ReviewResult();
        break;
    default:
        cout << "Invalid option." << endl;
        break;
    }
}
void TakingExam()
{
    cout << "+----------------------------------+" << endl;
    cout << "|    STUDENT IS TAKING THE EXAM    |" << endl;
    cout << "+----------------------------------+" << endl;
    Chain quest;
    quest.TakeExam();
    cout << "+----------------------------------+" << endl;
    cout << "|       DONE TAKING THE EXAM       |" << endl;
    cout << "+----------------------------------+" << endl;
}
void ReviewingExam()
{
    Chain exam;
    exam.LoadResult("student.txt");
    cout << "+----------------------------------+" << endl;
    cout << "|    REVIEWING YOUR EXAM RESULT    |" << endl;
    cout << "+----------------------------------+" << endl;
    exam.DisplayResult();
    cout << "+----------------------------------+" << endl;
    cout << "|    GOOD LUCK IN YOUR NEXT EXAM   |" << endl;
    cout << "+----------------------------------+" << endl;
}
void StudentOption()
{
    Chain trackingExam; // keep track student exam
    cout << "+----------------------------------+" << endl;
    cout << "|      CHOOSE STUDENT'S OPTION     |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "|  1. Taking exam.                 |" << endl;
    cout << "|  2. Review exam.                 |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << ">> Enter your choice: ";
    int option; cin >> option;
    cin.ignore(1);
    switch (option)
    {
    case 1:
        TakingExam();
        break;
    case 2:
        ReviewingExam();
        break;
    default:
        cout << "Invalid option." << endl;
        break;
    }
}
void WelcomeMessage()
{
    while (true)
    {
        cout << "+----------------------------------+" << endl;
        cout << "|   Welcome to the Quiz Program!   |" << endl;
        cout << "|      CHOOSE YOUR MODE BELOW      |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << "|      1. Teacher                  |" << endl;
        cout << "|      2. Student                  |" << endl;
        cout << "|      3. Exit!                    |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << ">> Enter your choice: ";
        int option;
        cin >> option;
        if (option == 1)
        {
            TeacherOption();
        }
        else if (option == 2)
        {
            StudentOption();
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            cout << "+----------------------------------+" << endl;
            cout << "|         INVALID MODE !!          |" << endl;
            cout << "+----------------------------------+" << endl;
        }
    }
}