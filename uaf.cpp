#include <fcntl.h>
#include <iostream> 
#include <cstring>
#include <cstdlib>
#include <unistd.h>


# std, cout, endl 함수들을 사용할 수 있게 한다. 또한 namespace는 어떤 변수나 함수의 소속을 알려주는 기능을 한다.
# 
using namespace std;

# c++ 구조체와 클래스


# Human이라는 클래스 생성
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


# Man이라는 클래스 생성
# Human 클래스 상속받음 (class Man : public Human) 
# 여기서는 Human을 부모 클래스, Man을 자식 클래스라고 칭한다
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


# Woman이라는 클래스 생성
# Human 클래스를 상속받음
# 여기서는 Human을 부모 클래스, Woman을 자식 클래스라고 칭한다.
# this 포인터를 통해 매개 변수 name와 멤버 변수를 name을 구분 짓는다 (다른 방법: 매개 변수와 멤버 변수의 이름을 다르게 해도 해결된다.) 
# 범위 지정 연산자( "::" ) :  여러 형태를 사용될 수 있다 (:: 식별자, 클래스이름 :: 식별자, 네임스페이스 :: 식별자, 열거체 :: 식별자 )
        # 여기서는 Human :: introduce() -> Human에 있는 introduce 함수를 사용한다.
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


# main 함수
# 객체 배열 : 클래스명 객체명[크기];
# 객체 포인터 배열 : 클래스명 * 객체명[크기];
# new와 delete를 이용한 동적 메모리 할당
        # new 생성자 : 주솟값을 return하기 때문에 포인터 변수에 저장해야한다.
        # delete : 동적 할당을 취소, 운영체제에 반환
# this 포인터를 이용한 매개 변수와 멤버 변수의 구분
# 클래스 멤버에 대한 포인터 : "->" (화살표 연산자) : 주소에 있는 값을 가져온다.  (.을 사용해도 되지만 현재 코드에서는 m,w가 포인터 멤버이기때문에 화살표 연산자 사용)

int main(int argc, char* argv[]){
        Human* m = new Man("Jack", 25); # 객체 포인터 배열 : 클래스명 * 객체명, new를 통한 동적 할당(주소값 반환)
        Human* w = new Woman("Jill", 21);
        
        # m과 w 포인터 변수에 Man과 Woman에 매개 변수에 값 넣고 멤버 변수에 값 저장된 주소값을 포인터에 저장
        
        size_t len;
        char* data;
        
        # data 포인터 변수 선언 
        
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


# https://jhnyang.tistory.com/334
# new 생성자 : 주소를 return 하기 때문에 new의 값을 저장하는 변수는 포인터 변수여야한다.
# 객체명과 멤버 변수의 차이 : 
        # 객체명 : 하나의 틀인 클래스에서 들어갈 재료/ 예시) 붕어빵 틀에 들어갈 재료
        # 멤버 변수 : 하나의 틀을 구성할 요소/ 예시) 붕어빵 틀 



