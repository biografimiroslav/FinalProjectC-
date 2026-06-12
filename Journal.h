#pragma once
#include "Student.h"
#include "Subject.h"
#include "GradeManager.h"
#include <vector>

class Journal
{
private:
    std::vector<Student> students;
    std::vector<Subject> subjects;
    std::vector<GradeManager> grades;
    int nextStudentId;

    GradeManager* findOrCreateGradeRecord(int studentId, const std::string& subjectName);

public:
    Journal();

    void addStudent(const std::string& name);
    void editStudent(int id, const std::string& newName);
    void removeStudent(int id);

    void addSubject(const std::string& name, int lessons);
    void editSubject(const std::string& oldName, const std::string& newName, int newLessons);
    void removeSubject(const std::string& name);

    void addGrade(int studentId, const std::string& subjectName, int grade, bool isExam);
    void editGrade(int studentId, const std::string& subjectName, size_t index, int newGrade, bool isExam);

    void showSubjectAverage(const std::string& subjectName) const;

    void saveStudentsToFile(const std::string& filename) const;
    void loadStudentsFromFile(const std::string& filename);

    void saveGradesToFile(const std::string& filename) const;
    void loadGradesFromFile(const std::string& filename);

    void displayJournal() const;
};