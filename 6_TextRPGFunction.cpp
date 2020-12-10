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

enum BATTLE
{
  BATTLE_NONE,
  BATTLE_ATTACK,
  BATTLE_BACK
};

enum ITEM_TYPE
{
  IT_NONE,
  IT_WEAPON,
  IT_ARMOR,
  IT_BACK 
};

enum MAP_TYPE
{
  MT_NONE,
  MT_EASY,
  MT_NORMAL,
  MT_HARD,
  MT_BACK
}; 

enum JOB
{
  JOB_NONE,
  JOB_KNIGHT,
  JOB_ARCHER,
  JOB_WIZARD,
  JOB_END // END 를 추가한 이유는 ? 향후 직업을 추가하면 값이 밀리는것을 방지하기 위해서 따로 코드 수정을 해줄 수고를 덜어줌
};

enum EQUIP
{
  EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX  3
#define STORE_ARMOR_MAX 3
#define	LEVEL_MAX 10

struct _tagItem
{
  char strName[NAME_SIZE];
  char strTypeName[NAME_SIZE];
  ITEM_TYPE eType;
  int iMin;
  int iMax;
  int iPrice;
  int iSell;
  char strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory 
{
  _tagItem tItem[INVENTORY_MAX];
  int iItemCount;
  int iGold;
};

// ============================================ 플레이어 구조체 ============================================

struct _tagPlayer  
{
  char strName[NAME_SIZE];
  char strJobName[NAME_SIZE];
  JOB eJob;
  int iAttackMin;
  int iAttackMax;
  int iArmorMin;
  int iArmorMax;
  int iHP;
  int iHPMax;
  int iMP;
  int iMPMax;
  int iExp;
  int iLevel;
  _tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory	tInventory;
};


struct _tagMonster 
{
  char strName[NAME_SIZE];
  int iAttackMin;
  int iAttackMax;
  int iArmorMin;
  int iArmorMax;
  int iHP;
  int iHPMax;
  int iMP;
  int iMPMax;
  int iLevel;
  int iExp;
  int iGoldMin;
  int iGoldMax;
};

struct _tagLevelUpStatus
{
	int	iAttackMin;
	int	iAttackMax;
	int	iArmorMin;
	int	iArmorMax;
	int	iHPMin;
	int	iHPMax;
	int	iMPMin;
	int	iMPMax;
};


int OutputMainMenu();
int InputInt();
void RunMap();

int main()
{

  const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };

  _tagLevelUpStatus	tLvUpTable[JOB_END - 1] = {};

  // 기사
  tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvUpTable[JOB_KNIGHT - 1].iHPMin = 50;
	tLvUpTable[JOB_KNIGHT - 1].iHPMax = 100;
	tLvUpTable[JOB_KNIGHT - 1].iMPMin = 10;
	tLvUpTable[JOB_KNIGHT - 1].iMPMax = 20;

  // 궁수
	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iHPMax = 60;
	tLvUpTable[JOB_ARCHER - 1].iMPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iMPMax = 50;

  // 마법사
	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvUpTable[JOB_WIZARD - 1].iHPMin = 20;
	tLvUpTable[JOB_WIZARD - 1].iHPMax = 40;
	tLvUpTable[JOB_WIZARD - 1].iMPMin = 50;
	tLvUpTable[JOB_WIZARD - 1].iMPMax = 100;

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
      case MT_BACK:
        bLoop = false;
        break;
    }
  }
}

