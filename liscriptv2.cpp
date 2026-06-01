#include <iostream>
#include "variables.h"
#include "eventassign.h"
#include "map.h"
#include "plots.h"
#include <vector>

#include std::vector;

void liscriptv2.cpp(TString type, TString det, TString range, TString compress, TString target) {
    double liruns;
    double carbonruns;
    double backgroundruns;

    double norm;

    vector<unsigned short> runs;

    if (target == "carbon") {
      for (int i = 0; i<12; i++) {
        runs.push_back(carbonruns[i]);
      }
    }
    else if (target == "li") {
      for (int i = 0; i<(liruns/liruns[0]); i++) {
        runs.push_back(liruns[i]);
      }
    }

    for (int i = 0; i < ndet; i++) {
      if (target == "carbon" ) {
        norm = 0.61; //0.61 is the normalization used for carbon. Found by comparing peak heights
      }
      else if (target == "li") {
        norm = 6.75;
      }
    }

    for (int current_run = 0; current_run < runs.size(); current_run++) {
      
        TString fileName;
        fileName.Form("catrina_%d_3000.root", run[current_run]);
        TFile *filename = new TFile(fileName);
        TTree *tree = (TTree *)filename->Get("tree");
        cout << "Pulling data from TTree..." << endl;
        TTreeReader reader(tree);

        TTreeReaderValue<ULong64_t>  evID = {reader, "evID"};
        TTreeReaderValue<UInt_t>    multi = {reader, "multi"};
        TTreeReaderArray<UShort_t>     sn = {reader, "sn"}; // serial no.
        TTreeReaderArray<UShort_t>     ch = {reader, "ch"}; // channel
        TTreeReaderArray<UShort_t>      e = {reader, "e"};  //long
        TTreeReaderArray<UShort_t>     e2 = {reader, "e2"}; //short
        TTreeReaderArray<ULong64_t>   e_t = {reader, "e_t"}; // in ns
        TTreeReaderArray<UShort_t>    e_f = {reader, "e_f"}; // in ps
    
        ULong64_t NumEntries = tree->GetEntries();

        while(Reaeder.Next()) {
            EventAssign(runs[current_run]);
            plotfill();
        }

    }



}