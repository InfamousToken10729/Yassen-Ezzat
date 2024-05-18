#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Student {
private:
    int student_id = 0;
    string name;
    vector<float> marks;
    char grade = ' ';

public:
    void add_marks(const vector<float>& subject_marks) {
        marks = subject_marks;
        calculate_grade();
    }

    void calculate_grade() {
        double total_marks = 0;
        for (float mark : marks) {
            total_marks += mark;
        }
        double average_marks = total_marks / marks.size();

        if (average_marks >= 90) {
            grade = 'A';
        }
        else if (average_marks >= 80) {
            grade = 'B';
        }
        else if (average_marks >= 70) {
            grade = 'C';
        }
        else if (average_marks >= 60) {
            grade = 'D';
        }
        else {
            grade = 'F';
        }
    }

    int get_student_id() const {
        return student_id;
    }

    string get_name() const {
        return name;
    }

    char get_grade() const {
        return grade;
    }

    vector<float> get_marks() const {
        return marks;
    }
    void set_id(int id) {
        student_id = id;
    }
    void set_name(const string& new_name) {
        name = new_name;
    }
    void display() const {
        cout << "Student ID: " << student_id << ", Name: " << name << endl;
    }
};

class StudentManagementSystem {
private:
    static vector<Student> students;
    string admin_password = "admin";

public:
    const vector<Student>& get_students() const {
        return students;
    }

    void set_students(const vector<Student>& new_students) {
        students = new_students;
    }

    void add_student_record(const Student& new_student) {
        students.push_back(new_student);
    }

    void search_student_record(int id) {
        bool found = false;
        for (const auto& student : students) {
            if (student.get_student_id() == id) {
                student.display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found!" << endl;
        }
    }

    void modify_student_record() {
        int id;
        cout << "Enter the ID of the student whose record you want to modify: ";
        cin >> id;

        bool found = false;
        for (auto& student : students) {
            if (student.get_student_id() == id) {
                cout << "Current student information:" << endl;
                student.display();

                int new_id;
                string new_name;
                vector<float> new_marks;

                cout << "Enter new student ID: ";
                cin >> new_id;
                cout << "Enter new name: ";
                cin >> new_name;

                int num_subjects;
                cout << "Enter the number of subjects: ";
                cin >> num_subjects;
                new_marks.resize(num_subjects);

                cout << "Enter marks for each subject: ";
                for (int i = 0; i < num_subjects; ++i) {
                    cout << "Subject " << (i + 1) << ": ";
                    cin >> new_marks[i];
                }

                student.set_id(new_id);
                student.set_name(new_name);
                student.add_marks(new_marks);

                cout << "Student record modified successfully." << endl;
                student.display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void generate_mark_sheet(int id) {
        bool found = false;
        for (const auto& student : students) {
            if (student.get_student_id() == id) {
                cout << "Mark Sheet for " << student.get_name() << " (ID: " << student.get_student_id() << ")\n";
                cout << "-----------------------------------\n";
                const vector<float>& marks = student.get_marks();
                for (size_t j = 0; j < marks.size(); ++j) {
                    cout << "Subject " << (j + 1) << ": " << marks[j] << "\n";
                }
                cout << "Grade: " << student.get_grade() << endl;
                cout << "-----------------------------------\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found!" << endl;
        }
    }

    void delete_student_record(int id) {
        bool found = false;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->get_student_id() == id) {
                it = students.erase(it);
                cout << "Student with ID " << id << " deleted successfully." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void change_admin_password(const string& new_password) {
        admin_password = new_password;
        cout << "Admin password changed successfully!" << endl;
    }

    string get_admin_password() const {
        return admin_password;
    }
};

vector<Student> StudentManagementSystem::students;

class MarkSheet {
private:
    Student student;
    double total_marks;
    char grade;

public:
    MarkSheet(const Student& s) : student(s) {
        generate();
    }

    void generate() {
        const vector<float>& marks = student.get_marks();
        total_marks = 0;
        for (float mark : marks) {
            total_marks += mark;
        }
        grade = student.get_grade();
    }

    void display() const {
        student.display();
        cout << "Total Marks = " << total_marks << ", Grade = " << grade << endl;
    }
};

class Admin {
private:
    string username;
    string password;

public:
    void setUsername(const string& uname) {
        username = uname;
    }

    void setPassword(const string& pass) {
        password = pass;
    }

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }
    void login(const string& uname, const string& pass) {
        if (username == uname && password == pass) {
            cout << "Login successful!" << endl;
        }
        else {
            cout << "Invalid username or password. Login failed!" << endl;
        }
    }
    void logout() {
        cout << "Logged out successfully!" << endl;
    }

    void changePassword(const string& oldPass, const string& newPass) {
        if (password == oldPass) {
            password = newPass;
            cout << "Password changed successfully!" << endl;
        }
        else {
            cout << "Incorrect old password. Password change failed!" << endl;
        }
    }
};

class FileHandler {
public:
    vector<Student> read_students_from_file(const string& filename) {
        ifstream infile(filename);
        vector<Student> students;

        if (!infile) {
            cout << "Failed to open file for reading." << endl;
            return students;
        }

        string line;
        while (getline(infile, line)) {
            istringstream iss(line);
            int id;
            string name;
            int num_subjects;

            iss >> id >> name >> num_subjects;

            vector<float> marks(num_subjects);
            for (int i = 0; i < num_subjects; ++i) {
                iss >> marks[i];
            }

            Student student;
            student.set_id(id);
            student.set_name(name);
            student.add_marks(marks);

            students.push_back(student);
        }

        infile.close();
        return students;
    }

    void write_students_to_file(const vector<Student>& students, const string& filename) {
        ofstream outfile(filename, ios::out | ios::trunc);
        if (!outfile) {
            cout << "Failed to open file for writing." << endl;
            return;
        }

        for (const auto& student : students) {
            outfile << student.get_student_id() << " " << student.get_name() << " ";
            const vector<float>& marks = student.get_marks();
            outfile << marks.size();
            for (const auto& mark : marks) {
                outfile << " " << mark;
            }
            outfile << "\n";
        }

        outfile.close();
    }
};

class SearchEngine {
public:
    vector<Student> data;
    void add_student(const Student& student) {
        data.push_back(student);
    }
    void search_by_id(int id) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].get_student_id() == id) {
                cout << "Record found: ";
                data[i].display();
                return;
            }
        }
        cout << "Record with ID " << id << " not found." << endl;
    }
    void search_by_name(const string& name) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].get_name() == name) {
                cout << "Record found: ";
                data[i].display();
                return;
            }
        }
        cout << "Record with name " << name << " not found." << endl;
    }
};

