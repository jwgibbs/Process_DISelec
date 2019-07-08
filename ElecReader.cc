#include "ElecReader.h"

ElecReader::ElecReader(string inFile, int targMass)
{
    rootfile = new TFile(inFile.c_str(),"READ");
    tree = (TTree*)rootfile->Get("ntuple_data");
//    b_part = tree->GetBranch("ntuple_data");
    l_targtype = tree->GetLeaf("TargType");
    l_q2 = tree->GetLeaf("Q2");
    l_nu = tree->GetLeaf("Nu");
    l_w = tree->GetLeaf("W");
    l_sector = tree->GetLeaf("sector");
    l_xb = tree->GetLeaf("Xb");
    l_x = tree->GetLeaf("X");
    l_y = tree->GetLeaf("Y");
    l_z = tree->GetLeaf("Z");
    l_uc = tree->GetLeaf("UC");
    l_vc = tree->GetLeaf("VC");
    l_wc = tree->GetLeaf("WC");
    l_vc_rd_c = tree->GetLeaf("VC_RD_C");
    l_vc_rd_fe = tree->GetLeaf("VC_RD_Fe");
    l_vc_rd_pb = tree->GetLeaf("VC_RD_Pb");
    l_xc = tree->GetLeaf("XC");
    l_yc = tree->GetLeaf("YC");
    l_zc = tree->GetLeaf("ZC");
    l_vc_tm_c = tree->GetLeaf("VC_TM_C");
    l_vc_tm_fe = tree->GetLeaf("VC_TM_Fe");
    l_vc_tm_pb = tree->GetLeaf("VC_TM_Pb");
    l_xec = tree->GetLeaf("XEC");
    l_yec = tree->GetLeaf("YEC");
    l_zec = tree->GetLeaf("ZEC");
    l_nphe = tree->GetLeaf("Nphe");
    l_deltat = tree->GetLeaf("DeltaT");
    l_ecin = tree->GetLeaf("Ein");
    l_ecout = tree->GetLeaf("Eout");
    l_p = tree->GetLeaf("P");

    TargetLabel.push_back("NoTarget");
    TargetLabel.push_back("LD2");
    TargetLabel.push_back("Nuc");

    TargetIndex.push_back(0);
    TargetIndex.push_back(1);
    TargetIndex.push_back(2);

    RangeLD2.push_back(-31.80);
    RangeLD2.push_back(-28.40);

    TargetMass = targMass; // set target mass

    switch(targMass){
      case 12:
        RangeNuc.push_back(-25.33);
        RangeNuc.push_back(-24.10);
        break;
      case 56:
        RangeNuc.push_back(-25.65);
        RangeNuc.push_back(-24.26);
        break;
      case 208:
        RangeNuc.push_back(-25.54);
        RangeNuc.push_back(-24.36);
        break;
      default:
          cout<<"????? Unknown solid target "<<targMass<<" ?????"<<endl;
          exit(0);
          break;
    }

    RangeElecMom.push_back(0.64); // Lower limit on e- momentum (in GeV)
    RangeElecMom.push_back(1000.0); // Upper limit on e- momentum (in GeV)

    RangeECu.push_back(40); // Lower limit on EC U-view (in cm)
    RangeECu.push_back(400); // Upper limit on EC U-view (in cm)

    RangeECv.push_back(0); // Lower limit on EC V-view (in cm)
    RangeECv.push_back(360); // Upper limit on EC V-view (in cm)

    RangeECw.push_back(0); // Lower limit on EC W-view (in cm)
    RangeECw.push_back(390); // Upper limit on EC W-view (in cm)

    RangeECin.push_back(0.06); // Lower limit on EC inner energy (in GeV)
    RangeECin.push_back(10.0); // Upper limit on EC inner energy (in GeV)

    RangeCCnphe.push_back(28); // Lower limit on CC num. photo-electrons
    RangeCCnphe.push_back(9999); // Upper limit on CC num. photo-electrons

    double dtCentroid = 0.0;
    double dtWidth = 0.6;
    double dtNsigmas = 3.0;
    double dtLo = dtCentroid - dtNsigmas*dtWidth;
    double dtHi = dtCentroid + dtNsigmas*dtWidth;
    Range_dtECSC.push_back(dtLo); // Lower limit on time difference between EC and SC (in ns)
    Range_dtECSC.push_back(dtHi); // Upper limit on time difference between EC and SC (in ns)

    EC_SamplingFrac_C[0][0] = 0.226726; EC_SamplingFrac_C[0][1] = 0.0379557; EC_SamplingFrac_C[0][2] = -0.00855326; EC_SamplingFrac_C[0][3] = 7.27022e-09; EC_SamplingFrac_C[0][4] = 0.0370079;
    EC_SamplingFrac_C[1][0] = 0.222333; EC_SamplingFrac_C[1][1] = 0.0581705; EC_SamplingFrac_C[1][2] = -0.0131283; EC_SamplingFrac_C[1][3] = 3.12094e-12; EC_SamplingFrac_C[1][4] = 0.0413565;
    EC_SamplingFrac_C[2][0] = 0.245212; EC_SamplingFrac_C[2][1] = 0.0213835; EC_SamplingFrac_C[2][2] = -0.00277372; EC_SamplingFrac_C[2][3] = 8.27916e-08; EC_SamplingFrac_C[2][4] = 0.0426498;
    EC_SamplingFrac_C[3][0] = 0.238399; EC_SamplingFrac_C[3][1] = 0.0301926; EC_SamplingFrac_C[3][2] = -0.00720393; EC_SamplingFrac_C[3][3] = -3.81029e-09; EC_SamplingFrac_C[3][4] = 0.0309331;
    EC_SamplingFrac_C[4][0] = 0.241834; EC_SamplingFrac_C[4][1] = 0.0442975; EC_SamplingFrac_C[4][2] = -0.0105584; EC_SamplingFrac_C[4][3] = 9.74651e-09; EC_SamplingFrac_C[4][4] = 0.0303602;
    EC_SamplingFrac_C[5][0] = 0.245868; EC_SamplingFrac_C[5][1] = 0.0545128; EC_SamplingFrac_C[5][2] = -0.0149168; EC_SamplingFrac_C[5][3] = 1.43097e-08; EC_SamplingFrac_C[5][4] = 0.0483305;

    EC_SamplingFrac_Fe[0][0] = 2.22E-1; EC_SamplingFrac_Fe[0][1] = 2.23E-2; EC_SamplingFrac_Fe[0][2] = -2.41E-3; EC_SamplingFrac_Fe[0][3] = 9.23E-3; EC_SamplingFrac_Fe[0][4] = 2.98E-2;
    EC_SamplingFrac_Fe[1][0] = 2.34E-1; EC_SamplingFrac_Fe[1][1] = 1.95E-2; EC_SamplingFrac_Fe[1][2] = -2.08E-3; EC_SamplingFrac_Fe[1][3] = 8.66E-3; EC_SamplingFrac_Fe[1][4] = 3.09E-2;
    EC_SamplingFrac_Fe[2][0] = 2.52E-1; EC_SamplingFrac_Fe[2][1] = 2.42E-2; EC_SamplingFrac_Fe[2][2] = -3.39E-3; EC_SamplingFrac_Fe[2][3] = 1.08E-2; EC_SamplingFrac_Fe[2][4] = 2.64E-2;
    EC_SamplingFrac_Fe[3][0] = 2.51E-1; EC_SamplingFrac_Fe[3][1] = 2.08E-2; EC_SamplingFrac_Fe[3][2] = -3.27E-3; EC_SamplingFrac_Fe[3][3] = 7.22E-3; EC_SamplingFrac_Fe[3][4] = 2.98E-2;
    EC_SamplingFrac_Fe[4][0] = 2.72E-1; EC_SamplingFrac_Fe[4][1] = 1.18E-2; EC_SamplingFrac_Fe[4][2] = -1.87E-3; EC_SamplingFrac_Fe[4][3] = 1.84E-2; EC_SamplingFrac_Fe[4][4] = 3.48E-2;
    EC_SamplingFrac_Fe[5][0] = 2.52E-1; EC_SamplingFrac_Fe[5][1] = 2.28E-2; EC_SamplingFrac_Fe[5][2] = -3.11E-3; EC_SamplingFrac_Fe[5][3] = 4.11E-3; EC_SamplingFrac_Fe[5][4] = 3.55E-2;

    EC_SamplingFrac_Pb[0][0] = 2.53E-1; EC_SamplingFrac_Pb[0][1] = 1.38E-2; EC_SamplingFrac_Pb[0][2] = -1.40E-3; EC_SamplingFrac_Pb[0][3] = 7.67E-3; EC_SamplingFrac_Pb[0][4] = 3.54E-2;
    EC_SamplingFrac_Pb[1][0] = 2.49E-1; EC_SamplingFrac_Pb[1][1] = 1.47E-2; EC_SamplingFrac_Pb[1][2] = -1.49E-3; EC_SamplingFrac_Pb[1][3] = 7.53E-3; EC_SamplingFrac_Pb[1][4] = 3.38E-2;
    EC_SamplingFrac_Pb[2][0] = 2.54E-1; EC_SamplingFrac_Pb[2][1] = 2.26E-2; EC_SamplingFrac_Pb[2][2] = -3.05E-3; EC_SamplingFrac_Pb[2][3] = 8.13E-3; EC_SamplingFrac_Pb[2][4] = 2.77E-2;
    EC_SamplingFrac_Pb[3][0] = 2.55E-1; EC_SamplingFrac_Pb[3][1] = 1.90E-2; EC_SamplingFrac_Pb[3][2] = -3.05E-3; EC_SamplingFrac_Pb[3][3] = 7.20E-3; EC_SamplingFrac_Pb[3][4] = 3.04E-2;
    EC_SamplingFrac_Pb[4][0] = 2.76E-1; EC_SamplingFrac_Pb[4][1] = 1.11E-2; EC_SamplingFrac_Pb[4][2] = -1.76E-3; EC_SamplingFrac_Pb[4][3] = 1.81E-2; EC_SamplingFrac_Pb[4][4] = 3.53E-2;
    EC_SamplingFrac_Pb[5][0] = 2.62E-1; EC_SamplingFrac_Pb[5][1] = 1.92E-2; EC_SamplingFrac_Pb[5][2] = -2.62E-3; EC_SamplingFrac_Pb[5][3] = 1.99E-3; EC_SamplingFrac_Pb[5][4] = 3.76E-2;
}

