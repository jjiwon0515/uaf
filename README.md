# uaf


#include <fcntl.h>
#include <iostream> 
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

class Human{
private:
        virtual void give_shell(){
                system("/bin/sh");
        }
protected:
        int age;
        string name;
public:
        virtual void introduce(){
                cout << "My name is " << name << endl;
                cout << "I am " << age << " years old" << endl;
        }
};

class Man: public Human{
public:
        Man(string name, int age){
                this->name = name;
                this->age = age;
        }
        virtual void introduce(){
                Human::introduce();
                cout << "I am a nice guy!" << endl;
        }
};

class Woman: public Human{
public:
        Woman(string name, int age){
                this->name = name;
                this->age = age;
        }
        virtual void introduce(){
                Human::introduce();
                cout << "I am a cute girl!" << endl;
        }
};

int main(int argc, char* argv[]){
        Human* m = new Man("Jack", 25);
        Human* w = new Woman("Jill", 21);

        size_t len;
        char* data;
        unsigned int op;
        while(1){
                cout << "1. use\n2. after\n3. free\n";
                cin >> op;

                switch(op){
                        case 1:
                                m->introduce();
                                w->introduce();
                                break;
                        case 2:
                                len = atoi(argv[1]);
                                data = new char[len];
                                read(open(argv[2], O_RDONLY), data, len);
                                cout << "your data is allocated" << endl;
                                break;
                        case 3:
                                delete m;
                                delete w;
                                break;
                        default:
                                break;
                }
        }

        return 0;
}


위의 코드를 기반으로 모르는 부분들을 공부하고 힌트가 될만한 case2 부분을 집중적으로 봤다.
class 부분을 이전에 구조체만 공부했는데 처음 보는 문법들을 새로 공부할 수 있는 시간이었다.
1. using namespace std --> std에 있는 cout, endl들을 사용할 수 있다
  1-1) cout << "문자열" : 문자열들을 출력하는 함수이다 . (printf와 같은 역할)
  1-2) "문자열" << endl : 문자열 뒤에 사용하여 다음 줄에 출력을 이어서 하고 싶을 때 사용한다 (줄바꿔서 출력시키는 역할)

2. class 클래스명 {} : 하나의 프로그램을 묶어서 표현 (가독성 좋아짐)
  2-1) virtual void introduce() : 부모 클래스에서 사용하여 함수 생성할 때 자식 클래그에서 해당 함수를 재사용할 수 있다.
  2-2) this -> name = name : 여기서 this는 지금 함수가 포함된 클래스를 뜻한다. 다른 클래스의 함수들의 변수들과 혼동하지 않게 하기위해서 사용하는 것 같다.
  
3. atoi 함수 : 이전에도 계속 봤었는데 다른 문제 풀고 다시 보면 까먹는 함수..... 문자열을 정수로 바꿔주는 함수이다. 
  EX) atoi("1234") = 1234 자료형을 바꿔준다고 생각하면 될듯하다.
  
내가 생각한 해결방법 : 
1) case 2에서 인자값을 argv[1] = 22 (ls -al 명령어를 실행했을 때 flag가 22byte 값을 가진다), argv[2] = 파일 이름을 넣어야하기 떄문에(flag 값을 넣었다)
   하지만 이 방법으로는 flag값을 확인할 수 없다. read함수에서 data에 해당 내용들을 할당하지만 이것을 출력시킬 수 없기 때문이다.
 
2) Mommy, what is Use After Free bug? : 해당 문제에 이런게 써있어서 uaf를 구글링 해봤더니 관련 취약점들을 공부할 수 있었다.
   uaf(use after free) : heap 구조와 관련된 취약점이다. 간단하게 이해한 것을 쓰면 같은 메모리 공간을 2개의 포인터가 공유한다. 그래서 하나의 포인터에서 메모리 value 값을 변경    하면 다른 하나의 포인터에 해당하는 value 값도 변경된다.
   이것들을 기반으로 문제를 풀기위해서 필요한 것 : 목표로 하는 메모리 주소, 입력값에서 목표까지 몇바이트 필요한지
