//
// Created by 南川 on 2021/2/9.
//
#include "vector"
#include "map"
#include "tuple"
#include "iostream"
using namespace std;

class BiMap {
    typedef map<int,int>::iterator Miii;
private:
    int k, K;
    map<int, int> mp;                               // ind -> val
    vector<Miii> front;   // val -> latest_ind (opt: the iterator of ind -> val)
public:
    int ans = 0;
    explicit BiMap(int K): k(0), K(K), front(20){}
    void insert(int id, int val) {
        front[val] = mp.insert({id, val}).first;
        mp.insert({id+1, val+1});
        // cout << "id: " << id << ", val: " << val << endl;
        // cout << "id: " << id << ", val: " << val << endl;
        // if(!front[val]->first) front[val] = mp.insert({id, val}).first, ++k;
        // else
        //     mp.erase(front[val]), front[val] = mp.insert({id, val}).first;
        // if(k > K)
        //     front[mp.begin()->second] = mp.end(), mp.erase(mp.begin()), --k;
        // if(k == K)
        //     ans += next(mp.begin())->first - mp.begin()->first;
    }
};

int main()
{
    BiMap b(10);
    b.insert(1,3);
}