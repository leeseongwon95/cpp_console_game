#include <iostream>
#include <time.h>

// 윈도우 환경에서는 conio.h 헤더파일을 추가해주면 되지만
// 표준라이브러리가 아니라 mac os 에서는 안돌아간다. 그래서 
// 밑의 두 헤더파일을 만들고 getch 함수를 직접 만들어 사용했다.
#include <termios.h>
#include <unistd.h>
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

using namespace std;

int main() {
  srand((unsigned int)time(0));

  int iNumber[25] = {};

  for (int i = 0; i < 24; i++) {
    iNumber[i] = i + 1;
  }

  // 가장 마지막 칸은 공백으로 비워둔다. 공백을 의미하는 값으로 특수한 값을 사용할건데 int max 라는 값을 사용한다.
  // int max 는 이미 정해진 값으로 int 로 표현할수 있는 최대값이다.
  iNumber[24] = INT_MAX;

  // 별이 있는 위치를 저장할 변수를 만들어준다.
  int iStarIndex = 24;

  // 마지막 공백을 제외하고 1 ~ 24 까지의 숫자를 섞어준다. 
  // 즉, 인덱스는 0 ~ 23 번 인덱스 까지만 섞어준다.

  int iTemp, idx1, idx2;

  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 24;
    idx2 = rand() % 24;

    iTemp = iNumber[idx1];
    iNumber[idx1] = iNumber[idx2];
    iNumber[idx2] = iTemp;
  }
  while (true) {

    // i for 문이 세로줄을 의미
    for (int i = 0; i < 5; i++) {
      // j for 문이 가로칸을 의미
      for (int j = 0; j < 5; j++) {
        // i 가 0 일때 j 는 0 ~ 4 까지 반복한다. 이 경우 0 * 5 + (0 ~ 4) 를 더하게 됨
        // 인덱스는 0, 1, 2, 3, 4 가 나오게 되고
        // i 가 1 일때 j는 0 ~ 4 까지 반복한다. 이 경우 1 * 5 + (0 ~ 4) 를 더하가 됨
        // 인덱스는 5, 6, 7, 8, 9 가 나오게 되고
        // i 가 2 일때 j 는 0 ~ 4 까지 반복한다. 이 경우 2 * 5 + (0 ~ 4) 를 더하게 됨
        // 인덱스는 10, 11, 12, 13, 14 가 나오게 되고
        // i 가 3 일때 j는 0 ~ 4 까지 반복한다. 이 경우 3 * 5 + (0 ~ 4) 를 더하가 됨
        // 인덱스는 15, 16, 17, 18, 19 가 나오게 되고
        // i 가 4 일때 j 는 0 ~ 4 까지 반복한다. 이 경우 4 * 5 + (0 ~ 4) 를 더하게 됨
        // 인덱스는 20, 21, 22, 23, 24 가 나오게 되고

        // 줄번호 * 가로개수 + 칸번호

        if (iNumber[i * 5 + j] == INT_MAX)
          cout << "*\t";
        else
          cout << iNumber[i * 5 + j] << "\t";
      }
      cout << endl;
    }

    // 퍼즐을 모두 맞췄을 때
    bool bWin = true;

    // 퍼즐을 맞추었는지 체크한다.
    for (int i = 0; i < 24; i++) {
      if (iNumber[i] != i + 1) {
        bWin = false;
        break;
      }
    }

    if (bWin == true) {
      cout << "숫자를 모두 맞췄습니다." << endl;
      break;
    }

    cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : \n";
    // getch 함수는 문자 1개를 입력받는 함수이다. 이 함수는 Enter 를 치지 않더라도
    // 문자를 누르는 순간 바로 그 문자를 반환하고 종료된다.
    char cInput = getch();

    if (cInput == 'q' || cInput == 'Q') break;
    
    switch (cInput) {
      case 'w':
      case 'W':
        // 가장 윗줄일 때는 w를 눌러도 위로 올라가서는 안된다.
        if (iStarIndex > 4) {
        // 별이 있는 위치에서 바로 위에 있는 값을 넣어준다
        iNumber[iStarIndex] = iNumber[iStarIndex - 5];
        // 위의 위치에 별을 넣어주어서 2개의 값을 서로 교체한다.
        iNumber[iStarIndex - 5] = INT_MAX;
        // 별이 한 칸 위로 올라갔으므로 한 칸 위의 인덱스로 만들어준다.
        iStarIndex -= 5; 
        }
        break;
      case 's':
      case 'S':
        if (iStarIndex < 20) { // 제일 아랫줄 인덱스가 20 ~ 24
        iNumber[iStarIndex] = iNumber[iStarIndex + 5];
        iNumber[iStarIndex + 5] = INT_MAX;
        iStarIndex += 5;
        }
        break;
      case 'a':
      case 'A':
        if (iStarIndex % 5 != 0) { 
        iNumber[iStarIndex] = iNumber[iStarIndex - 1];
        iNumber[iStarIndex - 1] = INT_MAX;
        --iStarIndex;
        }
        break;

      case 'd':
      case 'D':
        if (iStarIndex % 5 != 4) {
        iNumber[iStarIndex] = iNumber[iStarIndex + 1];
        iNumber[iStarIndex + 1] = INT_MAX;
        ++iStarIndex;
        }
        break;
    }
  }
  return 0;
}