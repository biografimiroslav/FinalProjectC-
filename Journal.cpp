#include "Journal.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Journal::Journal() : nextStudentId(1) {}

GradeManager* Journal::findOrCreateGradeRecord(int studentId, const std::string& subjectName)
{
    for (auto& g : grades)
    {
        if (g.getStudentId() == studentId && g.getSubjectName() == subjectName)
        {
            return &g;
        }
    }
    grades.push_back(GradeManager(studentId, subjectName));
    return &grades.back();
}

void Journal::addStudent(const std::string& name)
{
    students.push_back(Student(nextStudentId++, name));
}

void Journal::editStudent(int id, const std::string& newName)
{
    for (auto& s : students)
    {
        if (s.getId() == id)
        {
            s.setName(newName);
            return;
        }
    }
}

void Journal::removeStudent(int id)
{
    students.erase(std::remove_if(students.begin(), students.end(),
        [id](const Student& s) { return s.getId() == id; }), students.end());

    grades.erase(std::remove_if(grades.begin(), grades.end(),
        [id](const GradeManager& g) { return g.getStudentId() == id; }), grades.end());
}

void Journal::addSubject(const std::string& name, int lessons)
{
    subjects.push_back(Subject(name, lessons));
}

void Journal::editSubject(const std::string& oldName, const std::string& newName, int newLessons)
{
    for (auto& sub : subjects)
    {
        if (sub.getName() == oldName)
        {
            sub.setName(newName);
            sub.setLessonsPerWeek(newLessons);
            break;
        }
    }

    if (oldName != newName)
    {
        std::vector<GradeManager> updatedGrades;
        for (auto& g : grades)
        {
            if (g.getSubjectName() == oldName)
            {
                GradeManager newG(g.getStudentId(), newName);
                for (int val : g.getCurrentGrades()) newG.addCurrentGrade(val);
                for (int val : g.getExamGrades()) newG.addExamGrade(val);
                updatedGrades.push_back(newG);
            }
            else
            {
                updatedGrades.push_back(g);
            }
        }
        grades = updatedGrades;
    }
}

void Journal::removeSubject(const std::string& name)
{
    subjects.erase(std::remove_if(subjects.begin(), subjects.end(),
        [&name](const Subject& sub) { return sub.getName() == name; }), subjects.end());

    grades.erase(std::remove_if(grades.begin(), grades.end(),
        [&name](const GradeManager& g) { return g.getSubjectName() == name; }), grades.end());
}

void Journal::addGrade(int studentId, const std::string& subjectName, int grade, bool isExam)
{
    GradeManager* record = findOrCreateGradeRecord(studentId, subjectName);
    if (isExam)
    {
        record->addExamGrade(grade);
    }
    else
    {
        record->addCurrentGrade(grade);
    }
}

void Journal::editGrade(int studentId, const std::string& subjectName, size_t index, int newGrade, bool isExam)
{
    for (auto& g : grades)
    {
        if (g.getStudentId() == studentId && g.getSubjectName() == subjectName)
        {
            if (isExam) g.editExamGrade(index, newGrade);
            else g.editCurrentGrade(index, newGrade);
            return;
        }
    }
}

void Journal::showSubjectAverage(const std::string& subjectName) const
{
    std::cout << "Average Grades for Subject: " << subjectName << std::endl;
    for (const auto& s : students)
    {
        double sum = 0.0;
        bool found = false;
        for (const auto& g : grades)
        {
            if (g.getStudentId() == s.getId() && g.getSubjectName() == subjectName)
            {
                sum = g.calculateAverage();
                found = true;
                break;
            }
        }
        std::cout << s.getName() << " (ID: " << s.getId() << ") -> Average: " << (found ? sum : 0.0) << std::endl;
    }
}

void Journal::saveStudentsToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << nextStudentId << "\n";
    for (const auto& s : students)
    {
        file << s.getId() << "," << s.getName() << "\n";
    }
}

void Journal::loadStudentsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    students.clear();
    std::string line;
    if (std::getline(file, line))
    {
        std::stringstream ss(line);
        ss >> nextStudentId;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, name;
        if (std::getline(ss, idStr, ',') && std::getline(ss, name))
        {
            students.push_back(Student(std::stoi(idStr), name));
        }
    }
}

void Journal::saveGradesToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& g : grades)
    {
        file << g.getStudentId() << ";" << g.getSubjectName() << ";";
        for (size_t i = 0; i < g.getCurrentGrades().size(); ++i)
        {
            file << g.getCurrentGrades()[i] << (i == g.getCurrentGrades().size() - 1 ? "" : ",");
        }
        file << ";";
        for (size_t i = 0; i < g.getExamGrades().size(); ++i)
        {
            file << g.getExamGrades()[i] << (i == g.getExamGrades().size() - 1 ? "" : ",");
        }
        file << "\n";
    }
}

void Journal::loadGradesFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    grades.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string sIdStr, subName, currentStr, examStr;

        std::getline(ss, sIdStr, ';');
        std::getline(ss, subName, ';');
        std::getline(ss, currentStr, ';');
        std::getline(ss, examStr, ';');

        int sId = std::stoi(sIdStr);
        GradeManager record(sId, subName);

        if (!currentStr.empty())
        {
            std::stringstream currSS(currentStr);
            std::string token;
            while (std::getline(currSS, token, ','))
            {
                record.addCurrentGrade(std::stoi(token));
            }
        }

        if (!examStr.empty())
        {
            std::stringstream examSS(examStr);
            std::string token;
            while (std::getline(examSS, token, ','))
            {
                record.addExamGrade(std::stoi(token));
            }
        }
        grades.push_back(record);
    }
}

void Journal::displayJournal() const
{
    std::cout << "\n========== CLASS JOURNAL ==========" << std::endl;
    for (const auto& s : students)
    {
        std::cout << "Student: " << s.getName() << " [ID: " << s.getId() << "]" << std::endl;
        for (const auto& sub : subjects)
        {
            std::cout << "  Subject: " << sub.getName() << " (" << sub.getLessonsPerWeek() << " lessons/week)" << std::endl;
            bool found = false;
            for (const auto& g : grades)
            {
                if (g.getStudentId() == s.getId() && g.getSubjectName() == sub.getName())
                {
                    std::cout << "    Current Grades: ";
                    for (int v : g.getCurrentGrades()) std::cout << v << " ";
                    std::cout << "\n    Exam Grades:    ";
                    for (int v : g.getExamGrades()) std::cout << v << " ";
                    std::cout << "\n    Average Total:  " << g.calculateAverage() << std::endl;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                std::cout << "    No recorded grades yet." << std::endl;
            }
        }
        std::cout << "-----------------------------------" << std::endl;
    }
}