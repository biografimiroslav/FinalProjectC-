#pragma once
#include <string>

class Subject
{
private:
    std::string name;
    int lessonsPerWeek;

public:
    Subject(const std::string& subjectName, int lessons);

    std::string getName() const;
    void setName(const std::string& subjectName);

    int getLessonsPerWeek() const;
    void setLessonsPerWeek(int lessons);
};