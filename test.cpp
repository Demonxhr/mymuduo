#include <vector>
#include <queue>
#include <iostream>

struct OpenPoint{
    int x;
    int y;
    int cost;                 // 耗费值
    int pred;                 // 预测值
    OpenPoint* father;        // 父节点
    OpenPoint() = default;
    OpenPoint(int pX,int pY, int endX, int endY, int c, OpenPoint* fatherp) : x(pX),y(pY),cost(c), father(fatherp) {
        //相对位移x,y取绝对值
        int relativeX = std::abs(endX - pX);
        int relativeY = std::abs(endY - pY);
        //x,y偏移值n
        int n = relativeX - relativeY;
        //预测值pred = (max–n)*14+n*10+c
        pred = std::max(relativeX, relativeY) * 14 - std::abs(n) * 4 + c;
    }
};

//比较器，用以优先队列的指针类型比较
struct OpenPointPtrCompare {
    bool operator()(OpenPoint* a, OpenPoint* b) {
        return a->pred > b->pred;
    }
};
std::priority_queue<OpenPoint*, std::vector<OpenPoint*>, OpenPointPtrCompare> openlist;

std::vector<OpenPoint*> aa(20000);
int main(){
    
    for(int i = 0; i<20000;++i)
    {
        std::cout << i << std::endl;
        //openlist.push(new OpenPoint(1,1,1,1,1,nullptr));
        aa.push_back(new OpenPoint(1,1,1,1,1,nullptr));
    }

}