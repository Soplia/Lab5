#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int DATH = 0;
const int ALIVE = 1;
//const int maxn = 50;
const int maxr = 100,maxl = 100;// maxsize of row & column for map
const int dx[] = { -1,-1,-1,0,1,1,1,0 }, dy[] = { -1,0,1,1,1,0,-1,-1 };

int map[maxr][maxl];
int newmap[maxr][maxl];
int m, n; // row-size & column-size of map
int general = 0;

//初始化，生成随机数（无法避免随机数的浪费）
void rule1()
{
    srand((unsigned int)time(NULL));
    for(int i = 0;i < m;i++)
        for (int j = 0; j < n; j++)
            map[i][j] = rand() % 2;        //假设约n/2
}

//"脉冲星"，周期为3
void rule2()
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            map[i][j] = 0;
    map[4][2] = map[5][2] = map[6][2] = 1;
    map[4][7] = map[5][7] = map[6][7] = 1;
    map[2][4] = map[2][5] = map[2][6] = 1;
    map[7][4] = map[7][5] = map[7][6] = 1;
    
    map[10][2] = map[11][2] = map[12][2] = 1;
    map[10][7] = map[11][7] = map[12][7] = 1;
    map[9][4] = map[9][5] = map[9][6] = 1;
    map[14][4] = map[14][5] = map[14][6] = 1;
    
    map[4][9] = map[5][9] = map[6][9] = 1;
    map[4][14] = map[5][14] = map[6][14] = 1;
    map[2][10] = map[2][11] = map[2][12] = 1;
    map[7][10] = map[7][11] = map[7][12] = 1;
    
    map[10][9] = map[11][9] = map[12][9] = 1;
    map[10][14] = map[11][14] = map[12][14] = 1;
    map[9][10] = map[9][11] = map[9][12] = 1;
    map[14][10] = map[14][11] = map[14][12] = 1;
}

//计算(x,y)周围存活细胞的个数
int neighbor_num(int x, int y,int map[][maxl])
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && map[nx][ny])  cnt++;
    }
    return cnt;
}

//打印第i代的结果
void print_general()
{
    printf("第%d代：\n", general);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            if (map[i][j])  printf("■");
            else printf("□");
        printf("\n");
    }
}

//将map复制到tmp_map
void copy_map(int map[][maxl], int tmp_map[][maxl])
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            tmp_map[i][j] = map[i][j];
}

//得到下一代
void iteration()
{
    int tmp_map[maxr][maxl];
    copy_map(map, tmp_map);        //保存之前图像，使得当前元素状态的改变还是基于之前的地图，而不是被修改了的
    for(int i = 0;i < m;i++)
        for (int j = 0; j < n; j++)
        {
            int cnt = neighbor_num(i, j, tmp_map);
            switch (cnt)
            {
                case 2: continue;
                case 3: map[i][j] = ALIVE; break;
                default: map[i][j] = DATH; break;
            }
        }
    
    general++;
    print_general();
}

int main()
{
    scanf("%d%d", &m, &n);
    rule1();
    print_general();
    while (1)
        iteration();
    
    return 0;
}
