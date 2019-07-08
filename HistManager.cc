#include <vector>
#include <string>
#include "HistManager.h"
#include <iostream>

HistManager::HistManager()
{
    MAX_SECTORS = 6;
    ID_ELECTRON = 11;
    BEAM_ENERGY = 5.014; // 4.5

    Target.push_back("NoTarget");
    Target.push_back("LD2");
    Target.push_back("Nuc");
    Target.push_back("NoTarget_Corr");
    Target.push_back("LD2_Corr");
    Target.push_back("Nuc_Corr");
    Target.push_back("All_NoCuts");
    Target.push_back("All_ElecCuts");
}

//
// BookHist - routine to set up histograms
//
void HistManager::BookHist()
{

    int i;

    char hname[100];
    char htitle[200];

    for(i=0; i<this->Get_nTarget(); i++){
      sprintf(hname,"q2_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"Q^{2}, %s",this->Get_Target(i).c_str());
      q2[i] = new TH1D(hname,htitle, 100, 0., 4.);

      sprintf(hname,"nu_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"\nu, %s",this->Get_Target(i).c_str());
      nu[i] = new TH1D(hname,htitle, 150, 1.5, 4.5);

      sprintf(hname,"elecZ_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"Z Vertex of Electron, %s",this->Get_Target(i).c_str());
	    elecZ[i] = new TH1D(hname,htitle, 300, -40, -20);

      sprintf(hname,"elecZC_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"Z Vertex of Electron, Corrected, %s",this->Get_Target(i).c_str());
 	    elecZC[i] = new TH1D(hname,htitle, 300, -40, -20);

      sprintf(hname,"elecZSector_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"Z Vertex of Electron vs Sector, %s",this->Get_Target(i).c_str());
      elecZSector[i] = new TH2D(hname, htitle, 300, -40, -20, 6, 0.5, 6.5);

      sprintf(hname,"elecZCSector_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"Z Vertex of Electron vs Sector, Corrected, %s",this->Get_Target(i).c_str());
      elecZCSector[i] = new TH2D(hname, htitle, 300, -40, -20, 6, 0.5, 6.5);

      sprintf(hname,"TotalMomentum_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"Total Momentum, %s",this->Get_Target(i).c_str());
	    TotalMomentum[i] = new TH1D(hname,htitle, 500, 0, 5);

      sprintf(hname,"X_VS_Y_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"X Vertex vs Y Vertex, %s",this->Get_Target(i).c_str());
      X_VS_Y[i] = new TH2D(hname,htitle, 100, -0.05, 0.05, 100, -0.05, 0.05);

      sprintf(hname,"XC_VS_YC_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"X Vertex vs Y Vertex, corrected, %s",this->Get_Target(i).c_str());
      XC_VS_YC[i] = new TH2D(hname,htitle, 100, -0.05, 0.05, 100, -0.05, 0.05);

      sprintf(hname,"ECtot_VS_P_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"ECtot vs P, %s",this->Get_Target(i).c_str());
      ECtot_VS_P[i] = new TH2D(hname,htitle, 500, 0, 5, 100, 0, 1.0);

      sprintf(hname,"ECin_VS_ECout_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"ECin vs ECout, %s",this->Get_Target(i).c_str());
      ECin_VS_ECout[i] = new TH2D(hname,htitle, 100, 0, 0.5, 100, 0, 0.25);

      sprintf(hname,"ECtotP_VS_P_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"ECtot/P vs P, %s",this->Get_Target(i).c_str());
      ECtotP_VS_P[i] = new TH2D(hname,htitle, 500, 0, 5, 100, 0, 0.5);

        // particle ID histogram
      sprintf(hname,"CCnphe_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"CC Number of Photo-electrons, %s",this->Get_Target(i).c_str());
      CCnphe[i] = new TH1D(hname,htitle, 200, 0, 400);

      sprintf(hname,"ECu_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"EC U-view, %s",this->Get_Target(i).c_str());
      ECu[i] = new TH1D(hname,htitle, 450, 0, 450);

      sprintf(hname,"ECv_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"EC V-view, %s",this->Get_Target(i).c_str());
      ECv[i] = new TH1D(hname,htitle, 450, 0, 450);

      sprintf(hname,"ECw_%s",this->Get_Target(i).c_str());
      sprintf(htitle,"EC W-view, %s",this->Get_Target(i).c_str());
      ECw[i] = new TH1D(hname,htitle, 450, 0, 450);

	    sprintf(hname,"hW_%s",this->Get_Target(i).c_str());
	    sprintf(htitle,"W of Reaction, %s",this->Get_Target(i).c_str());
	    hW[i] = new TH1D(hname, htitle, 350, 1.0, 3.5);

//		sprintf(hname,"z_fracE_%s",myTgt.Get_Label(i).c_str());
//		sprintf(htitle,"Fractional Energy, %s",myTgt.Get_Label(i).c_str());
//		z_fracE[i] = new TH1D(hname, htitle, 150, 0, 1.5);
    }
}

//
// WriteHist - routine to write histograms to the output file
//
void HistManager::WriteHist(string RootFile){

    int i;

	  TFile *out = new TFile(RootFile.c_str(), "recreate");
	  out->cd();

    TDirectory *cdTarget[8];

    for(i=0; i<this->Get_nTarget(); i++){
      // create a directory for check on kinematics
      cdTarget[i] = out->mkdir(this->Get_Target(i).c_str());
      cdTarget[i]->cd();

      q2[i]->GetXaxis()->SetTitle("Q^{2} (GeV/c)^{2}");
      q2[i]->GetYaxis()->SetTitle("Counts");
	    q2[i]->Write();

      nu[i]->GetXaxis()->SetTitle("\nu (GeV)");
      nu[i]->GetYaxis()->SetTitle("Counts");
	    nu[i]->Write();

      elecZ[i]->GetXaxis()->SetTitle("e^{-} Z vertex (cm)");
      elecZ[i]->GetYaxis()->SetTitle("Counts");
	    elecZ[i]->Write();

      elecZC[i]->GetXaxis()->SetTitle("e^{-} Z vertex (cm)");
      elecZC[i]->GetYaxis()->SetTitle("Counts");
	    elecZC[i]->Write();

      elecZSector[i]->GetXaxis()->SetTitle("e^{-} Z vertex (cm)");
      elecZSector[i]->GetYaxis()->SetTitle("Sector");
      elecZSector[i]->Write();

      elecZCSector[i]->GetXaxis()->SetTitle("e^{-} Z vertex (cm)");
      elecZCSector[i]->GetYaxis()->SetTitle("Sector");
      elecZCSector[i]->Write();

      TotalMomentum[i]->GetXaxis()->SetTitle("Momentum (GeV/c)");
      TotalMomentum[i]->GetYaxis()->SetTitle("Particle");
	    TotalMomentum[i]->Write();

      X_VS_Y[i]->GetXaxis()->SetTitle("X vertex (cm)");
      X_VS_Y[i]->GetYaxis()->SetTitle("Y vertex (cm)");
      X_VS_Y[i]->Write();

      XC_VS_YC[i]->GetXaxis()->SetTitle("X vertex (cm)");
      XC_VS_YC[i]->GetYaxis()->SetTitle("Y vertex (cm)");
      XC_VS_YC[i]->Write();

      CCnphe[i]->GetXaxis()->SetTitle("Number of Photo-electrons");
      CCnphe[i]->GetYaxis()->SetTitle("Particle");
      CCnphe[i]->Write();

      ECu[i]->GetXaxis()->SetTitle("EC U (cm)");
      ECu[i]->GetYaxis()->SetTitle("Particle");
      ECu[i]->Write();

      ECv[i]->GetXaxis()->SetTitle("EC V (cm)");
      ECv[i]->GetYaxis()->SetTitle("Particle");
      ECv[i]->Write();

      ECw[i]->GetXaxis()->SetTitle("EC W (cm)");
      ECw[i]->GetYaxis()->SetTitle("Particle");
      ECw[i]->Write();

      ECtot_VS_P[i]->GetXaxis()->SetTitle("Momentum (GeV/c)");
      ECtot_VS_P[i]->GetYaxis()->SetTitle("EC total energy");
      ECtot_VS_P[i]->Write();

      ECtotP_VS_P[i]->GetXaxis()->SetTitle("Momentum (GeV/c)");
      ECtotP_VS_P[i]->GetYaxis()->SetTitle("EC_{total}/Mom.");
      ECtotP_VS_P[i]->Write();

      ECin_VS_ECout[i]->GetXaxis()->SetTitle("EC inner energy");
      ECin_VS_ECout[i]->GetYaxis()->SetTitle("EC outer energy");
      ECin_VS_ECout[i]->Write();

      hW[i]->GetXaxis()->SetTitle("W (GeV)");
      hW[i]->GetYaxis()->SetTitle("Counts");
      hW[i]->Write();

//    z_fracE[i]->GetXaxis()->SetTitle("z");
//    z_fracE[i]->GetYaxis()->SetTitle("Counts");
//    z_fracE[i]->Write();
    }
    out->Close();
}
