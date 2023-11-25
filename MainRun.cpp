#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;
#define endl '\n'

struct ExamInfor
{
    string name, id, time;
    int rightAns;
    double mark;
    void ShowInfor(int quests)
    {
        cout << "+----------------------------------+" << endl;
        cout << "|          Congratulation!!        |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << "Student's name: " << name << endl;
        cout << "Student's ID: " << id << endl;
        cout << "Done at: " << time << endl;
        cout << "Pass: " << rightAns << "/" << quests << endl;
        cout << "Mark of exam: " << mark << endl;
    }
    void CheckPoint()
    {
        ofstream out;
        out.open("checkpoint.txt", ios::app | ios::out);
        out << endl;
        out << name << endl;
        out << id << endl;
        out << time << endl;
        out << rightAns << endl;
        out << mark << endl;
        out.close();
    }
};
struct Quest
{
    string quest, A, B, C, D, ans, studentAns;
};
class Node
{
public:
    Quest data;
    Node* next;
};
Node* makeNode(Quest q)
{
    Node* newNode = new Node;
    newNode->data.quest = q.quest;
    newNode->data.A = q.A;
    newNode->data.B = q.B;
    newNode->data.C = q.C;
    newNode->data.D = q.D;
    newNode->data.ans = q.ans;
    newNode->data.studentAns = q.studentAns;
    newNode->next = NULL;
    return newNode;
}
string GetRealTime()
{
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M %d/%m/%Y", localTime);
    return buffer;
}
class Chain
{
private:
    Node* first, * last;
    int len;
public:
    Chain();
    ~Chain();
    void LoadQuests(string);
    void LoadResult(string);
    void Display(int);
    void DisplayResult();
    int Length() { return len; }
    Node* GetNodeAtIndex(int);
    void ClearFile(string);
    void WriteExam(string, Node*);
    void StudentExam(string, Node*);
    void Shuffling();
    void TakeExam();
    void ReviewExam();
};
Chain::Chain()
{
    first = last = NULL;
    len = 0;
}
Chain::~Chain()
{
    Node* p = first;
    while (p != NULL)
    {
        first = first->next;
        delete p;
        p = first;
    }
}
void Chain::LoadResult(string filename)
{
    ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        string line;
        while (getline(in, line))
        {
            Quest q;
            getline(in, q.quest);
            getline(in, q.A);
            getline(in, q.B);
            getline(in, q.C);
            getline(in, q.D);
            getline(in, q.ans);
            getline(in, q.studentAns);
            Node* newNode = makeNode(q);
            if (len == 0)
            {
                first = newNode;
                last = newNode;
            }
            else
            {
                last->next = newNode;
                last = newNode;
            }
            len++;
        }
    }
    else
    {
        cerr << "Error when load student's result ..." << endl;
        exit(EXIT_FAILURE);
    }
}
void Chain::LoadQuests(string filename)
{
    ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        string line;
        while (getline(in, line))
        {
            Quest q;
            getline(in, q.quest);
            getline(in, q.A);
            getline(in, q.B);
            getline(in, q.C);
            getline(in, q.D);
            getline(in, q.ans);
            Node* newNode = makeNode(q);
            if (len == 0)
            {
                first = newNode;
                last = newNode;
            }
            else
            {
                last->next = newNode;
                last = newNode;
            }
            len++;
        }
    }
    else
    {
        cerr << "Error when load questions ..." << endl;
        exit(EXIT_FAILURE);
    }
}
void Chain::ClearFile(string filename)
{
    ofstream ofs(filename, ios::trunc);
}
void Chain::WriteExam(string filename, Node* tmp)
{
    ofstream out;
    // write exam to file
    out.open(filename, ios::app | ios::out);
    out << endl;
    out << tmp->data.quest << endl;
    out << tmp->data.A << endl;
    out << tmp->data.B << endl;
    out << tmp->data.C << endl;
    out << tmp->data.D << endl;
    out << tmp->data.ans << endl;
    out.close();
}
void Chain::StudentExam(string filename, Node* tmp)
{
    ofstream out;
    // write exam history to file
    out.open(filename, ios::app | ios::out);
    out << endl;
    out << tmp->data.quest << endl;
    out << tmp->data.A << endl;
    out << tmp->data.B << endl;
    out << tmp->data.C << endl;
    out << tmp->data.D << endl;
    out << tmp->data.ans << endl;
    out << tmp->data.studentAns << endl;
    out.close();
}
void Chain::Display(int num)
{
    if (num <= 0 || num > len)
    {
        cerr << "Invalid number of questtions..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        Node* tmp = first;
        ClearFile("exam.txt");
        for (int i = 1; i <= num; i++)
        {
            WriteExam("exam.txt", tmp);
            if (i < 10)
            {
                cout << "Question 0" << i << " : " << tmp->data.quest << endl;
            }
            else
            {
                cout << "Question " << i << " : " << tmp->data.quest << endl;
            }
            cout << "A. " << tmp->data.A << endl;
            cout << "B. " << tmp->data.B << endl;
            cout << "C. " << tmp->data.C << endl;
            cout << "D. " << tmp->data.D << endl;
            tmp = tmp->next;
        }
    }
}
void Chain::DisplayResult()
{
    Node* tmp = first;
    while (tmp)
    {
        for (int i = 1; i <= len; i++)
        {
            WriteExam("exam.txt", tmp);
            if (i < 10)
            {
                cout << "Question 0" << i << " : " << tmp->data.quest << endl;
            }
            else
            {
                cout << "Question " << i << " : " << tmp->data.quest << endl;
            }
            cout << "A. " << tmp->data.A << endl;
            cout << "B. " << tmp->data.B << endl;
            cout << "C. " << tmp->data.C << endl;
            cout << "D. " << tmp->data.D << endl;
            cout << "The correct answer is: " << tmp->data.ans << endl;
            cout << "Your answer is: " << tmp->data.studentAns << endl;
            cout << ">>";
            if (tmp->data.ans == tmp->data.studentAns)
            {
                cout << "RIGHT! GOOD JOB!" << endl;
            }
            else
            {
                cout << "WRONG! GOOD LUCK!" << endl;
            }
            cout << endl;
            tmp = tmp->next;
        }
    }
}
Node* Chain::GetNodeAtIndex(int idx)
{
    Node* current = first;
    for (int i = 0; i < idx; i++)
    {
        current = current->next;
    }
    return current;
}
void Chain::Shuffling()
{
    if (len == 0)
    {
        return;
    }
    srand(time(0));
    // Fisher-Yates shuffle
    for (int i = len - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Node* nodeI = GetNodeAtIndex(i);
        Node* nodeJ = GetNodeAtIndex(j);
        Quest tmp = nodeI->data;
        nodeI->data = nodeJ->data;
        nodeJ->data = tmp;
    }
}
void Chain::TakeExam()
{
    ExamInfor student;
    student.rightAns = 0;
    Chain exam;
    cin.ignore(0);
    cout << "Enter your name: ";
    getline(cin, student.name);
    cout << "Enter your ID: ";
    getline(cin, student.id);
    cout << endl;
    exam.LoadQuests("exam.txt");
    ClearFile("student.txt");
    Node* tmp = exam.first;
    for (int i = 1; i <= exam.len; i++)
    {
        if (i < 10)
        {
            cout << "Question 0" << i << " : " << tmp->data.quest << endl;
        }
        else
        {
            cout << "Question " << i << " : " << tmp->data.quest << endl;
        }
        cout << "A. " << tmp->data.A << endl;
        cout << "B. " << tmp->data.B << endl;
        cout << "C. " << tmp->data.C << endl;
        cout << "D. " << tmp->data.D << endl;
        string ans;
        cout << ">> Answer [UPPER CASE]: ";
        getline(cin, ans);
        while (ans < "A" || ans > "D")
        {
            cout << "INVALID ANSWERS!! PLEASE ANSWER AGAIN." << endl;
            cout << ">> Answer [UPPER CASE]: ";
            getline(cin, ans);
        }
        tmp->data.studentAns = ans;
        if (ans == tmp->data.ans)
        {
            student.rightAns++;
        }
        StudentExam("student.txt", tmp);
        tmp = tmp->next;
        cout << endl;
    }
    student.time = GetRealTime();
    student.mark = student.rightAns * 10.0 / exam.len;
    student.ShowInfor(exam.len);
    student.CheckPoint();
}
void Chain::ReviewExam()
{
    Chain exam;
    exam.LoadQuests("exam.txt");
    Node* tmp = exam.first;
    for (int i = 1; i <= exam.len; i++)
    {
        if (i < 10)
        {
            cout << "Question 0" << i << " : " << tmp->data.quest << endl;
        }
        else
        {
            cout << "Question " << i << " : " << tmp->data.quest << endl;
        }
        cout << "A. " << tmp->data.A << endl;
        cout << "B. " << tmp->data.B << endl;
        cout << "C. " << tmp->data.C << endl;
        cout << "D. " << tmp->data.D << endl;
        cout << ">> Answer: " << tmp->data.ans << endl;
        tmp = tmp->next;
        cout << endl;
    }
}

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
void ReviewLastesExam()
{
    cout << "+----------------------------------+" << endl;
    cout << "|TEACHER IS REVIEW THE LASTEST EXAM|" << endl;
    cout << "+----------------------------------+" << endl;
    Chain quest;
    quest.ReviewExam();
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
    cout << "|  2. Review lastest random exam.  |" << endl;
    cout << "|  3. Add a question to database.  |" << endl;
    cout << "|  4. Review student exam result.  |" << endl;
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
        ReviewLastesExam();
        break;
    case 3:
        AddQuestion();
        break;
    case 4:
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

int main()
{
    WelcomeMessage();
}