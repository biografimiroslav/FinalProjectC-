#include "Subject.h"

Subject::Subject(const std::string& subjectName, int lessons)
    : name(subjectName), lessonsPerWeek(lessons) {
}

std::string Subject::getName() const { return name; }
void Subject::setName(const std::string& subjectName) { name = subjectName; }

int Subject::getLessonsPerWeek() const { return lessonsPerWeek; }
void Subject::setLessonsPerWeek(int lessons) { lessonsPerWeek = lessons; }