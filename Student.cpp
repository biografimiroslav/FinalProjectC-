#include "Student.h"

Student::Student(int studentId, const std::string& studentName)
    : id(studentId), name(studentName) {
}

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
void Student::setName(const std::string& studentName) { name = studentName; }