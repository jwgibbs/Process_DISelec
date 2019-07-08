/************************************************************************/
/*   Process_DISelec.cc                                                 */
/*                                                                      */
/*  June 2019 - Modified by M. H. Wood, Canisius College                */
/*                                                                      */
/************************************************************************/

#include "Process_DISelec.h"

int process (string inFile, int MaxEvents, int dEvents, int targMass) {
    int i;
    int iTarg, iTargCorr;
    float yDIS;

    ElecReader myElecReader(inFile,targMass);
    int entries = myElecReader.Get_Entries();

    double BEAM_ENERGY = myHistManager.GetBEAM_ENERGY();
    double MASS_ELECTRON = myHistManager.GetMASS_ELECTRON();
    TLorentzVector beam(0., 0., BEAM_ENERGY, sqrt(BEAM_ENERGY*BEAM_ENERGY + MASS_ELECTRON*MASS_ELECTRON));

    cout << "Entries: " << entries << endl;

    int StopProcess;
    if(MaxEvents){
        StopProcess = MaxEvents;
    }else{
        StopProcess = entries;
    }

    int processed;
    for (processed = 0; processed < StopProcess; processed = processed + 1) {
        if (!(processed % dEvents)) cout << "Processed Entries: " << processed << endl;

        myElecReader.ReadEntry(processed);

        yDIS = myElecReader.Get_Nu()/beam.E(); // fraction of electron's initial energy lost in the target rest frame

        Fill_Kine_Histograms(myElecReader,6);
        Fill_EC_Histograms(myElecReader,6);
        if(myElecReader.Get_ElectronCuts()){
          Fill_Kine_Histograms(myElecReader,7);
          Fill_EC_Histograms(myElecReader,7);
          iTarg = (int) myElecReader.Get_TargType();
          Fill_Kine_Histograms(myElecReader,iTarg);
          Fill_EC_Histograms(myElecReader,iTarg);
          iTargCorr = myElecReader.Get_TargType_Corr() + myHistManager.GetMAX_TARGTYPE();
          Fill_Kine_Histograms(myElecReader,iTargCorr);
          Fill_EC_Histograms(myElecReader,iTargCorr);
        }
//        z_fracEnergy = Omega.E()/nu; // fractional energy taken by hadron
//        myHistManager.GetZ_fracE(Vz_index)->Fill(z_fracEnergy); // histogram for fractional z

    } // end for loop for processing events

    myElecReader.Delete_RootFile(); // close the root TFile
    return processed;
}

void Fill_Kine_Histograms(ElecReader Rdr, int num)
{
  TVector3 elec_vert = Rdr.GetVertex();
  TVector3 elec_vert_corr = Rdr.GetVertexCorr();

  // increment counter for e-, uncorr. vertex (num 1-3) and corr. vertex (num 4-6)
  myCounter.Increment(myCounter.Get_CtrLabel(num));

  myHistManager.GetQ2(num)->Fill(Rdr.Get_Q2());
  myHistManager.GetNu(num)->Fill(Rdr.Get_Nu());
  myHistManager.GetHW(num)->Fill(Rdr.Get_W()); // histogram for W
  myHistManager.GetElecZ(num)->Fill(elec_vert.Z()); // fill electron z vertex histogram
  myHistManager.GetElecZC(num)->Fill(elec_vert_corr.Z()); // fill corrected electron z vertex histogram
  myHistManager.GetElecZSector(num)->Fill(elec_vert.Z(),Rdr.Get_Sector()); // fill electron z vertex per sector histogram
  myHistManager.GetElecZCSector(num)->Fill(elec_vert_corr.Z(),Rdr.Get_Sector()); // fill corrected electron z vertex per sector histogram
  myHistManager.GetX_VS_Y(num)->Fill(elec_vert.X(),elec_vert.Y()); // fill electron x vs y vertex histogram
  myHistManager.GetXC_VS_YC(num)->Fill(elec_vert_corr.X(),elec_vert_corr.Y()); // fill electron x vs y vertex histogram
  myHistManager.GetTotalMomentum(num)->Fill(Rdr.Get_P()); // histogram for e- momentum
}

