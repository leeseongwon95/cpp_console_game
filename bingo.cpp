#include <iostream>
#include <time.h>
// system clear 를 위해
#include <stdlib.h>

using namespace std;

int main() {
  srand((unsigned int)time(0));

  int iNumber[25] = {};

  // 1 ~ 25 까지의 숫자를 넣어준다.
  for (int i = 0; i < 25; ++i) {
    iNumber[i] = i + 1;
  }

  // 숫자를 섞어준다
  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; ++i) {
    idx1 = rand() % 25;
    idx2 = rand() % 25;

    iTemp = iNumber[idx1];
    iNumber[idx1] = iNumber[idx2];
    iNumber[idx2] = iTemp;
  }

  while (true) {
    // Mac 에서는 system("cls") 가 안되고 헤더파일을 추가하고 clear 를 해주면 됨.
    system("clear");

    // 숫자를 5 x 5 로 출력한다.
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (iNumber[i * 5 + j] == INT_MAX) cout << "*\t";
        else cout << iNumber[i * 5 + j] << "\t";
      } 
      cout << endl;
    }
    cout << "숫자를 입력하세요(0은 종료) : ";
    int iInput;
    cin >> iInput;

    if (iInput == 0) break;
    else if (iInput < 1 || iInput > 25) continue;

    // 중복입력을 체크하기 위한 변수이다. 기본적으로 중복되었다라고 
    // 하기위해 true 로 잡아줌.
    bool bAcc = true;

    // 모든 숫자를 차례대로 검사해서 입력한 숫자와 같은 숫자가 있는지를 찾아낸다.
    for (int i = 0; i < 25; ++i) {
      // 같은 숫자가 있을 경우 
      if (iInput == iNumber[i]) {
        // 숫자를 찾았을 경우 중복된 숫자가 아니므로 
        // bAcc 변수를 false 로 만들어준다.
        bAcc = false;

        // 숫자를 *로 변경하기 위해 특수한 값인 INT_MAX 로 만들어준다.
        iNumber[i] = INT_MAX;

        // 더 이상 다른 숫자를 찾아볼 필요가 없으므로 반복문을 빠져나간다.
        break;
      }
    }
    // bAcc 변수가 true 일 경우 중복된 숫자를 입력해서 숫자를 *로
    // 바꾸지 못했으므로 다시 입력받게 continue 해준다
    if (bAcc) continue;
  }

  return 0;
}