#ifndef HISTMANAGER_H
#define HISTMANAGER_H
#include <vector>
#include <string>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

using namespace std;

class HistManager
{
private:
    static const Int_t MAX_TARGTYPE = 3; // target types (0=unknown, 1=liquid, 2=solid)
    static const Int_t MAX_TARGTYPE_CORR = 3; // target types (0=unknown, 1=liquid, 2=solid)
    static const Int_t MAX_HISTS = MAX_TARGTYPE+MAX_TARGTYPE_CORR + 2;
    int MAX_SECTORS; // max. number of CLAS sectors
    int ID_ELECTRON; // PDG electron id
    double MASS_ELECTRON; // mass of charged pion in GeV/c^2
    double BEAM_ENERGY; // electron beam energy in GeV

    vector<string> Target;

    TH1D *q2[MAX_HISTS];
    TH1D *nu[MAX_HISTS];
    TH1D *elecZ[MAX_HISTS];
    TH1D *elecZC[MAX_HISTS];
    TH2D *X_VS_Y[MAX_HISTS];
    TH2D *XC_VS_YC[MAX_HISTS];
    TH1D *TotalMomentum[MAX_HISTS];
    TH1D *hW[MAX_HISTS];
//    TH1D *z_fracE[MAX_HISTS];
    TH2D *elecZSector[MAX_HISTS];
    TH2D *elecZCSector[MAX_HISTS];

    TH1D *CCnphe[MAX_HISTS];
    TH1D *ECu[MAX_HISTS];
    TH1D *ECv[MAX_HISTS];
    TH1D *ECw[MAX_HISTS];
    TH2D *ECtot_VS_P[MAX_HISTS];
    TH2D *ECtotP_VS_P[MAX_HISTS];
    TH2D *ECin_VS_ECout[MAX_HISTS];

public:
    HistManager();
    void BookHist();
    void WriteHist(string RootFile);

    int Get_nTarget() {return Target.size();};
	  string Get_Target(int num) {return Target[num];};

    TH1D* GetQ2(int index) { return q2[index]; };
    TH1D* GetNu(int index) { return nu[index]; };
    TH1D* GetElecZ(int index) { return elecZ[index]; };
    TH1D* GetElecZC(int index) { return elecZC[index]; };
    TH2D* GetX_VS_Y(int index) { return X_VS_Y[index]; };
    TH2D* GetXC_VS_YC(int index) { return XC_VS_YC[index]; };
    TH1D* GetTotalMomentum(int index) { return TotalMomentum[index]; };
    TH1D* GetCCnphe(int index) { return CCnphe[index]; };
    TH1D* GetECu(int index) { return ECu[index]; };
    TH1D* GetECv(int index) { return ECv[index]; };
    TH1D* GetECw(int index) { return ECw[index]; };
    TH2D* GetECtot_VS_P(int index) { return ECtot_VS_P[index]; };
    TH2D* GetECtotP_VS_P(int index) { return ECtotP_VS_P[index]; };
    TH2D* GetECin_VS_ECout(int index) { return ECin_VS_ECout[index]; };

    TH1D* GetHW(int index) { return hW[index]; };
//    TH1D* GetZ_fracE(int index) { return z_fracE[index]; };
    TH2D* GetElecZSector(int index) { return elecZSector[index]; };
    TH2D* GetElecZCSector(int index) { return elecZCSector[index]; };

    int GetMAX_TARGTYPE() { return MAX_TARGTYPE; };
    int GetMAX_TARGTYPE_CORR() { return MAX_TARGTYPE_CORR; };
    int GetMAX_SECTORS() { return MAX_SECTORS; };
    int GetID_ELECTRON() { return ID_ELECTRON; };
    double GetMASS_ELECTRON() { return MASS_ELECTRON; };
    double GetBEAM_ENERGY() { return BEAM_ENERGY; };
};
#endif
