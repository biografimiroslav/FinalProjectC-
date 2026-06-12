#include "Journal.h"
#include <iostream>

int main()
{
    Journal schoolJournal;

    schoolJournal.addStudent("John Doe");
    schoolJournal.addStudent("Alice Smith");
    schoolJournal.addStudent("Bob Johnson");

    schoolJournal.addSubject("Mathematics", 4);
    schoolJournal.addSubject("History", 2);

    schoolJournal.addGrade(1, "Mathematics", 10, false);
    schoolJournal.addGrade(1, "Mathematics", 11, false);
    schoolJournal.addGrade(1, "Mathematics", 12, true);

    schoolJournal.addGrade(2, "Mathematics", 8, false);
    schoolJournal.addGrade(2, "Mathematics", 9, true);

    schoolJournal.addGrade(1, "History", 9, false);
    schoolJournal.addGrade(2, "History", 12, false);

    schoolJournal.displayJournal();

    schoolJournal.saveStudentsToFile("students.txt");
    schoolJournal.saveGradesToFile("grades.txt");

    schoolJournal.editStudent(3, "Robert Johnson");
    schoolJournal.editSubject("History", "World History", 3);
    schoolJournal.editGrade(1, "Mathematics", 0, 12, false);
    schoolJournal.removeStudent(2);

    std::cout << "\n=== Journal After Runtime Modification ===" << std::endl;
    schoolJournal.displayJournal();

    std::cout << "\n=== Reloading From Saved State Files ===" << std::endl;
    Journal restoredJournal;
    restoredJournal.addSubject("Mathematics", 4);
    restoredJournal.loadStudentsFromFile("students.txt");
    restoredJournal.loadGradesFromFile("grades.txt");
    restoredJournal.displayJournal();

    std::cout << "\n=== Calculations Overview ===" << std::endl;
    restoredJournal.showSubjectAverage("Mathematics");

    return 0;
}