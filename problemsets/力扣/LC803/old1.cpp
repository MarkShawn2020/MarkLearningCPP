//
// Created by 南川 on 2021/1/16.
//

#ifndef MARKLEARNINGCPP_OLD_H
#define MARKLEARNINGCPP_OLD_H

#endif //MARKLEARNINGCPP_OLD_H

void dropTraverse(vector<vector<int>> & grid, array<array<Deg, G>, G> & ds, int N, int M, int x, int y, InDir inDir, int & k){
    /**
     * 邻接点的入度为0，则++k（消掉）
     * 邻接点的入度为1，则反向更新依赖链（--in）
     */
    // x-1，y（上方）
    if(x>0 && ds[x-1][y].down && inDir!=UP){
        ds[x-1][y].down = false;
        int kAdjIn = --ds[x-1][y].in;
        if(kAdjIn == 0) {
            cout << "(x,y)=(" << x << "," << y << ")" << endl;
        }

        if(kAdjIn<2)
            dropTraverse(grid, ds, N, M, x-1, y, DOWN, k+=1-kAdjIn);
    }
    // x+1, y（下方）
    if(x<N-1 && ds[x+1][y].up && inDir!=DOWN){
        ds[x+1][y].up = false;
        int kAdjIn = --ds[x+1][y].in;
        if(kAdjIn == 0) {
            cout << "(x,y)=(" << x << "," << y << ")" << endl;
        }

        if(kAdjIn<2)
            dropTraverse(grid, ds, N, M, x+1, y, UP, k+=1-kAdjIn);
    }
    // x, y-1（左方）
    if(y>0 && ds[x][y-1].right && inDir!=LEFT) {
        ds[x][y-1].right = false;
        int kAdjIn = --ds[x][y-1].in;
        if(kAdjIn == 0) {
            cout << "(x,y)=(" << x << "," << y << ")" << endl;
        }

        if(kAdjIn<2)
            dropTraverse(grid, ds, N, M, x, y-1, RIGHT, k+=1-kAdjIn);
    }
    // x, y+1 （右方）
    if(y<M-1 && ds[x][y+1].left && inDir!=RIGHT){
        ds[x][y+1].left = false;
        int kAdjIn = --ds[x][y+1].in;
        if(kAdjIn == 0) {
            cout << "(x,y)=(" << x << "," << y << ")" << endl;
        }

        if(kAdjIn<2)
            dropTraverse(grid, ds, N, M, x, y+1, LEFT, k+=1-kAdjIn);
    }
}