void Fill_EC_Histograms(ElecReader Rdr, int num)
{
    myHistManager.GetCCnphe(num)->Fill(Rdr.Get_Nphe());
    myHistManager.GetECu(num)->Fill(Rdr.Get_UC());
    myHistManager.GetECv(num)->Fill(Rdr.Get_VC());
    myHistManager.GetECw(num)->Fill(Rdr.Get_WC());
    myHistManager.GetECtot_VS_P(num)->Fill(Rdr.Get_P(),Rdr.Get_ECtot());
    myHistManager.GetECin_VS_ECout(num)->Fill(Rdr.Get_ECin(),Rdr.Get_ECout());

    if(Rdr.Get_P()!=0.0){
        myHistManager.GetECtotP_VS_P(num)->Fill(Rdr.Get_P(),Rdr.Get_ECtot()/Rdr.Get_P());
    }
}

void PrintUsage(char *processName)
{
    cerr << processName << " <options> <filename>\n";
    cerr << "\toptions are:\n";
    cerr << "\t-o<filename>\tROOT output file (def. = ctProcess_omega.root).\n";
    cerr << "\t-M#\t\tprocess maximum # of events.\n";
    cerr << "\t-D#\t\tinform user when # of events have been processed (def. = 1000).\n";
    cerr << "\t-T#\t\tTarget mass number\n";
    cerr << "\t-h\t\tprint the above" << endl;
}

void PrintAnalysisTime(float tStart, float tStop){
    //time to complete function
    float minutes = 0;
    float seconds = 0;
    minutes = (tStop - tStart)/1000000;
    minutes = (minutes)/60;
    seconds = fmod(minutes,1);
    minutes = minutes-seconds;
    seconds = seconds*60;

    if (minutes==0){
        cout<<endl<<"Completed in "<<seconds<<" seconds."<<endl<<endl;
    }
    else{
        cout<<endl<<"Completed in "<<minutes<<" minutes and "<<seconds<<" seconds."<<endl<<endl;
    }
}

void PrintTVector3(TVector3 V){
    cout <<"X "<<V.X()<<"\t";
    cout <<"Y "<<V.Y()<<"\t";
    cout <<"Z "<<V.Z()<<"\t" <<endl;
}

void PrintTLorentzVector(TLorentzVector TLV){
    cout <<"Px "<<TLV.Px()<<"\t";
    cout <<"Py "<<TLV.Py()<<"\t";
    cout <<"Pz "<<TLV.Pz()<<"\t";
    cout <<"E " <<TLV.E() <<"\t";
    cout <<"M " <<TLV.M() <<"\t";
    cout <<"M^2 " <<TLV.M2() <<endl;
}

#ifndef __CINT__
int main (int argc, char **argv) {

    extern char *optarg;
    int c;
    extern int optind;

    int i;
    int dEvents = 1000; // increment of events for processing print statement
    int MaxEvents = 0; // max. number of events to process
    int TotEvents;

    int targMass = 2; // mass number for target

    string inFile;
    string outFile = "Process_DISelec.root";

    float timeStart = clock(); // start time

    for (i = 0; i < argc; ++i) cerr << argv[i] << " "; cerr << endl;
    while ((c = getopt(argc,argv, "o:M:D:T:h")) != -1 ) {
        switch (c) {
            case 'o': outFile = optarg; break;
            case 'M': MaxEvents = atoi(optarg); break;
            case 'D': dEvents = atoi(optarg); break;
            case 'T': targMass = atoi(optarg); break;
            case 'h':
                PrintUsage(argv[0]);
                exit(0);
                break;

            default:
                cerr << "Unrecognized argument: " << optarg << endl;
                PrintUsage(argv[0]);
                exit(0);
                break;
        }
    }

    myCounter.Init(); // zero out the counters
    myHistManager.BookHist(); // declare histograms

    for (i = optind; i < argc; ++i) {
        inFile = argv[i]; // process all arguments on command line.
        if (inFile != '-') { // we have a file to process
            cout << "Analyzing file " << inFile << endl; // let user know which file is being processed
            // process the root file and return number of processed events
            TotEvents = process(inFile,MaxEvents,dEvents,targMass);
            cout<<TotEvents<<" events processed"<<endl; // print out stats
        }
    }

    myHistManager.WriteHist(outFile); // write histograms to a file
    myCounter.Print(); // Print the counter statistics

    float timeStop = clock();
    PrintAnalysisTime(timeStart,timeStop);
}
#endif
