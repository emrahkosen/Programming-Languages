#include <iostream>
#include <string>

using namespace std;

class Student
{
    private:
        int grade;
    public:
        Student(int grade)
        {
            this->grade = grade;
        }

        void getOtherStudentGrade(Student *st)
        {
            cout<<st->grade<<endl;//st and grade has same address
        }
};

int main()
{

  Student s1(12);
  Student s2(15);

  s2.getOtherStudentGrade(&s1);//it can do this and return 12
}
