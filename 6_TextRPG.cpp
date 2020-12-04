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

enum ITEM_TYPE
{
  IT_NONE,
  IT_WEAPON,
  IT_ARMOR,
  IT_BACK 
};

enum STORE_MENU
{
  SM_NONE,
  SM_WEAPON,
  SM_ARMOR,
  SM_BACK
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

// ============================================= 몬스터 구조체 =============================================

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

// =============================================== MAIN 문 ===============================================

int main() 
{
  srand((unsigned int)time(0));

  // 레벨업에 필요한 경험치 목록을 만든다.
  const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
  
  // JOB_END 는 4이다. 그런데 직업은 3개이므로 -1 을 해주어서 배열을 각 직업별로 생성하도록 한다.
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
  tPlayer.tInventory.iGold = 10000;

  // ============================================= 직업별 능력치 =============================================

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

  // ============================================= 몬스터를 생성 =============================================

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

  // 상점에서 판매할 아이템 목록을 생성한다.

  _tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
  _tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

  // 각 아이템 정보들을 설정해준다.
  strcpy(tStoreWeapon[0].strName, "목검");
	strcpy(tStoreWeapon[0].strTypeName, "무기");
	strcpy(tStoreWeapon[0].strDesc, "나무로 만든 칼");
	tStoreWeapon[0].eType = IT_WEAPON;
	tStoreWeapon[0].iMin = 5;
	tStoreWeapon[0].iMax = 10;
	tStoreWeapon[0].iPrice = 1000;
	tStoreWeapon[0].iSell = 500;

	strcpy(tStoreWeapon[1].strName, "장궁");
	strcpy(tStoreWeapon[1].strTypeName, "무기");
	strcpy(tStoreWeapon[1].strDesc, "짱짱한 활");
	tStoreWeapon[1].eType = IT_WEAPON;
	tStoreWeapon[1].iMin = 20;
	tStoreWeapon[1].iMax = 40;
	tStoreWeapon[1].iPrice = 7000;
	tStoreWeapon[1].iSell = 3500;

	strcpy(tStoreWeapon[2].strName, "지팡이");
	strcpy(tStoreWeapon[2].strTypeName, "무기");
	strcpy(tStoreWeapon[2].strDesc, "나무로 만든 지팡이");
	tStoreWeapon[2].eType = IT_WEAPON;
	tStoreWeapon[2].iMin = 90;
	tStoreWeapon[2].iMax = 150;
	tStoreWeapon[2].iPrice = 30000;
	tStoreWeapon[2].iSell = 15000;

	// ================ 방어구 =================
	strcpy(tStoreArmor[0].strName, "천갑옷");
	strcpy(tStoreArmor[0].strTypeName, "방어구");
	strcpy(tStoreArmor[0].strDesc, "천으로 만든 허접한 갑옷");
	tStoreArmor[0].eType = IT_ARMOR;
	tStoreArmor[0].iMin = 2;
	tStoreArmor[0].iMax = 5;
	tStoreArmor[0].iPrice = 1000;
	tStoreArmor[0].iSell = 500;

	strcpy(tStoreArmor[1].strName, "가죽갑옷");
	strcpy(tStoreArmor[1].strTypeName, "방어구");
	strcpy(tStoreArmor[1].strDesc, "동물 가죽으로 만든 질긴 갑옷");
	tStoreArmor[1].eType = IT_ARMOR;
	tStoreArmor[1].iMin = 10;
	tStoreArmor[1].iMax = 20;
	tStoreArmor[1].iPrice = 7000;
	tStoreArmor[1].iSell = 3500;

	strcpy(tStoreArmor[2].strName, "판금갑옷");
	strcpy(tStoreArmor[2].strTypeName, "방어구");
	strcpy(tStoreArmor[2].strDesc, "강철로 만든 판금 갑옷");
	tStoreArmor[2].eType = IT_ARMOR;
	tStoreArmor[2].iMin = 70;
	tStoreArmor[2].iMax = 90;
	tStoreArmor[2].iPrice = 30000;
	tStoreArmor[2].iSell = 15000;


  // =============================================== 로비 ===============================================

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
            cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " << tPlayer.iExp << " / " << 
              iLevelUpExp[tPlayer.iLevel - 1] << endl;
            if (tPlayer.bEquip[EQ_WEAPON] == true)
  					{
		  				cout << "공격력 : " << tPlayer.iAttackMin << " + " <<
							tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
	  				}

            else
					  {
						  cout << "공격력 : " << tPlayer.iAttackMin << " - " <<
							  tPlayer.iAttackMax;
					  }

            if (tPlayer.bEquip[EQ_ARMOR] == true)
					  {
						  cout << "\t방어력 : " << tPlayer.iArmorMin << " + " <<
							tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					  }

            else
					  {
						  cout << "\t방어력 : " << tPlayer.iArmorMin << " - " <<
							  tPlayer.iArmorMax << endl;
					  }

					  cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
						  "\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

					  if (tPlayer.bEquip[EQ_WEAPON])
						  cout << "무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;

					  else
						  cout << "무기 : 없음";

					  if (tPlayer.bEquip[EQ_ARMOR])
						  cout << "\t방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;

					  else
						  cout << "\t방어구 : 없음" << endl;

					  cout << "획득골드 : " << tPlayer.tInventory.iGold << " Gold" << endl << endl;

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
                int iAttackMin = tPlayer.iAttackMin;
                int iAttackMax = tPlayer.iAttackMax;

                // 무기를 장착하고 있을 경우 무기와 Min, Max 를 더해준다.
                if (tPlayer.bEquip[EQ_WEAPON])
						    {
							    iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							    iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						    }

                int	iAttack = rand() % (iAttackMax - iAttackMin + 1) +
							    iAttackMin;
						    int	iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
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
							    int	iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
								    tMonster.iGoldMin);
							    tPlayer.tInventory.iGold += iGold;

