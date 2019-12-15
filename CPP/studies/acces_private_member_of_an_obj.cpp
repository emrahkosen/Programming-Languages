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
            cout<<st<<endl;//st and grade has same address

            int *i = (int *)st;
//            *i = 100;
            cout<<*i<<endl;
            cout<<*(int *)st<<endl;

            cout<<&st->grade<<endl;//12
            cout<< st->grade<<endl; //can access private variable of other student object
            st->grade = 19; //chances the private variable of an obj of that class
            cout<< st->grade<<endl;//19

        }
};

int main()
{

  Student s1(12);
  Student s2(15);

  s2.getOtherStudentGrade(&s1);
}
