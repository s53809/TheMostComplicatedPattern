#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

vector<int> patternSequence;
vector<vector<bool>> pattern;
vector<pair<float, bool>> gradient;
vector<pair<int, int>> cornerPyo;

int Gomsa(int N, int yPos, int xPos, int curY, int curX) {
	float guradent;
	if (curX - xPos != 0) {
		guradent = (float)(curY - yPos) / (float)(curX - xPos);
	}
	else { // 기울기 무한대 예외처리
		guradent = -10;
	}
	if (guradent == -0) {
		guradent = 0;
	}
	for (int i = 0; i < gradient.size(); i++) {
		if (guradent == gradient[i].first && gradient[i].second == false) {
			return i;
		}
	}
	return -1;
}

int cornerGomsa(int curY, int curX, int yPos, int xPos) {
	for (int i = 0; i < cornerPyo.size(); i++) {
		if (xPos == cornerPyo[i].first && yPos == cornerPyo[i].second) {
			if (pattern[(curY + yPos) / 2][(curX + xPos) / 2] == true) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	return 0;
}

int showPatternNum(int yPos, int xPos) {
	int stac = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == yPos && j == xPos) {
				return stac;
			}
			else {
				stac++;
			}
		}
	}
}

void makePattern(int N, int yPos, int xPos) {
	if (N == 9) { // N이 9가 된 순간 패턴은 완성해져있다고 판단
		for (int i = 0; i < patternSequence.size(); i++) {
			cout << patternSequence[i];
			if (i != 8) {
				cout << "->";
			}
		}
		cout << "\n\n";
		return;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i != yPos || j != xPos) && (pattern[i][j] == false)) {
				int numberOfgradient = Gomsa(N, i, j, yPos, xPos);
				if (numberOfgradient != -1) {
					if (xPos == 1 && yPos == 1) {
						gradient[numberOfgradient].second = true;
						pattern[i][j] = true;
						patternSequence.push_back(showPatternNum(i, j));
						makePattern(N + 1, i, j);
						gradient[numberOfgradient].second = false;
						pattern[i][j] = false;
						patternSequence.pop_back();
					}
					else {
						bool isCorner = false;
						bool isPossible = false;
						for (int i = 0; i < cornerPyo.size(); i++) {
							if (xPos == cornerPyo[i].first && yPos == cornerPyo[i].second) {
								isCorner = true;
							}
						}
						if (isCorner == false) {
							if (xPos == 1 && yPos == 0 && j == 1 && i == 2) {
								if (pattern[1][1] == true) {
									isPossible = true;
								}
							}
							else if (xPos == 0 && yPos == 1 && j == 2 && i == 1) {
								if (pattern[1][1] == true) {
									isPossible = true;
								}
							}
							else if (xPos == 2 && yPos == 1 && j == 0 && i == 1) {
								if (pattern[1][1] == true) {
									isPossible = true;
								}
							}
							else if (xPos == 1 && yPos == 2 && j == 1 && i == 0) {
								if (pattern[1][1] == true) {
									isPossible = true;
								}
							}
							else {
								isPossible = true;
							}
						}
						else {
							int resultNum = cornerGomsa(yPos, xPos, i, j);
							if (resultNum == 1 || resultNum == 0) {
								isPossible = true;
							}
						}
						if (isPossible == true) {
							gradient[numberOfgradient].second = true;
							pattern[i][j] = true;
							patternSequence.push_back(showPatternNum(i, j));
							makePattern(N + 1, i, j);
							gradient[numberOfgradient].second = false;
							pattern[i][j] = false;
							patternSequence.pop_back();
						}
					}
				}
			}
		}
	}
}

int main() {
	cornerPyo.push_back(make_pair(0, 0));
	cornerPyo.push_back(make_pair(2, 0));
	cornerPyo.push_back(make_pair(0, 2));
	cornerPyo.push_back(make_pair(2, 2));
	gradient.push_back(make_pair(0, false)); // 0
	gradient.push_back(make_pair(1, false)); // 3
	gradient.push_back(make_pair(-1, false)); // 2
	gradient.push_back(make_pair(2, false)); // 5
	gradient.push_back(make_pair(-2, false)); // 4
	gradient.push_back(make_pair(0.5, false)); // 7
	gradient.push_back(make_pair(-0.5, false)); // 6
	gradient.push_back(make_pair(-10, false)); // 1
	pattern.resize(3);
	for (int i = 0; i < 3; i++) {
		pattern[i].resize(3);
		for (int j = 0; j < 3; j++) {
			pattern[i][j] = false;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			patternSequence.push_back(showPatternNum(i, j));
			pattern[i][j] = true;
			makePattern(1, i, j);
			patternSequence.pop_back();
			pattern[i][j] = false;
		}
	}
	cout << "모든 최대복잡패턴 찾기 프로젝트\n제작: 1404 김민서\n아무키나 눌러 종료 . . .\n";
	_getch();
	return 0;
}