                  cout << tMonster.iExp << "경험치를 획득하였습니다." << endl;
                  cout << iGold << "골드를 획득하였습니다." << endl;

                  tMonster.iHP = tMonster.iHPMax;
                  tMonster.iMP = tMonster.iMPMax;

                  // 레벨업을 했는지 체크해 본다.
                  if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							    {
                    // 플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
                    tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

                    // 레벨을 증가시킨다.
                    ++tPlayer.iLevel;

                    cout << "레벨업 !! " << endl;

                    // 능력치를 상승시킨다.
                    // 직업 인덱스를 구한다.
                    int	iJobIndex = tPlayer.eJob - 1;
                    int	iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) +
									    tLvUpTable[iJobIndex].iHPMin;
								    int	iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin + 1) +
									    tLvUpTable[iJobIndex].iMPMin;

								    tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
								    tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
								    tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
								    tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

								    tPlayer.iHPMax += iHPUp;
								    tPlayer.iMPMax += iMPUp;
								  
								    tPlayer.iHP = tPlayer.iHPMax;
								    tPlayer.iMP = tPlayer.iMPMax;
                  }   

                  system("read"); // mac에서는 pause 대신 read 를 씀
                  break;
                }

                // 몬스터가 살아있다면 플레이어를 공격한다.

                iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
							    tMonster.iAttackMin;

						    int	iArmorMin = tPlayer.iArmorMin;
						    int	iArmorMax = tPlayer.iArmorMax;

						    if (tPlayer.bEquip[EQ_ARMOR])
						    {
							    iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							    iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						    }


                iArmor = rand() % (iArmorMax - iArmorMin + 1) +
							    iArmorMin;

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
                  int iGold = tPlayer.tInventory.iGold * 0.1f;

                  tPlayer.iExp -= iExp;
                  tPlayer.tInventory.iGold -= iGold;

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
        while (true)
        {
          system("clear");
          cout << "============================ 상점 ============================" << endl;
          cout << "1. 무기상점" << endl;
          cout << "2. 방어구상점" << endl;
          cout << "3. 뒤로가기" << endl;
          cout << "상점을 선택하세요." << endl;
          cin >> iMenu;

          if (cin.fail())
          {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
          }

          else if (iMenu == SM_BACK) break;

          // ========================================= 판매 목록 =========================================
          switch (iMenu)
          {
            case SM_WEAPON:
              while (true)
              {
                system("clear");

                cout << "============================ 무기 상점 ============================" << endl;
                // 판매 목록을 보여준다.
                for (int i = 0; i < STORE_WEAPON_MAX; ++i)
                {
                  
                  cout << i + 1 << ". 이름 : " << tStoreWeapon[i].strName << "\t종류 : " << tStoreWeapon[i].strTypeName << endl;
                  cout << "공격력 : " << tStoreWeapon[i].iMin << " - " << tStoreWeapon[i].iMax << endl;
                  cout << "판매가격 : " << tStoreWeapon[i].iPrice << "\t구매가격 : " << tStoreWeapon[i].iSell << endl;
                  cout << "설명 : " << tStoreWeapon[i].strDesc << endl << endl;
                }

                cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
                cout << "보유금액 : " << tPlayer.tInventory.iGold << endl;
                cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
                cout << "구입할 아이템을 선택하세요.";
                cin >> iMenu;

                if (cin.fail())
                {
                  cin.clear();
                  cin.ignore(1024, '\n');
                  continue;
                }

                else if (iMenu == STORE_WEAPON_MAX + 1) break;

                else if (iMenu < 1 || iMenu > STORE_WEAPON_MAX + 1)
						    {
							    cout << "잘못선택하였습니다." << endl;
							    system("read");
							    continue;
					      }

                // 상점판매목록의 배열을 인덱스로 구해준다.
                int	iWeaponIndex = iMenu - 1;

                // 인벤토리가 꽉찼는지 검사한다.
                if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						    {
							    cout << "가방이 꽉 찼습니다." << endl;
							    system("read");
							    continue;
						    }

                // 돈이 부족할 경우
                else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice)
						    {
							    cout << "보유금액이 부족합니다." << endl;
							    system("read");
							    continue;
						    }


                // 처음에 iItemCount는 하나도 추가되어 있지 않기 때문에 0으로 초기화 되어 있으므로,
                // 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고 카운트 1이 된다.
                // 다음번에 추가할때는 1번 인덱스에 추가하게된다.
                tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							    tStoreWeapon[iWeaponIndex];
						    ++tPlayer.tInventory.iItemCount;

                // 골드를 차감한다
						    tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;

						    cout << tStoreWeapon[iWeaponIndex].strName << " 아이템을 구매하였습니다." << endl;
						    system("read");
              }
              break;
            case SM_ARMOR:
              while (true)
              {
                system("clear");

                cout << "============================ 방어구 상점 ============================" << endl;
                // 판매 목록을 보여준다.
                for (int i = 0; i < STORE_ARMOR_MAX; ++i)
                {
                  cout << i + 1 << ". 이름 : " << tStoreArmor[i].strName << "\t종류 : " << tStoreArmor[i].strTypeName << endl;
                  cout << "공격력 : " << tStoreArmor[i].iMin << " - " << tStoreArmor[i].iMax << endl;
                  cout << "판매가격 : " << tStoreArmor[i].iPrice << "\t구매가격 : " << tStoreArmor[i].iSell << endl;
                  cout << "설명 : " << tStoreArmor[i].strDesc << endl << endl;
                }

                cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl;
                cout << "보유금액 : " << tPlayer.tInventory.iGold << "Gold" << endl;
                cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
                cout << "구입할 아이템을 선택하세요.";
                cin >> iMenu;

                if (cin.fail())
                {
                  cin.clear();
                  cin.ignore(1024, '\n');
                  continue;
                }

                else if (iMenu == STORE_ARMOR_MAX + 1) break;

                else if (iMenu < 1 || iMenu > STORE_ARMOR_MAX + 1)
						    {
							    cout << "잘못선택하였습니다." << endl;
							    system("read");
							    continue;
					      }

                // 상점판매목록의 배열을 인덱스로 구해준다.
                int iArmorIndex = iMenu - 1;

                // 인벤토리가 꽉찼는지 검사한다.
                if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						    {
							    cout << "가방이 꽉 찼습니다." << endl;
							    system("read");
							    continue;
						    }

                // 돈이 부족할 경우
                else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice)
						    {
							    cout << "보유금액이 부족합니다." << endl;
							    system("read");
							    continue;
						    }


                // 처음에 iItemCount는 하나도 추가되어 있지 않기 때문에 0으로 초기화 되어 있으므로,
                // 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고 카운트 1이 된다.
                // 다음번에 추가할때는 1번 인덱스에 추가하게된다.
                tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							    tStoreArmor[iArmorIndex];
						    ++tPlayer.tInventory.iItemCount;

                // 골드를 차감한다
						    tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;

						    cout << tStoreArmor[iArmorIndex].strName << " 아이템을 구매하였습니다." << endl;
						    system("read");
              }

              break;
          }

        }
        break;

      // ============================================ 가방 ============================================

      case MM_INVENROTY:
        while (true) {
          system("clear");
          cout << "============================ 가방 ============================" << endl;
          cout << endl;
          cout << "=============== Player ===============" << endl;
          cout << "이름 : " << tPlayer.strName << "\t직업 : " <<  tPlayer.strJobName << endl;
          cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " << tPlayer.iExp << endl;

          // 무기를 장착하고 있을 경우 공격력에 무기공격력을 추가하여 출력한다. 
          if (tPlayer.bEquip[EQ_WEAPON] == true) 
          {
            cout << "공격력 : " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
              tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
          }

          else 
          {
            cout << " 공격력 : " << tPlayer.iAttackMin << " - " << 
              tPlayer.iAttackMax;
          }

          // 방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
          if (tPlayer.bEquip[EQ_ARMOR] == true) 
          {
            cout << "\t방어력 : " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
              tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax;
          }

          else 
          {
            cout << "\t방어력 : " << tPlayer.iArmorMin << " - " << 
              tPlayer.iArmorMax << endl;
          }

          cout << "체력 : " << tPlayer .iHP << " / " << tPlayer.iHPMax << "\t마나 : " 
          << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

          if (tPlayer.bEquip[EQ_WEAPON])
            cout << "장착무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;

          else
            cout << "장착무기 : 없음";

          if (tPlayer.bEquip[EQ_ARMOR])
            cout << "\t장착방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;

          else
            cout << "\t장착방어구 : 없음" << endl;

          cout << "보유골드 : " << tPlayer.tInventory.iGold << "Gold" << endl;
          cout << endl;

          for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i) 
          {
            cout << "=============== Item ===============" << endl;
            cout << i + 1 << ". 이름 : " << tPlayer.tInventory.tItem[i].strName << "\t종류 : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
            cout << "공격력 : " << tPlayer.tInventory.tItem[i].iMin << " - " << tPlayer.tInventory.tItem[i].iMax << endl;
            cout << "판매가격 : " << tPlayer.tInventory.tItem[i].iPrice << "\t구매가격 : " << tPlayer.tInventory.tItem[i].iSell << endl;
            cout << "설명 : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
          }

          cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
          cout << "장착할 아이템을 선택하세요 : ";
          cin >> iMenu;

          if (cin.fail())
          {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
          }

          else if (iMenu == tPlayer.tInventory.iItemCount + 1) break;

          else if (iMenu < 1 || iMenu > tPlayer.tInventory.iItemCount + 1)
          {
            cout << "잘못 선택하였습니다." << endl;
            system("read");
            continue;
          }

          // 아이템의 인덱스를 구해준다. 
          int idx = iMenu - 1;

          // 제대로 선택했을 경우 해당 아이템의 종류에 따라 장착 부위를 결정하게 한다.
          EQUIP eq;

          switch (tPlayer.tInventory.tItem[idx].eType)
          {
            case IT_WEAPON:
              eq = EQ_WEAPON;
              break;
            case IT_ARMOR:
              eq = EQ_ARMOR;
              break;
          }

          // 아이템이 장착되어 있지 않을 경우 장착되어 있는 아이템과 장착할 아이템을 교체해 주어야 한다.
          // Swap 알고리즘을 활용한다.
          if (tPlayer.bEquip[eq] == true)
				  {
					  _tagItem	tSwap = tPlayer.tEquip[eq];
					  tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					  tPlayer.tInventory.tItem[idx] = tSwap;
				  }

          // 장착되어 있지 않을 경우 인벤토리 아이템을 장착창으로 옮기고 인벤토리는 1칸 비워지게 된다.
          else 
          {
            tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

            for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; ++i)
					  {
						  tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					  }

            --tPlayer.tInventory.iItemCount;

            // 장착을 했기 때문에 true 로 만들어 준다.
            tPlayer.bEquip[eq] = true;
          }

          cout << tPlayer.tEquip[eq].strName << "아이템을 장착하였습니다." << endl;

          system("read");
        }
        break;
      default:
        cout << "잘못 선택하였습니다." << endl;
        break; 
    }
  }
  return 0;
}