class Menu {
public:
    void display_menu() {
        cout << "1. Add Student Record" << endl;
        cout << "2. Search Student Record" << endl;
        cout << "3. Modify Student Record" << endl;
        cout << "4. Generate Mark Sheet" << endl;
        cout << "5. Delete Student Record" << endl;
        cout << "6. Change admin password" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void execute_option(StudentManagementSystem& sms) {
        int choice;
        cout << "Please select an option: ";
        cin >> choice;
        int id;
        switch (choice) {
        case 1: {
            string name;
            vector<float> marks;

            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter student name: ";
            cin >> name;

            int num_subjects;
            cout << "Enter the number of subjects: ";
            cin >> num_subjects;
            marks.resize(num_subjects);

            cout << "Enter marks for each subject: ";
            for (int i = 0; i < num_subjects; ++i) {
                cout << "Subject " << (i + 1) << ": ";
                cin >> marks[i];
            }

            Student new_student;
            new_student.set_id(id);
            new_student.set_name(name);
            new_student.add_marks(marks);
            new_student.display();
            sms.add_student_record(new_student);
            break;
        }
        case 2: {
            cout << "Enter student ID to search: ";
            cin >> id;
            sms.search_student_record(id);
            break;
        }
        case 3:
            sms.modify_student_record();
            break;
        case 4: {
            cout << "Enter student ID to generate mark sheet: ";
            cin >> id;
            sms.generate_mark_sheet(id);
            break;
        }
        case 5: {
            cout << "Enter student ID to delete record: ";
            cin >> id;
            sms.delete_student_record(id);
            break;
        }
        case 6: {
            string old_password, new_password;
            cout << "Enter old password: ";
            cin >> old_password;
            if (old_password == sms.get_admin_password()) {
                cout << "Enter new password: ";
                cin >> new_password;
                sms.change_admin_password(new_password);
            }
            else {
                cout << "Incorrect password. Password change failed!" << endl;
            }
            break;
        }
        case 7:
            cout << "Exiting the system. Goodbye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    void exit_menu() {
        cout << "Exiting the system. Goodbye!" << endl;
        exit(0);
    }
};

int main() {
    StudentManagementSystem sms;
    Menu menu;
    FileHandler fileHandler;
    string filename = "Data.txt";
    vector<Student> students = fileHandler.read_students_from_file(filename);
    sms.set_students(students);

    while (true) {
        menu.display_menu();
        menu.execute_option(sms);
        fileHandler.write_students_to_file(sms.get_students(), filename);
    }
    return 0;
}