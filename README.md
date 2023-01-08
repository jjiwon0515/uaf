# uaf

```c
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


# ->, . 연산자들은 구조체에 접근한다는 의미로 사용된다. 구조체 변수나 함수같은 원소들에 접근할 때 사용된다. 
# new를 사용하여 동적할당을 한다. new는 주소값을 반환하는 생산자이므로 m ,w 포인터 변수와 함께 사용된다. 
int main(int argc, char* argv[]){
        Human* m = new Man("Jack", 25);        // m = Man("Jack", 25);
        Human* w = new Woman("Jill", 21);      // w = Woman("Jill", 21);

        size_t len;
        char* data;
        unsigned int op;
        while(1){
                cout << "1. use\n2. after\n3. free\n";
                cin >> op;

                switch(op){
                        case 1:
                                m->introduce();                 m = Man("Jack" , 25); -> introduce()
                                w->introduce();                 w = Woman("Jill" , 21); -> introduce()
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
```

위의 코드를 기반으로 모르는 부분들을 공부하고 힌트가 될만한 case2 부분을 집중적으로 봤다.<br>
class 부분을 이전에 구조체만 공부했는데 처음 보는 문법들을 새로 공부할 수 있는 시간이었다.<br>
1. using namespace std --> std에 있는 cout, endl들을 사용할 수 있다<br>
  1-1) cout << "문자열" : 문자열들을 출력하는 함수이다 . (printf와 같은 역할)<br>
  1-2) "문자열" << endl : 문자열 뒤에 사용하여 다음 줄에 출력을 이어서 하고 싶을 때 사용한다 (줄바꿔서 출력시키는 역할)<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;2. class 클래스명 {} : 하나의 프로그램을 묶어서 표현 (가독성 좋아짐)<br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2-1) virtual void introduce() : 부모 클래스에서 사용하여 함수 생성할 때 자식 클래그에서 해당 함수를 재사용할 수 있다.<br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2-2) this -> name = name : 여기서 this는 지금 함수가 포함된 클래스를 뜻한다. <br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;다른 클래스의 함수들의 변수들과 혼동하지 않게 하기 위해서 사용하는 것 같다.<br>
  <br>
&nbsp;&nbsp;&nbsp;&nbsp;3. atoi 함수 : 이전에도 계속 봤었는데 다른 문제 풀고 다시 보면 까먹는 함수..... 문자열을 정수로 바꿔주는 함수이다. <br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;EX) atoi("1234") = 1234 자료형을 바꿔준다고 생각하면 될듯하다.<br>
  <br><br><br><br>
내가 생각한 해결방법 : <br>
1) case 2에서 인자값을 argv[1] = 22 (ls -al 명령어를 실행했을 때 flag가 22byte 값을 가진다), argv[2] = 파일 이름을 넣어야하기 떄문에(flag 값을 넣었다)<br>
   하지만 이 방법으로는 flag값을 확인할 수 없다. read함수에서 data에 해당 내용들을 할당하지만 이것을 출력시킬 수 없기 때문이다.<br>
 <br>
