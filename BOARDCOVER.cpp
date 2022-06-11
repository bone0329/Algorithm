#include <iostream>
#include <vector>
using namespace std;

bool checker(vector<vector<int>>& board, int x, int y, int type, int delta);
int cover(vector<vector<int>>& board);

vector<vector<int>> baseboard;

int c, h, w;

int main()
{
    cout << "테스트 케이스 수 : ";
    cin >> c;
    cout << "높이, 너비 : ";
    cin >> h >> w;
    cout << "보드 입력 : " << endl;
    int temp=0;
    vector<int> temp2;
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            cin >> temp;
            temp2.push_back(temp);
        }
        baseboard.push_back(temp2);
        temp2.clear();
    }
    cout << cover(baseboard);
}

const int coverType[4][3][2] = 
{
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1 ,0}, {1, 1}},
    {{0, 0}, {1, 0}, {1,-1}}
};
//가장 왼쪽 상단 빈칸을 기준으로 하면, 가능한 설치 방법은 위 4개 밖에 없음.
//type으로 지정된 방법에 따라 그 방법으로 설치가 가능하면 참 반환.
//지정된 방법이 밖으로 나가거나, 검은 칸을 덮으면 거짓 반환.
//delta값이 1이면 설치 -1이면 삭제.
bool checker(vector<vector<int>>& board, int y, int x, int type, int delta)
{
    bool result = true;
    //설치될 3칸에 대해
    for(int i=0; i<3; ++i)
    {
        const int nx = x + coverType[type][i][1];
        const int ny = y + coverType[type][i][0];
        //칸이 보드 밖으로 나가는지
        if(ny < 0 || ny>=board.size() || nx < 0 || nx >= board[0].size())
        {
            result = false;
        }
        //칸이 검은 칸을 덮는지(delta가 1이고 board가 1인 경우.)
        else if ((board[ny][nx]+=delta)>1)
        {
            result = false;
        }
    }
    return result;
}

int cover(vector<vector<int>>& board)
{
    //가장 왼쪽 상단 빈칸 찾기
    int x = -1, y = -1;
    for(int i=0; i<board.size(); ++i)
    {
        for(int j=0; j<board[i].size(); ++j)
        {
            if(board[i][j]==0)
            {
                x=j;
                y=i;
                break;
            }
        }
        //가장 왼쪽 상단 빈칸을 찾은 경우, 이후 탐색하지 않는다.
        if(y!=-1)break;
    }
    //빈칸이 없는 경우, 다 채워진 것이므로 1 반환
    if(y==-1)return 1;
    int ret = 0;
    //4가지 경우를 모두 확인.
    for(int type = 0; type<4; ++type)
    {
        //현재 방법이 설치 가능하면 재귀함수 호출
        if(checker(board, y, x, type, 1))
        {
            ret += cover(board);
        }
        //다음 방법 확인을 위해 되돌리기
        checker(board, y, x, type, -1);
    }
    return ret;
}