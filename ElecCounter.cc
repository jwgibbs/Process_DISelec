#include <cmath>
#include <vector>
#include <string>
#include "ElecCounter.h"
#include <iostream>

ElecCounter::ElecCounter()
{
    CtrLabel.push_back("e-, NoTarget (uncorr. vertex)");
    CtrLabel.push_back("e-, LD2 (uncorr. vertex)");
    CtrLabel.push_back("e-, Nuc (uncorr. vertex)");
    CtrLabel.push_back("e-, NoTarget (corr. vertex)");
    CtrLabel.push_back("e-, LD2 (corr. vertex)");
    CtrLabel.push_back("e-, Nuc (corr. vertex)");
    CtrLabel.push_back("Total Events, No Cuts");
    CtrLabel.push_back("Total Events, e- Cuts");
    this->Init();
}

void ElecCounter::Init()
{
    CtrStats.assign(this->Get_nCtrLabel(),0);
}

void ElecCounter::Increment(string label)
{
    bool ifound = false;

    for(int ii=0; ii<this->Get_nCtrLabel(); ii++){
        if (this->Get_CtrLabel(ii).compare(label)==0) {
            CtrStats[ii]++;
            ifound = true;
        }
    }
    if(!ifound) cout<<"ElecCounter::Increment(), Unknown label "<<label<<endl;
}

void ElecCounter::Print()
{
    int ii;
    cout<<"Statistics Summary"<<endl;
    cout<<"=================="<<endl;
    for(ii=0;ii<this->Get_nCtrLabel();ii++){
        cout << this->Get_CtrLabel(ii) << "\t" << this->Get_CtrStats(ii) << "\t";
        cout << "("<<(float)this->Get_CtrStats(ii)/(float)this->Get_CtrStats(6)<<")"<< endl;
    }
    std::cout << "N[nuc]/N[LD2] (cut on uncorrected Vertex): " << "\t";
    std::cout << (float)this->Get_CtrStats(2)/(float)this->Get_CtrStats(1) << '\n';
    std::cout << "N[nuc]/N[LD2]  (cut on corrected Vertex): " << "\t";
    std::cout << (float)this->Get_CtrStats(5)/(float)this->Get_CtrStats(4) << '\n';
}
