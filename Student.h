#pragma once
#include <string>
#include <vector>

class Student
{
private:
    int id;
    std::string name;

public:
    Student(int studentId, const std::string& studentName);

    int getId() const;
    std::string getName() const;
    void setName(const std::string& studentName);
};