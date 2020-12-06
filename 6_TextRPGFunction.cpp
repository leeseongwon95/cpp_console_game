#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

enum MAIN_MENU 
{
  MM_NONE,
  MM_MAP,
  MM_STORE,
  MM_INVENROTY,
  MM_EXIT  
};

enum MAP_TYPE
{
  MT_NONE,
  MT_EASY,
  MT_NORMAL,
  MT_HARD,
  MT_BACK
}; 


int OutputMainMenu();
int InputInt();
void RunMap();

int main()
{
  srand((unsigned int)time(0));

  bool bLoop = true;

  while (bLoop)
  {
    switch (OutputMainMenu())
    {
      case MM_MAP:
        RunMap(); // 맵 관련 루프를 처리한다.
        break;
      case MM_STORE:
        break;
      case MM_INVENROTY:
        break;
      case MM_EXIT:
        bLoop = false;
        break; 
    }
  }

  return 0;
}

// 숫자 입력을 받는다. 입력 오류까지 처리해주고 INT_MAX 를 리턴하면
// 입력 오류이다.
int InputInt()
{
  int iInput;
  cin >> iInput;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(1024, '\n');
    return INT_MAX; // INT_MAX 가 리턴되면 입력이 잘못되었는다는 의미
  }
  return iInput;
}

// 메인 메뉴를 화면에 보여주고 입력받은 메뉴를 반환한다.
// 입력 오류 일 경우 혹은 잘못된 번호를 입력한 경우 MM_NONE을
// 반환해준다.
int OutputMainMenu() {
  system("clear");
  cout << "============================ 로비 ============================" << endl;
  cout << "1. 맵" << endl;
  cout << "2. 상점" << endl;
  cout << "3. 가방" << endl;
  cout << "4. 종료" << endl;
  cout << "메뉴를 선택하세요" << endl;
  int iMenu = InputInt();

  if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
    return MM_NONE;

  return iMenu; 
}

int OutputMapMenu()
{
  system("clear");
  cout << "============================ 맵 ============================" << endl;
  cout << "1. 쉬움" << endl;
  cout << "2. 보통" << endl;
  cout << "3. 어려움" << endl;
  cout << "4. 뒤로가기" << endl;
  cout << "맵을 선택하세요 : " << endl;
  int iMenu = InputInt();

  if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
    return MM_NONE;

  return iMenu;
}

// 맵에 관련된 동작을 처리한다.
void RunMap() 
{
  bool bLoop = true;

  while (bLoop)
  {
    switch (OutputMapMenu())
    {
      case MT_EASY:
        cout << "============================ 쉬움 ============================" << endl;
        break;
      case MT_NORMAL:
        cout << "============================ 보통 ============================" << endl;
        break;
      case MT_HARD:
        cout << "============================ 어려움 ============================" << endl;
        break;
    }
  }
}

