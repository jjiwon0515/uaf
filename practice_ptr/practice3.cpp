#include <iostream>
#include <cstring>

# std 소속에 있는 함수들을 사용할 수 있도록 한다.
using namespace std;

# 클래스 Car를 선언
class Car
{

private:
    // 멤버 상수
    enum
    {
        ID_LEN = 20,
        MAX_SPD = 200,
        FUEL_STEP = 2,
        ACC_STEP = 10,
        BRK_STEP = 10
    };
    // 맴버 변수
    char gamerID[ID_LEN];
    int fuelGauge;
    int curSpeed;
public:
    // 맴버 함수
    void InitMembers(const char* ID, int fuel);
    void ShowCarState();
    void Accel();
    void Break();
};


# 클래스 안의 InitMembers 함수들을 가져온다 
# ID 포인터 변수와 fuel 변수를 매개변수로 받는다.
void Car::InitMembers(const char* ID, int fuel)
{
    strcpy_s(gamerID, ID);  // strcpy는 안전하지 않은 함수이므로 strcpy_s 사용
    fuelGauge = fuel;
    curSpeed = 0;
}


# 클래스 안의 ShowCarstate 함수를 가져온다.
void Car::ShowCarState()
{
    cout << "소유자 ID: " << gamerID << endl;
    cout << "연료량: " << fuelGauge << "%" << endl;
    cout << "현재 속도: " << curSpeed << "km/h" << endl << endl;
}


# 클래스 안의 Accel 함수를 가져온다.
void Car::Accel()
{
    if (fuelGauge <= 0)
        return;
    else
        fuelGauge -= FUEL_STEP;

    if (curSpeed + ACC_STEP >= MAX_SPD)
    {
        curSpeed = MAX_SPD;
        return;
    }
    curSpeed += ACC_STEP;
}


# 클래스 안의 Break 함수들 가져온다.
void Car::Break()
{
    if (curSpeed < BRK_STEP)
    {
        curSpeed = 0;
        return;
    }
    curSpeed -= BRK_STEP;
}



int main(void)
{
    Car run99;  // 클래스 Car의 객체 run99
    run99.InitMembers("run99", 100);  // 클래스는 선언과 초기화를 분리해야 함
    run99.Accel(); // run99의 맴버 함수
    run99.Accel();
    run99.ShowCarState();
    run99.Break();
    run99.ShowCarState();

    Car sped77;  // 클래스 Car의 객체 sped77
    sped77.InitMembers("sped77", 100);
    sped77.Accel();  // sped77의 맴버 함수
    sped77.Break();
    sped77.ShowCarState();

    system("pause");  // VC++ 에서만 필요

    return 0;
}