2) Mommy, what is Use After Free bug? : 해당 문제에 이런게 써있어서 uaf를 구글링 해봤더니 관련 취약점들을 공부할 수 있었다.<br>
   uaf(use after free) : heap 구조와 관련된 취약점이다. 간단하게 이해한 것을 쓰면 같은 메모리 공간을 2개의 포인터가 공유한다. <br>
   그래서 하나의 포인터에서 메모리 value 값을 변경    하면 다른 하나의 포인터에 해당하는 value 값도 변경된다.<br><br>
   이것들을 기반으로 문제를 풀기위해서 필요한 것 : 목표로 하는 메모리 주소, 입력값에서 목표까지 몇바이트 필요한지 -> 이것들로 입력값으로 목표 주소까지 byte를 채운 후 <br>
   <br>목표주소를 넣어주고 다음 실행에 목실행하면 목표 주소로 바로 갈 수 있다. (스택에서 call back 즉 ret 부분을 만나는 부분에 목표 주소를 넣으면 된다. bof문제와 유사)<br>
   
   
   ```asm
   0x0000000000400fad <+233>:   call   0x400dd0 <_ZNSirsERj@plt>
   0x0000000000400fb2 <+238>:   mov    eax,DWORD PTR [rbp-0x18]
   0x0000000000400fb5 <+241>:   cmp    eax,0x2
   0x0000000000400fb8 <+244>:   je     0x401000 <main+316>
   0x0000000000400fba <+246>:   cmp    eax,0x3
   0x0000000000400fbd <+249>:   je     0x401076 <main+434>
   0x0000000000400fc3 <+255>:   cmp    eax,0x1
   0x0000000000400fc6 <+258>:   je     0x400fcd <main+265>

   ```
   해당 부분은 switch 함수 부분인 것을 확인할 수 있었다(함수마다 breakpoint를 잡고 실행)<br>
   지금 가장 먼저 집중해야하는 곳은 op가 2일 때이다.<br>
   아래 코드가 해당 부분이다.<br>
   
   ```asm
   0x0000000000401000 <+316>:   mov    rax,QWORD PTR [rbp-0x60]
   0x0000000000401004 <+320>:   add    rax,0x8
   0x0000000000401008 <+324>:   mov    rax,QWORD PTR [rax]
   0x000000000040100b <+327>:   mov    rdi,rax
   0x000000000040100e <+330>:   call   0x400d20 <atoi@plt>
   0x0000000000401013 <+335>:   cdqe   
   0x0000000000401015 <+337>:   mov    QWORD PTR [rbp-0x28],rax
   0x0000000000401019 <+341>:   mov    rax,QWORD PTR [rbp-0x28]
   0x000000000040101d <+345>:   mov    rdi,rax
   0x0000000000401020 <+348>:   call   0x400c70 <_Znam@plt>
   0x0000000000401025 <+353>:   mov    QWORD PTR [rbp-0x20],rax
   0x0000000000401029 <+357>:   mov    rax,QWORD PTR [rbp-0x60]
   0x000000000040102d <+361>:   add    rax,0x10
   0x0000000000401031 <+365>:   mov    rax,QWORD PTR [rax]
   0x0000000000401034 <+368>:   mov    esi,0x0
   0x0000000000401039 <+373>:   mov    rdi,rax
   0x000000000040103c <+376>:   mov    eax,0x0                         
   0x0000000000401041 <+381>:   call   0x400dc0 <open@plt>
   0x0000000000401046 <+386>:   mov    rdx,QWORD PTR [rbp-0x28]
   0x000000000040104a <+390>:   mov    rcx,QWORD PTR [rbp-0x20]
   0x000000000040104e <+394>:   mov    rsi,rcx
   0x0000000000401051 <+397>:   mov    edi,eax
   0x0000000000401053 <+399>:   call   0x400ca0 <read@plt>
   0x0000000000401058 <+404>:   mov    esi,0x401513
   0x000000000040105d <+409>:   mov    edi,0x602260
   0x0000000000401062 <+414>:   call   0x400cf0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>

   
   
```
다시 생각해보면 우선 메모리가 할당되는 부분을 use를 통해서 함수 주소를 찾고, free로 메모리 할당을 취소한다.<br>
마지막으로 취소한 메모리에 입력값을 넣어서 heap overflow를 실행한다.<br>
   
   
 ```asm
   0x0000000000400fcd <+265>:   mov    rax,QWORD PTR [rbp-0x38]
   0x0000000000400fd1 <+269>:   mov    rax,QWORD PTR [rax]
   0x0000000000400fd4 <+272>:   add    rax,0x8
   0x0000000000400fd8 <+276>:   mov    rdx,QWORD PTR [rax]
   0x0000000000400fdb <+279>:   mov    rax,QWORD PTR [rbp-0x38]
   0x0000000000400fdf <+283>:   mov    rdi,rax
   0x0000000000400fe2 <+286>:   call   rdx                                              호출하는 함수는 m -> introduce();                       
   0x0000000000400fe4 <+288>:   mov    rax,QWORD PTR [rbp-0x30]
   0x0000000000400fe8 <+292>:   mov    rax,QWORD PTR [rax]
=> 0x0000000000400feb <+295>:   add    rax,0x8
   0x0000000000400fef <+299>:   mov    rdx,QWORD PTR [rax]
   0x0000000000400ff2 <+302>:   mov    rax,QWORD PTR [rbp-0x30]
   0x0000000000400ff6 <+306>:   mov    rdi,rax
   0x0000000000400ff9 <+309>:   call   rdx                                               w -> introduce();로 추론할 수 있었다.                      

  
     
       
  
  
  
  ```
  해당 부분을 정리했다. 이것들을 바탕으로 overflow를 하려면 몇 byte가 필요한지 알아낼 수 있다.<br>
  2번째로 해당 함수에서 ret에 들어갈 우리가 목적지로 하는 메모리 주소가 필요하다. <br>
  이것까지 다 구한다면 답을 구하기 위한 포멧으로는 ./uaf (argv[1]=overflow를 발생시키기 위해 필요한 byte 수) (**argv[2]=목적지 메모리 주소(/bin/sh) + cat flag)<br> 
  1번을 눌렀을 때 할당되는 메모리 양만큼 byte 채우고 마지막에 give_shell함수 주소 넣기<br>


  ----------------------------------------------------------------------------2일차--------------------------------------------------------------------------
  gdb로 레지스터랑 목적지 메모리 주소를 찾아보고 있는데 너무 어렵다..(찾지 못했음) <br>
  그러다가 gdb를 사용하던 중 /bin/sh이 실행되어서 cat flag를 입력했는데 권한이 안된다고 나왔다. 바로 이전 문제에 풀었던 증상과 똑같다. 아무래도 gdb에서 접근하는 것은 <br>
  uaf파일을 실행해서 접근하는 것과 다르게 권한 상승이 안되나보다.<br>
