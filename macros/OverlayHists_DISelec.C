// OverlayHists_DISelec.C
//
// macro to overlay eg2a DIS e- histograms
//
// Michael H. Wood, Canisius College
//
//--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// gROOT->Reset();   // start from scratch

Float_t Lmar = 0.125;
Float_t Rmar = 0.125;
Float_t yoff = 1.75;
Int_t lcol[10] = {1,2,4,6,7,8,9,10,14,15};

//
// OverlayHists_DISelec - overlay 1D histograms
//
//                  fAna = output from eg2a DMS
//                  hname = histogram name
//                  target = target name
//
void OverlayHists_DISelec(string fAna, string hname, string target, int iCorr)
{
	int i;
	char OutCan[100];
	string hTgtName;
	string TgtDirName;
	TH1F *hist[3];
	TH1F *hsum;
	TDirectory *tmp;

	vector<string> TgtDir;
	TgtDir.push_back("NoTarget");
	TgtDir.push_back("LD2");
	TgtDir.push_back("Nuc");

	vector<string> TgtCorr;
	TgtCorr.push_back("");
	TgtCorr.push_back("_Corr");

  printf("Analyzing file %s\n",fAna.c_str());

	TFile *fm = new TFile(fAna.c_str(),"READ");

	for(i=0; i<TgtDir.size(); i++){
		TgtDirName = TgtDir.at(i) + TgtCorr.at(iCorr);
		tmp = fm->GetDirectory(TgtDirName.c_str());

		hTgtName = hname + "_" + TgtDirName;

		hist[i] = (TH1F*)tmp->Get(hTgtName.c_str());
		if(i==0){
			hsum = (TH1F*)hist[i]->Clone("hsum");
		}else{
			hsum->Add(hist[i]);
		}
	}

  // Canvas to plot histogram
  TCanvas *c1 = new TCanvas("c1","c1",0,0,600,600);
  c1->SetBorderMode(1);  //Bordermode (-1=down, 0 = no border, 1=up)
  c1->SetBorderSize(5);
  gStyle->SetOptStat(0);
  c1->SetFillStyle(4000);

  c1->cd();
  gPad->SetLeftMargin(Lmar);
  gPad->SetRightMargin(Rmar);
  gPad->SetFillColor(0);

	TLegend *leg = new TLegend(0.7,0.7,0.95,0.875);

	hsum->SetTitle(0);
	hsum->GetXaxis()->CenterTitle();
	hsum->GetYaxis()->CenterTitle();
	hsum->GetYaxis()->SetTitleOffset(yoff);
  hsum->SetLineWidth(2);
	hsum->Draw();
	leg->AddEntry(hsum,"Total","l");

	for(i=0; i<TgtDir.size(); i++){
		hist[i]->SetLineWidth(2);
		hist[i]->SetLineColor(lcol[i+1]);
		hist[i]->SetFillColorAlpha(lcol[i+1],0.5);
		hist[i]->Draw("same");
		leg->AddEntry(hist[i],TgtDir.at(i).c_str(),"l");
	}
//	leg->SetLineColor(0);
//	leg->SetFillStyle(0);
	leg->Draw();

	sprintf(OutCan,"DISelec_Overlay_%s%s_%s.gif",hname.c_str(),TgtCorr.at(iCorr).c_str(),target.c_str());
	c1->Print(OutCan);
//	sprintf(OutCan,"DISelec_Overlay_%s.eps",hname.c_str());
//	c1->Print(OutCan);
}

//
// OverlayHists_VZBySectorDISelec - overlay 1D histograms
//
//                  fAna = output from eg2a DMS
//                  hname = histogram name
//                  target = target name
//
void OverlayHists_VzBySector_DISelec(string fAna, int hindex, string target, int iCorr)
{
	int i, j;
	char OutCan[100];
	string strname;
	string hTgtName;
	string hSumName;
	string htitle;
	string TgtDirName;
	TH1D *hist[3][6];
	TH2D *h2D[3];
	TH1D *hsum[6];
	TDirectory *tmp;
	TLegend *leg[6];

	vector<string> hname;
	hname.push_back("elecZSector");
	hname.push_back("elecZCSector");

	vector<string> TgtCorr;
	TgtCorr.push_back("");
	TgtCorr.push_back("_Corr");

	if(hindex<0 || hindex>hname.size()){
		cout<<"Wrong histogram index "<<hindex<<endl;
		cout<<"Value should be 0 <= hindex < "<<hname.size()<<endl;
		exit(0);
	}
	vector<string> TgtDir;
	TgtDir.push_back("NoTarget");
	TgtDir.push_back("LD2");
	TgtDir.push_back("Nuc");

  printf("Analyzing file %s\n",fAna.c_str());

	TFile *fm = new TFile(fAna.c_str(),"READ");

	for(i=0; i<TgtDir.size(); i++){
		TgtDirName = TgtDir.at(i) + TgtCorr.at(iCorr);
		tmp = fm->GetDirectory(TgtDirName.c_str());
		hTgtName = hname.at(hindex) + "_" + TgtDirName;
		h2D[i] = (TH2D*)tmp->Get(hTgtName.c_str());

		for(j=0; j<6; j++){
			strname = hTgtName + "_px_" + std::to_string(i) + "_" + std::to_string(j);
			hist[i][j] = (TH1D*)h2D[i]->ProjectionX(strname.c_str(),j+1,j+1,"");
			if(i==0){
				hSumName = "hsum_" + std::to_string(j);
				hsum[j] = (TH1D*)hist[i][j]->Clone(hSumName.c_str());
			}else{
				hsum[j]->Add(hist[i][j]);
			}
		}
	}

  // Canvas to plot histogram
  TCanvas *c1 = new TCanvas("c1","c1",0,0,1100,750);
  c1->SetBorderMode(1);  //Bordermode (-1=down, 0 = no border, 1=up)
  c1->SetBorderSize(5);
  gStyle->SetOptStat(0);
  c1->SetFillStyle(4000);
	c1->Divide(3,2);

	for(j=0; j<6; j++){
  	c1->cd(j+1);
  	gPad->SetLeftMargin(Lmar);
  	gPad->SetRightMargin(Rmar);
  	gPad->SetFillColor(0);

 		leg[j]= new TLegend(0.7,0.7,0.95,0.875);

		htitle = "Sector " + std::to_string(j+1);
		hsum[j]->SetTitle(htitle.c_str());
		hsum[j]->GetXaxis()->CenterTitle();
		hsum[j]->GetYaxis()->CenterTitle();
		hsum[j]->GetYaxis()->SetTitleOffset(yoff);
		hsum[j]->SetLineWidth(2);
		hsum[j]->Draw();
		leg[j]->AddEntry(hsum[j],"Total","l");

		for(i=0; i<TgtDir.size(); i++){
			hist[i][j]->SetLineWidth(2);
			hist[i][j]->SetLineColor(lcol[i+1]);
			hist[i][j]->SetFillColorAlpha(lcol[i+1],0.5);
			hist[i][j]->Draw("same");
			leg[j]->AddEntry(hist[i][j],TgtDir.at(i).c_str(),"l");
		}
//	leg->SetLineColor(0);
//	leg->SetFillStyle(0);
		leg[j]->Draw();
	}

	sprintf(OutCan,"DISelec_Sector_%s%s_%s.gif",hname.at(hindex).c_str(),TgtCorr.at(iCorr).c_str(),target.c_str());
	c1->Print(OutCan);
}
