#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
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