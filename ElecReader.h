#ifndef ElecReader_H
#define ElecReader_H
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TLorentzVector.h"

using namespace std;

class ElecReader
{
    TFile *rootfile;
    TTree *tree;
//    TBranch *b_part;
    TLeaf *l_targtype;
    TLeaf *l_q2;
    TLeaf *l_nu;
    TLeaf *l_w;
    TLeaf *l_sector;
    TLeaf *l_xb;
    TLeaf *l_x;
    TLeaf *l_y;
    TLeaf *l_z;
    TLeaf *l_uc;
    TLeaf *l_vc;
    TLeaf *l_wc;
    TLeaf *l_vc_rd_c;
    TLeaf *l_vc_rd_fe;
    TLeaf *l_vc_rd_pb;
    TLeaf *l_xc;
    TLeaf *l_yc;
    TLeaf *l_zc;
    TLeaf *l_vc_tm_c;
    TLeaf *l_vc_tm_fe;
    TLeaf *l_vc_tm_pb;
    TLeaf *l_xec;
    TLeaf *l_yec;
    TLeaf *l_zec;
    TLeaf *l_nphe;
    TLeaf *l_deltat;
    TLeaf *l_ecin;
    TLeaf *l_ecout;
    TLeaf *l_p;

    vector<string> TargetLabel;
    vector<int> TargetIndex;
    vector<double> RangeLD2;
    vector<double> RangeNuc;

    vector<double> RangeElecMom;
    vector<double> RangeECu;
    vector<double> RangeECv;
    vector<double> RangeECw;
    vector<double> RangeECin;
    vector<double> RangeCCnphe;
    vector<double> Range_dtECSC;
    // parameters to calculate the EC sampling fraction of total energy vs P
    double EC_SamplingFrac_C[6][5];
    double EC_SamplingFrac_Fe[6][5];
    double EC_SamplingFrac_Pb[6][5];

    int TargetMass;
public:
    ElecReader(string inFile, int targMass);
    void ReadEntry(int num);
    void Delete_RootFile() {tree->Delete();};
    int Get_Entries() {return tree->GetEntries();};
    int Get_nTargetLabel() {return TargetLabel.size();};
    int Get_nTargetIndex() {return TargetIndex.size();};
    string Get_TargetLabel(int num) {return TargetLabel[num];};
    double Get_LD2_lo() {return RangeLD2[0];};
    double Get_LD2_hi() {return RangeLD2[1];};
    double Get_Nuc_lo() {return RangeNuc[0];};
    double Get_Nuc_hi() {return RangeNuc[1];};
    int Get_TargType_Corr();
    float Get_TargType() {return l_targtype->GetValue();};
    float Get_Q2() {return l_q2->GetValue();};
    float Get_Nu() {return l_nu->GetValue();};
    float Get_W() {return l_w->GetValue();};
    int Get_Sector() {return l_sector->GetValue()+1;};
    float Get_Xb() {return l_xb->GetValue();};
    float Get_X() {return l_x->GetValue();};
    float Get_Y() {return l_y->GetValue();};
    float Get_Z() {return l_z->GetValue();};
    float Get_UC() {return l_uc->GetValue();};
    float Get_VC() {return l_vc->GetValue();};
    float Get_WC() {return l_wc->GetValue();};
    float Get_VC_RD_C() {return l_vc_rd_c->GetValue();};
    float Get_VC_RD_Fe() {return l_vc_rd_fe->GetValue();};
    float Get_VC_RD_Pb() {return l_vc_rd_pb->GetValue();};
    float Get_XC() {return l_xc->GetValue();};
    float Get_YC() {return l_yc->GetValue();};
    float Get_ZC() {return l_zc->GetValue();};
    float Get_VC_TM_C() {return l_vc_tm_c->GetValue();};
    float Get_VC_TM_Fe() {return l_vc_tm_fe->GetValue();};
    float Get_VC_TM_Pb() {return l_vc_tm_pb->GetValue();};
    float Get_XEC() {return l_xec->GetValue();};
    float Get_YEC() {return l_yec->GetValue();};
    float Get_ZEC() {return l_zec->GetValue();};
    float Get_Nphe() {return l_nphe->GetValue();};
    float Get_DeltaT() {return l_deltat->GetValue();};
    float Get_ECin() {return l_ecin->GetValue();};
    float Get_ECout() {return l_ecout->GetValue();};
    float Get_P() {return l_p->GetValue();};

    TVector3 GetVertex();
    TVector3 GetVertexCorr();
    float Get_ECtot();

    double Get_ElecMom_lo() {return RangeElecMom[0];};
    double Get_ElecMom_hi() {return RangeElecMom[1];};
    double Get_ElecECu_lo() {return RangeECu[0];};
    double Get_ElecECu_hi() {return RangeECu[1];};
    double Get_ElecECv_lo() {return RangeECv[0];};
    double Get_ElecECv_hi() {return RangeECv[1];};
    double Get_ElecECw_lo() {return RangeECw[0];};
    double Get_ElecECw_hi() {return RangeECw[1];};
    double Get_ElecECin_lo() {return RangeECin[0];};
    double Get_ElecECin_hi() {return RangeECin[1];};
    double Get_ElecCCnphe_lo() {return RangeCCnphe[0];};
    double Get_ElecCCnphe_hi() {return RangeCCnphe[1];};
    double Get_Elec_dtECSC_lo() {return Range_dtECSC[0];};
    double Get_Elec_dtECSC_hi() {return Range_dtECSC[1];};
    double Get_EC_SamplingFraction(int coeff, int sector, int targMass);
    bool Cut_ElecECoverP();
    int Get_TargetMass() {return TargetMass;};
    bool Get_ElectronCuts();
};
#endif
