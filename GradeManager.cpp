#include "GradeManager.h"
#include <numeric>

GradeManager::GradeManager(int sId, const std::string& subName)
    : studentId(sId), subjectName(subName) {
}

int GradeManager::getStudentId() const { return studentId; }
std::string GradeManager::getSubjectName() const { return subjectName; }

const std::vector<int>& GradeManager::getCurrentGrades() const { return currentGrades; }
const std::vector<int>& GradeManager::getExamGrades() const { return examGrades; }

void GradeManager::addCurrentGrade(int grade) { currentGrades.push_back(grade); }
void GradeManager::addExamGrade(int grade) { examGrades.push_back(grade); }

bool GradeManager::editCurrentGrade(size_t index, int newGrade)
{
    if (index < currentGrades.size())
    {
        currentGrades[index] = newGrade;
        return true;
    }
    return false;
}

bool GradeManager::editExamGrade(size_t index, int newGrade)
{
    if (index < examGrades.size())
    {
        examGrades[index] = newGrade;
        return true;
    }
    return false;
}

void GradeManager::clearGrades()
{
    currentGrades.clear();
    examGrades.clear();
}

double GradeManager::calculateAverage() const
{
    double total = 0;
    int count = 0;

    for (int g : currentGrades)
    {
        total += g;
        count++;
    }
    for (int g : examGrades)
    {
        total += g * 2.0;
        count += 2;
    }

    return (count == 0) ? 0.0 : total / count;
}