void ElecReader::ReadEntry(int num)
{
    tree->GetEntry(num);
}

float ElecReader::Get_ECtot()
{
    float ECtot;
    ECtot = this->Get_ECin() + this->Get_ECout();
    return ECtot;
}

TVector3 ElecReader::GetVertex()
{
    TVector3 Vect;
    Vect.SetXYZ(this->Get_X(),this->Get_Y(),this->Get_Z());
    return Vect;
}

TVector3 ElecReader::GetVertexCorr()
{
    TVector3 Vect;
    Vect.SetXYZ(this->Get_XC(),this->Get_YC(),this->Get_ZC());
    return Vect;
}

// Return the CLAS eg2 target index from vertex Z.
//
// Return 0 = outside target limits, 1 = liquid deuterium, 2 = nuclear
// z must be given in cm
//
int ElecReader::Get_TargType_Corr()
{
    int ret = 0; // init the return variable
    double z = this->Get_ZC();

    if (z >= this->Get_LD2_lo() && z < this->Get_LD2_hi()) {
        ret = TargetIndex[1]; // deuterium target
    } else if (z >= this->Get_Nuc_lo() && z < this->Get_Nuc_hi()) {
        ret = TargetIndex[2]; // nuclear target
    } else {
        ret = TargetIndex[0]; // no target
    }

    return ret;
}

