#include <stdio.h>
#include <math.h>
#include <list>
#include <stdbool.h>
#include <vector>

using namespace std;

typedef struct Position Position;
typedef struct Map Map;

struct Position {
    int x,y;
};

struct Map {
    Position currPos;
    char value;
    bool isVisited;
    Map *before;
};

Map sMap[10][15];

char MapChar[10][16] = {
"###############",
"# ###         #",
"#   E         #",
"###       #####",
"##    #########",
"#    ##########",
"###           #",
"########    ###",
"#            S#",
"###############"
};

Position startPos, endPos;

void buildMap() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            char curr = MapChar[i][j];
            Position currPos;
            currPos.x = j;
            currPos.y = i;

            if(curr == 'S') {
                startPos = currPos;
            } 

            if(curr == 'E') {
                endPos = currPos;
            }

            sMap[i][j].before = NULL;
            sMap[i][j].currPos = currPos;
            sMap[i][j].isVisited = false;
            sMap[i][j].value = curr;
        }
    }   
}

void printMap() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            printf("%c", sMap[i][j].value);
        }
        puts(" ");
    }
}

//Atas kanan bawah Kiri
int moveY[4] = {-1, 0, 1, 0};
int moveX[4] = {0, 1, 0, -1};

void solve() {
    vector<Map*> listMap;
    listMap.push_back(&sMap[startPos.y][startPos.x]);
    Map* currMap;

    while(!listMap.empty()) {
        currMap = listMap[0];
        listMap.erase(listMap.begin());
        currMap->isVisited = true;

        if(currMap->value == 'E') break;

        for(int i=0; i<4;i++) {
            Map* newMap = &sMap[currMap->currPos.y + moveY[i]][currMap->currPos.x + moveX[i]];
            bool inList = false;

            for(int j = 0; j < listMap.size(); j++) {
                if(listMap[j] == newMap) {
                    inList = true;
                }
            }

            if(inList || newMap->value == '#' || newMap->isVisited) {
                continue;
            }

            listMap.push_back(newMap);
            newMap->before = currMap;
        }
    }

    while(currMap) {
        if(currMap->value != 'S' && currMap->value != 'E') currMap->value = '*';
        currMap = currMap->before;
    }

    printMap();
}

int main() {
    buildMap();
    solve();
    return 0;
}