#pragma once
#include <string>
#include <vector>

class GradeManager
{
private:
    int studentId;
    std::string subjectName;
    std::vector<int> currentGrades;
    std::vector<int> examGrades;

public:
    GradeManager(int sId, const std::string& subName);

    int getStudentId() const;
    std::string getSubjectName() const;

    const std::vector<int>& getCurrentGrades() const;
    const std::vector<int>& getExamGrades() const;

    void addCurrentGrade(int grade);
    void addExamGrade(int grade);

    bool editCurrentGrade(size_t index, int newGrade);
    bool editExamGrade(size_t index, int newGrade);

    void clearGrades();
    double calculateAverage() const;
};