```asm 
0x000000000040118b in Human::give_shell() ()
(gdb) 
$ 
 
 ```
 해당 메모리를 실행하니까 /bin/sh가 실행되는 것을 알 수 있었다. 하지만 flag를 열어 볼 수 없음. 이것을 기반으로 문제를 풀려고 파일을 생성하는데 전부 권한이 없단다..<br>
 vi, touch 명령어로 해도 vi편집기에서 저장이 되지 않고 마무리가 되는 모습만 계속 봤다. 그래서 구글링으로 <리눅스 파일 생성 -touch -vi -권한> 이런식으로 검색하니까 <br>
 리디렉션(>) 기호를 이용하거나 echo를 통해서 파일 내용을 파일 안에 넣으면서 동시에 파일을 만들 수 있는 방법이 있다고 한다. 그래서 그 방법을 사용했는데.............<br>
 만들어지지 않는다!; 내일 다시 방법을 찾아봐야겠다. 답지를 참고 참아서 혼자 힘으로 꼭 풀어봐야겠다.<br>
-----------------------------------------------------------------------------3일차-------------------------------------------------------------------
해당 환경에서 파일이 만들어지지 않는다. 그래서 파이썬 pwn 모듈로 파일을 생성해서 문제를 해결하려고 했는데, 방법을 찾기 어려웠다.<br>
그래서 <리눅스 임시 파일 생성>에 대해서 찾아보니 mktemp라고 /tmp 폴더 안에서 파일을 만드는 명령어를 찾을 수 있었다. 그래서 그냥 직접 tmp 폴더안에서 파일을 만들어봤다. <br>
성공적으로 만들 수 있었다. <br>
c언어 구조체에서 new를 통한 동적할당을 할 수 있고 delete가 free와 같은 역할을 한다는 것을 찾을 수 있었다. 코드 내용과 그에 대한 해석을 다시 해봐야겠다.<br>

코드에 대한 해석을 전부 끝냈다. 다시 디버깅해서 /tmp 폴더안에 0x000000000040118b를 넣고 동적할당을 할때 몇 byte를 가져가서 할당하는지 알아봐야 문제를 해결할 수 있을 것 같다<br>
give_shell함수는 0x00401570 주소에 위치하고 있고 함수를 call할 때 0x00401570 + 0x8 값의 결과를 부르기 때문에 애초에 0x00401570 - 0x8 = 0x00401568 값을 인자값으로 넣어준다.

**궁금증 : uaf 취약점을 이용할 때, 공격 코드를 할당하는 과정에서 크기를 같게 해야한다고 들었는데 크기를 확인할 수 있는 방법을 모르겠다.