double ElecReader::Get_EC_SamplingFraction(int coeff, int sector, int targMass)
{
    double ret = 0.0;

    if(sector>=1 && sector<=6){ //check that the sector is between 1 and 6
        if(coeff>=0 && coeff<5){
            switch (targMass){
                case 12: ret = this->EC_SamplingFrac_C[sector-1][coeff]; break;
                case 56: ret = this->EC_SamplingFrac_Fe[sector-1][coeff]; break;
                case 208: ret = this->EC_SamplingFrac_Pb[sector-1][coeff]; break;
                default:
                    cout<<"ElecReader::Get_EC_SamplingFraction: Target Mass "<< targMass <<" is unknown."<<endl;
                    ret = 0.0;
                    break;
            }
        }
        else{
            cout<<"ElecReader::Get_EC_SamplingFraction: Coefficient "<<coeff<<" is out of range."<<endl;
        }
    }
    else{
        cout<<"ElecReader::Get_EC_SamplingFraction: Sector "<<sector<<" is out of range."<<endl;
    }
    return ret;
}

// check the cut on electron EC inner energy
bool ElecReader::Cut_ElecECoverP()
{
    bool ret = false; // initialize to false

    float mom = this->Get_P();
    int sector = this->Get_Sector();
    float ectot = this->Get_ECtot();
    int tmass = this->Get_TargetMass();

    double a = this->Get_EC_SamplingFraction(0,sector,tmass);
    double b = this->Get_EC_SamplingFraction(1,sector,tmass);
    double c = this->Get_EC_SamplingFraction(2,sector,tmass);
    double d = this->Get_EC_SamplingFraction(3,sector,tmass);
    double f = this->Get_EC_SamplingFraction(4,sector,tmass);

    double centroid = a + b*mom + c*mom*mom;
    double sigma = sqrt(d*d + f*f/sqrt(mom));
    double Nsigma = 2.5;

    double diff = fabs(ectot/mom - centroid);

    ret = (diff < Nsigma*sigma) ? true : false;

    return ret;
}

