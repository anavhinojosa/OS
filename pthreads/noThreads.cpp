#include <iostream>
#include <fstream>

using namespace std;

struct Student {
    int id;
    int passed;
};

Student students[100000000];
int studentCount = 0;

double calculate() {
    double score = 0.0;
    int passedCount = 0;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].passed == 1) {
            passedCount++;
        }
    }
    score = (passedCount / (double)studentCount) * 100;
    return score;
}

int main() {
    ifstream infile("students.txt");
    if (!infile.is_open()) {
        cout << "Failed to open the file.\n";
        return 1;
    }

    while (infile >> students[studentCount].id >> students[studentCount].passed) {
        studentCount++;
    }
    infile.close();

    double percentage = calculate();
    cout << "No threads: \nPercentage of students who passed: " << percentage << "%\n";

    return 0;
}
