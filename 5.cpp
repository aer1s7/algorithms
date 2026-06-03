#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Student {
    int id;
    int grade;
};

class Archive {
    private:
        unordered_map<int, int> grades;
        int grade_counts[4] = {0};

    public:
        Archive(){
            for (int i = 0; i < 4; i++){
                grade_counts[i] = 0;
            }
        }

        void addStudent(int id, int grade){
            if (grade < 2 || grade > 5){
                cout << "Неверная оценка." << endl;
                return;
            }
            grades[id] = grade;
            grade_counts[grade-2]++;
        }

        int getGrade(int id) {
            if (grades.find(id) == grades.end()){
                cout << "Студент не найден." << endl;
                return -1;
            }
            return grades[id];
        }

        int getGradeCount(int grade){
            if (grade < 2 || grade > 5){
                cout << "Неверная оценка." << endl;
                return -1;
            }
            return grade_counts[grade-2];
        }

        void print(){
            for (const auto& student : grades){
                cout << "Student ID: " << student.first << ", оценка: " << student.second << endl; 
            }
        }
};

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Archive archive;
    vector <Student> students = {{1,5}, {5,3}, {2, 2}, {8, 4}, {3, 5}, {4, 4}, {6, 2}, {7,4}};
    cout << "Исходные оценки: " << endl;
    for (Student student : students){
        cout << "Student ID: " << student.id << ", оценка: " << student.grade << endl;
        archive.addStudent(student.id, student.grade);
    }

    int searchId = 8;
    cout << "Поиск оценки студента по ID = " << searchId << ": " << archive.getGrade(searchId) << endl;
    int searchGrade = 4;
    cout << "Количество студентов с оценкой " << searchGrade << ": " << archive.getGradeCount(searchGrade) << endl;
}