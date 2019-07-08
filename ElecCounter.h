#ifndef ElecCounter_H
#define ElecCounter_H
#include <vector>
#include <string>

using namespace std;

class ElecCounter
{
    vector<string> CtrLabel;
    vector<int> CtrStats;
public:
    ElecCounter();
    void Init();
    void Print();
    int Get_nCtrLabel() {return CtrLabel.size();};
    string Get_CtrLabel(int num) {return CtrLabel[num];};
    int Get_CtrStats(int num) {return CtrStats[num];};
    void Increment(string label);
};
#endif
