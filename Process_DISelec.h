#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TVector3.h"
#include "TFile.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "HistManager.h"
#include "ElecReader.h"
#include "ElecCounter.h"

#define DEBUG 0

using namespace std;

HistManager myHistManager; // declare the histogram manager
ElecCounter myCounter; // declare the counters

int process (string inFile, int MaxEvents, int dEvents, int targMass);
void PrintUsage(char *processName);
void PrintAnalysisTime(float tStart, float tStop);
void PrintTVector3(TVector3 V);
void PrintTLorentzVector(TLorentzVector TLV);
void Fill_Kine_Histograms(ElecReader Rdr, int num);
void Fill_EC_Histograms(ElecReader Rdr, int num);
