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

enum JOB
{
  JOB_NONE,
  JOB_KNIGHT,
  JOB_ARCHER,
  JOB_WIZARD,
  JOB_END // END 를 추가한 이유는 ? 향후 직업을 추가하면 값이 밀리는것을 방지하기 위해서 따로 코드 수정을 해줄 수고를 덜어줌
};

enum BATTLE
{
  BATTLE_NONE,
  BATTLE_ATTACK,
  BATTLE_BACK
};

#define NAME_SIZE 32

struct _tagInventory 
{
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
  _tagInventory tIventory;
};

// ============================================ 몬스터 구조체 ============================================

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

// ============================================ MAIN 문 ============================================

int main() 
{
  srand((unsigned int)time(0));

  // 게임을 시작할 때 플리에어 정보를 설정하게 한다.
  _tagPlayer tPlayer = {};
  
  // 플레이어 이름을 입력받는다.
   
  cout << "이름 : ";
  cin.getline(tPlayer.strName, NAME_SIZE - 1);

  int iJob = JOB_NONE;

  while (iJob == JOB_NONE)
  {
    system("clear");
    cout << "1. 기사" << endl;
    cout << "2. 궁수" << endl;
    cout << "3. 마법사" << endl;
    cout << "직업을 선택하세요 : ";
    cin >> iJob;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }
    else if (iJob <= JOB_NONE || iJob > JOB_END)
      iJob = JOB_NONE;
  }
  tPlayer.iLevel = 1;
  tPlayer.iExp = 0;
  tPlayer.eJob = (JOB)iJob;
  tPlayer.tIventory.iGold = 10000;

  // ============================================ 직업별 능력치 ============================================

  switch (tPlayer.eJob)
  {
    // ========== 기사 ==========

    case JOB_KNIGHT:
      strcpy(tPlayer.strJobName, "기사");
      tPlayer.iAttackMin = 5;
      tPlayer.iArmorMax = 10;
      tPlayer.iArmorMin = 10;
      tPlayer.iArmorMax = 15;
      tPlayer.iHPMax = 500;
      tPlayer.iHP = 500;
      tPlayer.iMP = 100;
      tPlayer.iMPMax = 100;
      break;

    // ========== 궁수 ==========

    case JOB_ARCHER:
      strcpy(tPlayer.strJobName, "궁수");
      tPlayer.iAttackMin = 10;
      tPlayer.iArmorMax = 15;
      tPlayer.iArmorMin = 10;
      tPlayer.iArmorMax = 15;
      tPlayer.iHPMax = 400;
      tPlayer.iHP = 400;
      tPlayer.iMP = 200;
      tPlayer.iMPMax = 200;
      break;

    // ========== 마법사 ==========

    case JOB_WIZARD:
      strcpy(tPlayer.strJobName, "마법사");
      tPlayer.iAttackMin = 15;
      tPlayer.iArmorMax = 20;
      tPlayer.iArmorMin = 5;
      tPlayer.iArmorMax = 10;
      tPlayer.iHPMax = 300;
      tPlayer.iHP = 300;
      tPlayer.iMP = 300;
      tPlayer.iMPMax = 300;
      break;

  }

  // ============================================ 몬스터를 생성 ============================================

  _tagMonster tMonsterArr[MT_BACK - 1] = {};

  // ========== 고블린 생성 ==========

  strcpy(tMonsterArr[0].strName, "고블린");
  tMonsterArr[0].iAttackMin = 20;
  tMonsterArr[0].iAttackMax = 30;
  tMonsterArr[0].iArmorMin = 2;
  tMonsterArr[0].iArmorMax = 5;
  tMonsterArr[0].iHP = 100;
  tMonsterArr[0].iHPMax = 100;
  tMonsterArr[0].iMP = 10;
  tMonsterArr[0].iMPMax = 10;
  tMonsterArr[0].iLevel = 1;
  tMonsterArr[0].iExp = 1000;
  tMonsterArr[0].iGoldMin = 500;
  tMonsterArr[0].iGoldMax = 1500;

  // ========== 트롤 생성 ==========

  strcpy(tMonsterArr[1].strName, "트롤");
  tMonsterArr[1].iAttackMin = 80;
  tMonsterArr[1].iAttackMax = 130;
  tMonsterArr[1].iArmorMin = 60;
  tMonsterArr[1].iArmorMax = 90;
  tMonsterArr[1].iHP = 2000;
  tMonsterArr[1].iHPMax = 2000;
  tMonsterArr[1].iMP = 100;
  tMonsterArr[1].iMPMax = 100;
  tMonsterArr[1].iLevel = 5;
  tMonsterArr[1].iExp = 7000;
  tMonsterArr[1].iGoldMin = 6000;
  tMonsterArr[1].iGoldMax = 8000;

  // ========== 드래곤 생성 ==========

  strcpy(tMonsterArr[2].strName, "드래곤");
  tMonsterArr[2].iAttackMin = 250;
  tMonsterArr[2].iAttackMax = 500;
  tMonsterArr[2].iArmorMin = 200;
  tMonsterArr[2].iArmorMax = 400;
  tMonsterArr[2].iHP = 30000;
  tMonsterArr[2].iHPMax = 30000;
  tMonsterArr[2].iMP = 20000;
  tMonsterArr[2].iMPMax = 20000;
  tMonsterArr[2].iLevel = 10;
  tMonsterArr[2].iExp = 30000;
  tMonsterArr[2].iGoldMin = 20000;
  tMonsterArr[2].iGoldMax = 50000;


  // ============================================ 로비 ============================================

  while (true)
  {
    system("clear");
    cout << "============================ 로비 ============================" << endl;
    cout << "1. 맵" << endl;
    cout << "2. 상점" << endl;
    cout << "3. 가방" << endl;
    cout << "4. 종료" << endl;
    cout << "메뉴를 선택하세요" << endl;
    int iMenu;
    cin >> iMenu;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (iMenu == MM_EXIT) break;
    
    // ============================================ 메뉴 ============================================

    switch (iMenu)
    {
      // ============================================ 맵 ============================================
      case MM_MAP:
        while (true)
        {
          system("clear");
          cout << "============================ 맵 ============================" << endl;
          cout << "1. 쉬움" << endl;
          cout << "2. 보통" << endl;
          cout << "3. 어려움" << endl;
          cout << "4. 뒤로가기" << endl;
          cout << "맵을 선택하세요 : " << endl;
          cin >> iMenu;

          if (cin.fail()) 
          {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
          }

          // 이 if 문에 속한 break 는 맵 메뉴를 돌려주기 위한 while 에 속해있으므로 
          // 이 while 문을 빠져나간다.
          if (iMenu == MT_BACK) break;
          
          // 선택한 메뉴에서 1을 빼주면 몬스터 배열의 인덱스가 된다.
          // 그렇게 해서 해당 맵의 몬스터를 생성해준다.
          _tagMonster tMonster = tMonsterArr[iMenu - 1];

          while (true)
          {
            system("clear");
            switch (iMenu)
            {
              // ============================================ 맵 난이도 ============================================

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
            
            // 플레이어 정보를 출력한다.
            cout << "=============== Player ===============" << endl;
            cout << "이름 : " << tPlayer.strName << "\t직업 : " <<  tPlayer.strJobName << endl;
            cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " << tPlayer.iExp << endl;
            cout << "공격력 : " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax << "\t방어력 : " 
            << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax << endl;
            cout << "체력 : " << tPlayer .iHP << " / " << tPlayer.iHPMax << "\t마나 : " 
            << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
            cout << "보유골드 : " << tPlayer.tIventory.iGold << "Gold" << endl;

            // 몬스터 정보 출력
            cout << "=============== Monster ===============" << endl;
            cout << "이름 : " << tMonster.strName << "\t레벨 : " << tMonster.iLevel << endl;
            cout << "공격력 : " << tMonster.iAttackMin << " - " << tMonster.iAttackMax << "\t방어력 : " 
            << tMonster.iArmorMin << " - " << tMonster.iArmorMax << endl;
            cout << "체력 : " << tMonster.iHP << " / " << tMonster.iHPMax << "\t마나 : " 
            << tMonster.iMP << " / " << tMonster.iMPMax << endl;
            cout << "획득경험치 : " << tMonster.iExp << "\t획득골드 : " << tMonster.iGoldMin << " - " 
            << tMonster.iGoldMax << endl;

            cout << "1. 공격" << endl;
            cout << "2. 도망가기" << endl;
            cout << "메뉴를 선택하세요 : ";
            cin >> iMenu;

            if (cin.fail())
            {
              cin.clear();
              cin.ignore(1024, '\n');
              continue;
            }

            else if (iMenu == BATTLE_BACK) break;

            switch (iMenu)
            {
              case BATTLE_ATTACK:
              {
                // 예를 들어 Min 5 Max 15 라고, 가정할 경우
                // 15 - 5 + 1 을 하면 11 이 된다. 11로 나눈 나머지는 0 ~ 10 이 나오게 되고
                // 여기에 Min값인 5를 더하게 되면 5 ~ 15 사이로 값이 나오게 되는것이다.
                int iAttack = rand() % (tPlayer.iAttackMax - tPlayer.iAttackMin + 1) + 
                  tPlayer.iAttackMin;
                int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
                  tMonster.iArmorMin;

                int iDamage = iAttack - iArmor;
                // 삼항연산자 : 조건식 ? true일때 값 : false 일때 값;
                iDamage = iDamage < 1 ? 1 : iDamage;

                // 몬스터 HP를 감소시킨다.
                tMonster.iHP -= iDamage;

                cout << tPlayer.strName << " (이)가 " << tMonster.strName << " 에게 " << iDamage << "피해를 입혔습니다." << endl;

                // 몬스터가 죽었을 경우를 처리한다.
                if (tMonster.iHP <= 0)
                {
                  cout << tMonster.strName << " 몬스터가 사망하였습니다." << endl;

                  tPlayer.iExp += tMonster.iExp;
                  int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) + tMonster.iGoldMin);
                  tPlayer.tIventory.iGold += iGold;

                  cout << tMonster.iExp << "경험치를 획득하였습니다." << endl;
                  cout << iGold << "골드를 획득하였습니다." << endl;

                  tMonster.iHP = tMonster.iHPMax;
                  tMonster.iMP = tMonster.iMPMax;

                  system("read"); // mac에서는 pause 대신 read 를 씀
                  break;
                }

                // 몬스터가 살아있다면 플레이어를 공격한다.
                iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) + 
                  tMonster.iAttackMin;
                iArmor = rand() % (tPlayer.iArmorMax - tPlayer.iArmorMin + 1) +
                  tPlayer.iArmorMin;

                iDamage = iAttack - iArmor;
                // 삼항연산자 : 조건식 ? true일때 값 : false 일때 값;
                iDamage = iDamage < 1 ? 1 : iDamage; // 최소 데미지를 1로 만들어 놓음

                // 플레이어의 HP 를 감소시킨다.
                tPlayer.iHP -= iDamage;

                cout << tMonster.strName << " (이)가 " << tPlayer.strName << " 에게 " << iDamage << " 피해를 입혔습니다." << endl;

                // 플레이어가 죽었을 경우
                if (tPlayer.iHP <= 0)
                {
                  cout << tPlayer.strName << " 플레이어가 사망하였습니다." << endl;

                  int iExp = tPlayer.iExp * 0.1f;
                  int iGold = tPlayer.tIventory.iGold * 0.1f;

                  tPlayer.iExp -= iExp;
                  tPlayer.tIventory.iGold -= iGold;

                  cout << iExp << " 경험치를 잃었습니다." << endl;
                  cout << iGold << " 골드를 잃었습니다." << endl; 

                  // 플레이어의 HP와 MP 를 회복한다. 
                  tPlayer.iHP = tPlayer.iHPMax;
                  tPlayer.iMP = tPlayer.iMPMax;
                }
                system("read"); 
              }
              break;
            }
          }
        }
        break;

      // ============================================ 상점 ============================================

      case MM_STORE:
        break;

      // ============================================ 가방 ============================================

      case MM_INVENROTY:
        break;
      default:
        cout << "잘못 선택하였습니다." << endl;
        break;
    }
  }
  return 0;
}