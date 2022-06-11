#include <iostream>
#include <cmath>
#include <string>
using namespace std;

string qtree(string::iterator& iter);
void decompress(string::iterator& iter, int x, int y, int size);

string img;
char decom[20][20];
int main()
{
    int tcNum;
    cout << "테스트 케이스 횟수 : ";
    cin >> tcNum;
    for(int i=0; i<tcNum; i++)
    {
        cout << "이미지 입력 : ";
        
        cin >> img;
        const string img2 = img;
        string::iterator it = img.begin();
        cout << qtree(it);
    }
}
//압축 해제 알고리즘
void decompress(string::iterator& iter, int x, int y, int size)
{
    char first = *(iter++);
    if(first =='w' || first =='b')
    {
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size; j++)
            {
                decom[x+i][y+j]=first;
            }
        }
    }
    else
    {
        int half = size/2;
        decompress(iter, x, y, half);
        decompress(iter, x+half, y, half);
        decompress(iter, x, y+half, half);
        decompress(iter, x+half, y+half, half);
    }
}
//압축 코드를 상하로 뒤집은 압축코드 반환
//하위 4개를 뒤집고, 상하를 '교체'하면 전체를 뒤집은 것.
//상하 '교체'란, 12/34 -> 34/12
string qtree(string::iterator& iter)
{
    char head = *(iter++);
    if(head == 'w' || head == 'b')
    {
        return string(1, head);
    }
    //qtree 호출마다 이터레이터 인덱스 증가됨.
    string topLeft = qtree(iter);
    string topRight = qtree(iter);
    string botLeft = qtree(iter);
    string botRight = qtree(iter);
    
    return string("x")+botLeft+botRight+topLeft+topRight;
}