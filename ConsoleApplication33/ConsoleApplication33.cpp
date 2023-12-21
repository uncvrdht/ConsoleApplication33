#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    double averageGrade;
    string name;

public:
    Student() { averageGrade = 0.0; name = ""; }
    Student(double a, string n) { averageGrade = a; name = n; }

    string GetName() const { return name; }
    double GetAverage() { return averageGrade; }

    bool operator==(const Student& other) const { return averageGrade == other.averageGrade; }
    bool operator!=(const Student& other) const { return !(*this == other); }
    bool operator>(const Student& other) const { return averageGrade > other.averageGrade; }
    bool operator<(const Student& other) const { return averageGrade < other.averageGrade; }

    operator const string() {
        return "Имя " + GetName() + ", " + to_string(GetAverage()) + " средняя оценка";
    }
};

class Group {
private:
    int numberOfStudents;
    string name;
    int course;
    Student* students;

public:
    Group() { numberOfStudents = 0; students = nullptr; }
    Group(int count) { numberOfStudents = count; students = new Student[numberOfStudents]; }
    Group(const Group& other) { this->CopyFrom(other); }//КОНСТРУКТОР КОПИРОВАНИЯ

    bool operator == (const Group& other) const { return numberOfStudents == other.numberOfStudents; }
    bool operator != (const Group& other) const { return !(*this == other); }

    operator const string() {
        return "Группа " + GetName() + " " + to_string(GetCourse()) + " курс, студентов: " + to_string(GetNumberOfStudents());
    }

    void SetNumber(int n) { numberOfStudents = n; }
    void SetName(const string& g) { name = g; }
    void SetCourse(int c) { course = c; }

    int GetNumberOfStudents() const { return numberOfStudents; }
    string GetName() const { return name; }
    int GetCourse() const { return course; }

    void CopyFrom(const Group& other) {
        delete[] students;

        numberOfStudents = other.numberOfStudents;

        students = new Student[numberOfStudents];
        for (int i = 0; i < numberOfStudents; i++) {
            students[i] = other.students[i];
        }
    }
    //ПЕРЕГРУЗКА =
    Group& operator = (const Group& other) {
    if (this != &other) {
        delete[] students;
        numberOfStudents = other.numberOfStudents;
        name = other.name;
        course = other.course;
        this->CopyFrom(other);
    }
    return *this;
}

    void PrintStudents() {
        for (int i = 0; i < numberOfStudents; i++) {
            cout << (string)students[i] << "\n";
        }
    }

    void AddStudent(const Student& student) {
        numberOfStudents++;

        Student* newStudents = new Student[numberOfStudents];
        if (numberOfStudents > 1) {
            this->CopyFrom(*this);
        }
        newStudents[numberOfStudents - 1] = student;

        delete[] students;
        students = newStudents;
    }

    ~Group() {
        delete[] students;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Student stud1(4.5, "Алина");
    Student stud2(3.4, "Гоша");
    Student stud3(2.2, "Стас");
    Student stud4(4.5, "Вова");

    cout << "Stud1: " << (string)stud1 << "\n";
    cout << "Stud2: " << (string)stud2 << "\n";
    cout << " == " << (stud1 == stud2) << "\n";
    cout << " != " << (stud1 != stud2) << "\n";
    cout << " > " << (stud1 > stud2) << "\n";
    cout << " < " << (stud1 < stud2) << "\n";

    cout << "Stud1: " << (string)stud1 << "\n";
    cout << "Stud4: " << (string)stud4 << "\n";
    cout << " == " << (stud1 == stud4) << "\n";
    cout << " != " << (stud1 != stud4) << "\n";
    cout << " > " << (stud1 > stud4) << "\n";
    cout << " < " << (stud1 < stud4) << "\n";

    Group group1; group1.SetName("Группа 1"); group1.SetCourse(1);
    Group group2; group2.SetName("Группа 2"); group2.SetCourse(1);

    group1.AddStudent(stud1);
    group1.AddStudent(stud2);

    group2.AddStudent(stud3);

    cout << "Group1: " << "\n"; group1.PrintStudents();
    cout << "Group2: " << "\n"; group2.PrintStudents();
    cout << " == " << (group1 == group2) << "\n";
    cout << " != " << (group1 != group2) << "\n";

    group2.AddStudent(stud4);

    cout << "Group1: " << "\n"; group1.PrintStudents();
    cout << "Group2: " << "\n"; group2.PrintStudents();
    cout << " == " << (group1 == group2) << "\n";
    cout << " != " << (group1 != group2) << "\n";
    
    Group group3(group1);
    Group group4; group4 = group2;
    cout << "Group3: " << "\n"; group3.PrintStudents();
    cout << "Group4: " << "\n"; group4.PrintStudents();
    return 0;
}
