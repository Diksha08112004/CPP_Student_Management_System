// Filename: student_management.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Student {
private:
    int roll;
    string name;
    string course;
    float marks;

public:
    void input();
    void display() const;
    int getRoll() const;
    float getMarks() const;
    string getName() const;
    void update();
};

void Student::input() {
    cout << "Enter Roll Number: "; cin >> roll;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Course: "; getline(cin, course);
    cout << "Enter Marks: "; cin >> marks;
}

void Student::display() const {
    cout << left << setw(10) << roll << setw(20) << name << setw(15) << course << setw(10) << marks << endl;
}

int Student::getRoll() const {
    return roll;
}

float Student::getMarks() const {
    return marks;
}

string Student::getName() const {
    return name;
}

void Student::update() {
    cout << "Updating record for Roll No. " << roll << endl;
    cin.ignore();
    cout << "Enter new name: "; getline(cin, name);
    cout << "Enter new course: "; getline(cin, course);
    cout << "Enter new marks: "; cin >> marks;
}

class StudentManager {
private:
    vector<Student> students;
    string filename = "students.dat";

public:
    StudentManager();
    void addStudent();
    void displayAll();
    void searchStudent();
    void deleteStudent();
    void updateStudent();
    void sortByMarks();
    void sortByName();
    void saveToFile();
    void loadFromFile();
};

StudentManager::StudentManager() {
    loadFromFile();
}

void StudentManager::addStudent() {
    Student s;
    s.input();
    students.push_back(s);
    saveToFile();
    cout << "Student added successfully!\n";
}

void StudentManager::displayAll() {
    cout << "\n--- All Student Records ---\n";
    cout << left << setw(10) << "Roll" << setw(20) << "Name" << setw(15) << "Course" << setw(10) << "Marks\n";
    for (const Student& s : students)
        s.display();
}

void StudentManager::searchStudent() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;
    for (const Student& s : students) {
        if (s.getRoll() == roll) {
            cout << "Student found:\n";
            s.display();
            return;
        }
    }
    cout << "Student not found!\n";
}

void StudentManager::deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;
    auto it = remove_if(students.begin(), students.end(), [roll](Student& s) {
        return s.getRoll() == roll;
    });
    if (it != students.end()) {
        students.erase(it, students.end());
        saveToFile();
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found!\n";
    }
}

void StudentManager::updateStudent() {
    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;
    for (Student& s : students) {
        if (s.getRoll() == roll) {
            s.update();
            saveToFile();
            cout << "Student updated successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void StudentManager::sortByMarks() {
    sort(students.begin(), students.end(), [](Student& a, Student& b) {
        return a.getMarks() > b.getMarks();
    });
    cout << "Sorted by marks (descending).\n";
    displayAll();
}

void StudentManager::sortByName() {
    sort(students.begin(), students.end(), [](Student& a, Student& b) {
        return a.getName() < b.getName();
    });
    cout << "Sorted by name (A-Z).\n";
    displayAll();
}

void StudentManager::saveToFile() {
    ofstream out(filename, ios::binary | ios::trunc);
    for (const Student& s : students)
        out.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    out.close();
}

void StudentManager::loadFromFile() {
    ifstream in(filename, ios::binary);
    if (!in) return;
    Student s;
    while (in.read(reinterpret_cast<char*>(&s), sizeof(Student)))
        students.push_back(s);
    in.close();
}

bool login() {
    string user, pass;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;
    return (user == "admin" && pass == "1234");
}

int main() {
    if (!login()) {
        cout << "Access denied!\n";
        return 0;
    }

    StudentManager manager;
    int choice;

    do {
        cout << "\n==== Student Management System ====\n";
        cout << "1. Add Student\n2. Display All\n3. Search Student\n4. Delete Student\n";
        cout << "5. Update Student\n6. Sort by Marks\n7. Sort by Name\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.displayAll(); break;
            case 3: manager.searchStudent(); break;
            case 4: manager.deleteStudent(); break;
            case 5: manager.updateStudent(); break;
            case 6: manager.sortByMarks(); break;
            case 7: manager.sortByName(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
