#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Course {
public:
    string courseName;
    string courseCode;
    int duration; // Duration in weeks

    Course(string name, string code, int dur) : courseName(name), courseCode(code), duration(dur) {}
};

class Student {
public:
    string name;
    string studentID;
    vector<Course> enrolledCourses;

    Student(string n, string id) : name(n), studentID(id) {}

    void enrollCourse(Course course) {
        enrolledCourses.push_back(course);
        cout << "Enrolled in course: " << course.courseName << endl;
    }

    void generateCertificate(Course course) {
        ofstream certFile;
        string fileName = studentID + "_" + course.courseCode + "_certificate.txt";
        certFile.open(fileName);
        certFile << "Certificate of Completion\n";
        certFile << "This certifies that " << name << " has successfully completed the course " << course.courseName << ".\n";
        certFile << "Course Code: " << course.courseCode << "\n";
        certFile << "Duration: " << course.duration << " weeks\n";
        certFile.close();
        cout << "Certificate generated: " << fileName << endl;
    }
};

void displayCourses(const vector<Course>& courses) {
    cout << "Available Courses:\n";
    for (const auto& course : courses) {
        cout << "Course Name: " << course.courseName << ", Course Code: " << course.courseCode << ", Duration: " << course.duration << " weeks\n";
    }
}

int main() {
    vector<Course> courses = {
        Course("C++ Programming", "CS101", 6),
        Course("Data Structures", "CS102", 8),
        Course("Algorithms", "CS103", 10)
    };

    vector<Student> students;

    string studentName, studentID;
    cout << "Enter student name: ";
    getline(cin, studentName);
    cout << "Enter student ID: ";
    getline(cin, studentID);

    Student newStudent(studentName, studentID);
    students.push_back(newStudent);

    int choice;
    while (true) {
        cout << "\n1. Display Courses\n";
        cout << "2. Enroll in Course\n";
        cout << "3. Generate Certificate\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            displayCourses(courses);
        } else if (choice == 2) {
            string courseCode;
            cout << "Enter course code to enroll: ";
            getline(cin, courseCode);

            bool courseFound = false;
            for (const auto& course : courses) {
                if (course.courseCode == courseCode) {
                    newStudent.enrollCourse(course);
                    courseFound = true;
                    break;
                }
            }
            if (!courseFound) {
                cout << "Course not found!\n";
            }
        } else if (choice == 3) {
            string courseCode;
            cout << "Enter course code to generate certificate: ";
            getline(cin, courseCode);

            bool courseFound = false;
            for (const auto& course : newStudent.enrolledCourses) {
                if (course.courseCode == courseCode) {
                    newStudent.generateCertificate(course);
                    courseFound = true;
                    break;
                }
            }
            if (!courseFound) {
                cout << "Course not found or not enrolled!\n";
            }
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}