#include <iostream>

#using namespace를 사용하여 std에 있는 cout,endl 함수들을 사용한다.
using namespace std;

# class 클래스명{} : 클래스를 생성한다. 해당 클래스안에 name, age, hobby라는 멤버변수를 private 접근지정자를 사용하여 선언했다. 
# 또한 char *을 사용하여 name와 hobby를 포인터 변수로 선언했다.
# void를 사용하여 반환값이 없다는 것을 알 수 있다. 
class student {
  private:
	    char * name;
	    int age;
	    char * hobby;
  public:
	    void ShowInfo();
	    # _name, _age, _hobby를 포인터 변수로 선언하고 매개변수로 받는다.
	    void SetInfo(char * _name, int _age, char * _hobby);
	    void Study();
	    void Sleep();
};


# 위 클래스에서 선언한 Showinfo() 함수이다.
# :: 모양은 범위 연산자이다. 클래스 선언 부분의 함수를 클래스 밖에서 정의할 때 사용된다. 이 방식이 클래스안에서 정의하는 것보다 관리하는 것이 편하다. 
# cout는 printf와 같은 출력하는 역할을 한다.
# endl은 cout함수와 자주 사용되며 출력하고 개행을 할 때 사용된다.
void student::ShowInfo()
{
	  cout << "이름: " << name << ", 나이: " << age << ", 취미: " << hobby << endl;
}



# 위의 함수와 똑같이 Setinfo는 student 클래스 소속이기 때문에 ::(범위 지정 연산자)를 통하여 코드를 분리하여 만들 수 있었다. 
# student 클래스 다른 함수들과는 다르게 매개변수를 받는 유일한 함수이다. {Setinfo(char * _name, int _age, char * _hobby)}
# 포인터 변수에 문자열을 저장할 수 있는 이유가 담긴 블로그다. 문자열 : 해당 문자열의 첫 문자의 "주소"라는 전제가 있다. 
# 그러므로 다른 정수형 변수 (예시/ num = 10 , p = &num)처럼 &(주소값을 가르킨다)을 붙일 필요가 없다. 
https://m.blog.naver.com/qkrghdud0/220856609693
# 포인터 변수 사용할 때 조심할 점 : 처음 값을 저장할 때만 &기호를 사용하거나 다른 방법들로 주소값을 저장한다. 
# 포인터에서 *기호와 &가 만나면 상쇄된다. --> char * name = "장지원" (문자열은 주소값을 나타내고 있다고했다. &jiwon으로 생략가능) 이럴 때 name의 *와 jiwon의 &가 상쇄되어 char name = jiwon처럼 생각한다.

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


# 클래스명 객체명 : 객체 생성 (stack)
# 클래스명 *객체명 = new 객체명 : 객체 생성 (heap)
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

