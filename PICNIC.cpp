#include <iostream>
using namespace std;
int n, m;
bool isFriend[10][10];
bool isPaired[10];

int counterPair(bool taken[10]);

int main()
{
    int i;
    cin >> i;
    for(int a=0; a<i; a++)
    {
        
        int f[100];
        cin >> n >> m;
        //친구 쌍 input
        for(int b=0; b<m*2; b++)
        {
            cin >> f[b];
        }
        //isFriend 초기화
        for(int d=0; d<10; d++)
        {
            for(int e=0; e<10; e++)
            {   
                isFriend[d][e]=false;
            }
        }
        //isFriend 설정
        for(int c=0; c<m*2; c+=2)
        {
            isFriend[f[c]][f[c+1]] = true;
            isFriend[f[c+1]][f[c]] = true;  //순서는 상관 없으므로 역순서도 true로 설정
        }
        //isPaired 초기화
        for(int k=0; k<10; k++)
        {
            isPaired[k]=false;
        }

        cout << counterPair(isPaired);
    }
}

int counterPair(bool taken[10])
{
    //가장 빠른 번호의 짝이 없는 학생 설정
    int firstfree = -1;
    for(int i=0; i<n; i++)
    {
        if(!taken[i])
        {
            firstfree = i;
            break;
        }
    }
    if(firstfree == -1) return 1;
    
    int ret = 0;
    //짝 지을 수 있는 case마다 짝을 짓고, 하위 함수에서 짝이 완성되면 1반환, 그렇지 않으면 0반환하여 합함
    for(int pairWith = firstfree+1; pairWith<n; pairWith++)
    {
        if(!taken[pairWith] && isFriend[firstfree][pairWith])
        {
            taken[firstfree] = taken[pairWith] = true;
            ret += counterPair(taken);
            taken[firstfree] = taken[pairWith] = false;
        }
    }
    return ret;
}