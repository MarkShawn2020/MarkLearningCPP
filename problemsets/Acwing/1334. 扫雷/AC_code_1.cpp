#include "cstdio"
#include "vector"

using namespace std;


#define maxn 1005

struct Point{
    int x;
    int y;
    bool operator < (const Point &b) const
    {
        if(x==b.x)
            return y<b.y;
        return x<b.x;
    }
};


int n,m;
char grid[maxn][maxn];
int check[maxn][maxn];  // 是否已经被seep/check（更新炸弹数）
int cnt[maxn][maxn];    // 炸弹数
int flag[maxn][maxn];

int ok;                 // number of all cells
int tol;                // number of swept cells
int step;               // number of steps
int boom;
vector<Point> record;   // record history


const int adjust[8][2] {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool sweep(int x,int y)             // false是指爆炸
{
    if(x<=0 || x>n || y<=0 || y>m)  // 用这种方法免去了循环中的数组越界判断，高！（参数与结构体解耦！）
        return true;
    if(grid[x][y]=='*')
    {
        printf("boom\n");
        printf("game over\n");
        return false;
    }
    int sum=0;                      // sum 是周围的炸弹数
    for(auto i : adjust)
    {
        int xx = x + i[0];
        int yy = y + i[1];
        if(xx<=0 || xx>n || y<=0 || y>m)
            continue;
        if(grid[xx][yy]=='*')
            sum+=1;
    }
    check[x][y]=1;
    cnt[x][y]=sum;                  // sweep 过程中更新炸弹数！！！
    Point tmp{};
    tmp.x=x;
    tmp.y=y;
    record.push_back(tmp);
    if(sum!=0)  return true;        // 炸弹数不等于0，直接返回

    for (auto i : adjust) {
        int xx = x + i[0];
        int yy = y + i[1];
        if (xx <= 0 || xx > n || y <= 0 || y > m) continue;
        if (flag[xx][yy] == 1) flag[xx][yy] = 0;
        if (check[xx][yy] == 1) continue;
        if (!sweep(xx, yy)) return false;
    }
    return true;

}


bool dsweep(int x,int y,int &f)
{
    int sum=0;
    for(auto i : adjust)
    {
        int xx = x + i[0];
        int yy = y + i[1];
        if(xx<=0 || xx>n || y<=0 || y>m)
            continue;
        if(flag[xx][yy]==1)
            sum++;
    }

    if(cnt[x][y]==0 || cnt[x][y]!=sum)
    {
        printf("failed\n");
        f=1;
        return true;
    }


    for(auto i : adjust)
    {
        int xx = x + i[0];
        int yy = y + i[1];
        if(xx<=0 || xx>n || y<=0 || y>m)
            continue;
        if(flag[xx][yy]==1)
            continue;
        if(check[xx][yy]==1)
            continue;
        if(!sweep(xx,yy))
            return false;
    }
    return true;
}

int run()
{
    char op[10];
    int x,y;
    while(true)
    {
        if(tol == ok-boom)                  //  在下一个循环的入口判断是否结束，高啊！！！
        {
            printf("finish\n");
            printf("total step %d\n",step);
            return 0;
        }
        scanf("%s",op);
        if(op[0]=='Q')
        {
            printf("give up\n");
            printf("total step %d\n",step);
            return 0;
        }
        else if(op[0]=='F')
        {
            step+=1;
            scanf("%d%d",&x,&y);
            if(check[x][y])
            {
                printf("swept\n");
                continue;
            }
            if(flag[x][y]==1)
            {
                flag[x][y]=0;
                printf("cancelled\n");
            }

            else
            {
                flag[x][y]=1;
                printf("success\n");
            }

        }
        else if(op[0]=='S')
        {
            step+=1;
            record.clear();         // 清空之前的访问记录
            scanf("%d%d",&x,&y);
            if(check[x][y]==1)
                printf("swept\n");
            else if(flag[x][y]==1)
                printf("flagged\n");
            else
            {
                if(!sweep(x,y))
                {
                    printf("total step %d\n",step);
                    return 0;
                }
                printf("%d cell(s) detected\n", (int)record.size());
                tol+=record.size(); // ��¼��̽������Ŀ
                sort(record.begin(),record.end());
                for(int i=0;i<record.size();i++)
                    printf("%d %d %d\n",record[i].x,record[i].y,cnt[record[i].x][record[i].y]);
            }
        }
        else if(op[0]=='D')
        {
            step+=1;
            record.clear();
            scanf("%d%d",&x,&y);
            if(check[x][y]==0)
            {
                printf("not swept\n");
                continue;
            }
            int f=0;
            if(!dsweep(x,y,f))
            {
                printf("total step %d\n",step);
                return 0;
            }
            tol+=record.size();
            if(record.size()!=0)
            {
                printf("%d cell(s) detected\n", (int)record.size());
                sort(record.begin(),record.end());
                for(int i=0;i<record.size();i++)
                    printf("%d %d %d\n",record[i].x,record[i].y,cnt[record[i].x][record[i].y]);
            }
            else if(f!=1)
            {
                printf("no cell detected\n");
            }

        }

    }

}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/1334. 扫雷/case3.txt", "r", stdin);
    clock_t start = clock();

    scanf("%d%d",&n,&m);
    ok=n*m;
    for(int i=1;i<=n;i++)
        scanf("%s",grid[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(grid[i][j]=='*')
                boom+=1;

    run();

    clock_t end = clock();
    printf("\ntime: %.4f ms", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

    return 0;

}