bool ElecReader::Get_ElectronCuts()
{
  bool ret = false;
  bool PCut = (this->Get_P() >= this->Get_ElecMom_lo() && this->Get_P() < this->Get_ElecMom_hi()) ? true : false;
  bool NpheCut = (this->Get_Nphe() >= this->Get_ElecCCnphe_lo() && this->Get_Nphe() < this->Get_ElecCCnphe_hi()) ? true : false;
  bool ECinCut = (this->Get_ECin() >= this->Get_ElecECin_lo() && this->Get_ECin() < this->Get_ElecECin_hi()) ? true : false;
  bool ECuCut = (this->Get_UC() >= this->Get_ElecECu_lo() && this->Get_UC() < this->Get_ElecECu_hi()) ? true : false;
  bool ECvCut = (this->Get_VC() >= this->Get_ElecECv_lo() && this->Get_VC() < this->Get_ElecECv_hi()) ? true : false;
  bool ECwCut = (this->Get_WC() >= this->Get_ElecECw_lo() && this->Get_WC() < this->Get_ElecECw_hi()) ? true : false;
  bool DtCut = (this->Get_DeltaT() >= this->Get_Elec_dtECSC_lo() && this->Get_DeltaT() < this->Get_Elec_dtECSC_hi()) ? true : false;
  bool ECPCut = Cut_ElecECoverP();

  ret = PCut && NpheCut && ECinCut && ECuCut && ECvCut && ECwCut && DtCut && ECPCut;
  return ret;
}
