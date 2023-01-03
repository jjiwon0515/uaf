#include <iostream>

using namespace std;

class student {
  private:
	    char * name;
	    int age;
	    char * hobby;
  public:
	    void ShowInfo();
	    void SetInfo(char * _name, int _age, char * _hobby);
	    void Study();
	    void Sleep();
};



void student::ShowInfo()
{
	  cout << "이름: " << name << ", 나이: " << age << ", 취미: " << hobby << endl;
}




void student::SetInfo(char * _name, int _age, char * _hobby)
{
	name = _name;
	age = _age;
	hobby = _hobby;
}

void student::Study()
{
	cout << "공부!" << endl;
}

void student::Sleep()
{
	cout << "잠!" << endl;
}

int main()
{
	student stu;

	stu.SetInfo("김철수", 16, "컴퓨터 게임");
	stu.ShowInfo();

	while(true) {
		stu.Study();
		stu.Sleep();
	}

	return 0;
}


결과 : 
