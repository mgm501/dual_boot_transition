#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TCutG.h"
#include "TChain.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <TEntryList.h>
#include <sstream>
#include <vector>
#include "TH1.h"
#include "TF1.h"
#include "TSpectrum.h"
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>
#include "TSystem.h"
//#include "plot.h"
//#include "plotdef.h"
#define NDET 17

//struct Plot Plot;
//struct Plot *tof[NDET];

TFile *_file2 = TFile::Open("neutron_cuts.root");
TCutG *ncut_00 = (TCutG*)gROOT->FindObject("ncut_4");
TCutG *ncut_01 = (TCutG*)gROOT->FindObject("ncut_5");
TCutG *ncut_02 = (TCutG*)gROOT->FindObject("ncut_7");
TCutG *ncut_03 = (TCutG*)gROOT->FindObject("ncut_2");
TCutG *ncut_04 = (TCutG*)gROOT->FindObject("ncut_10");
TCutG *ncut_05 = (TCutG*)gROOT->FindObject("ncut_11");
TCutG *ncut_06 = (TCutG*)gROOT->FindObject("ncut_13");
TCutG *ncut_07 = (TCutG*)gROOT->FindObject("ncut_105");
TCutG *ncut_08 = (TCutG*)gROOT->FindObject("ncut_106");
TCutG *ncut_09 = (TCutG*)gROOT->FindObject("ncut_107");
TCutG *ncut_10 = (TCutG*)gROOT->FindObject("ncut_108");
TCutG *ncut_11 = (TCutG*)gROOT->FindObject("ncut_110");
TCutG *ncut_12 = (TCutG*)gROOT->FindObject("ncut_111");
TCutG *ncut_13 = (TCutG*)gROOT->FindObject("ncut_112");
TCutG *ncut_14 = (TCutG*)gROOT->FindObject("ncut_114");
TCutG *ncut_15 = (TCutG*)gROOT->FindObject("ncut_8");
TCutG *ncut_16 = (TCutG*)gROOT->FindObject("ncut_115");

const std::map<unsigned short, int> SN2Bd = {
  {336, 0},
  {409, 1},
  {89, 2}
};


const std::map<unsigned short, int> SN2Bd2 = {
  {336, 0},
  {409, 1},
  {405, 2},
};

// 3,5,6,9,11,12,14, big neutron
// 105, 106, 107, 108, 110, 111, 112, 114, 115  small neutron detector
// 200 is RF
// detector number in channel number index
const int mapping[3][16] = {
  // 0,   1,   2,  3,  4,   5,   6,   7,  8,   9,  10,  11,  12, 13,  14, 15
  {108,  -1,  -1, -1, -1, 105, 106, 107, -1,  -1, 110, 111, 112, -1, 114, 115 },
  { -1,  -1,  -1,  4, -1,   5,   7,  -1, -1,   2,  -1,  11,  10, -1,  13,   8 },
  { -1,  -1,  -1, -1, -1,  -1,  -1,  -1, -1,  -1,  -1,  -1, 200, -1,  -1,  -1 }
};

const int mapping2[3][16] = {
  // 0,   1,   2,  3,  4,   5,   6,   7,  8,   9,  10,  11,  12, 13,  14, 15
  {108,  -1,  -1, -1, -1, 105, 106, 107, -1,  -1, 110, 111, 112, -1, 114, 115 },
  { -1,  -1,  -1,  4, -1,   5,   7,  -1, -1,   2,  -1,  11,  10, -1,  13,   8 },
  { 200,  -1,  -1, -1, -1,  -1,  -1,  -1, -1,  -1,  -1,  -1, -1, -1,  -1,  -1 }
};


// small detectors prefixed with 100. detector index to loop id
const std::map<unsigned short, int> Index2ID = {
  {  2,   3},
  {  4,   0},
  {  5,   1},
  {  7,   2},
  {  8,  15},
  { 10,   4},
  { 11,   5},
  { 13,   6},
  {105,   7},
  {106,   8},
  {107,   9},
  {108,  10},
  {110,  11},
  {111,  12},
  {112,  13},
  {114,  14},
  {115,  16},
  {200, 200},
};

const std::map<unsigned short, int> ID2Index = {
  {  3,  2},
  {  0,  4},
  {  1,  5},
  {  2,  7},
  { 15,  8},
  {  4,  10},
  {  5,  11},
  {  6,  13},
  {  7,  105},
  {  8,  106},
  {  9,  107},
  { 10,  108},
  { 11,  110},
  { 12,  111},
  { 13,  112},
  { 14,  114},
  { 16,  115},
  {200,  200},
};


//this is the channel number to loop index
const std::map<unsigned short, int> Channel2ID = {
  {3,    0},
  {5,    1},
  {6,    2},
  {9,    3},
  {11,   5},
  {12,   4},
  {14,   6},
  {15,  15},
  {105,  7},
  {106,  8},
  {107,  9},
  {100,  10},
  {110,  11},
  {111,  12},
  {112,  13},
  {114,  14},
  {115,  16},
};

//this is loop index to channel number
const std::map<unsigned short, int> ID2Board = {
  {0,  3},
  {1,  5},
  {2,  6},
  {3,  9},
  {4,  12},
  {5,  11},
  {6,  14},
  {7,  105},
  {8,  106},
  {9,  107},
  {10, 100},
  {11, 110},
  {12, 111},
  {13, 112},
  {14, 114},
  {15, 15},
  {16, 115},
};

//this is loop index to board
const std::map<int, int> Det2Board = {
  {0,  409},
  {1,  409},
  {2,  409},
  {3,  409},
  {4,  409},
  {5,  409},
  {6,  409},
  {7,  336},
  {8,  336},
  {9,  336},
  {10, 336},
  {11, 336},
  {12, 336},
  {13, 336},
  {14, 336},
  {15, 409},
  {16, 336},
};

//this is loop index to channel without board
const std::map<int, int> Det2Channel = {
  {0,  3},
  {1,  5},
  {2,  6},
  {3,  9},
  {4,  12},
  {5,  11},
  {6,  14},
  {7,  5},
  {8,  6},
  {9,  7},
  {10, 0},
  {11, 10},
  {12, 11},
  {13, 12},
  {14, 14},
  {15, 15},
  {16, 15},
};

//loop id to angle order
const std::map<int, int> Det2AngleOrder = {
{0, 12},
{1, 15},
{2, 7},
{3, 3},
{4, 14},
{5, 6},
{6, 8},
{7, 5},
{8, 11},
{9, 0},
{10, 16},
{11, 4},
{12, 13},
{13, 2},
{14, 10},
{15, 1},
{16, 9},
};

//double Angle[NDET] = {127, 45, 137, 100, 132, 110, 105, 97.5, 107.5, 112.5, 139.5, 124.5, 47.5, 134.5, 102.5, 50, 129.5}; 
//double Angle[NDET] = {131, 45, 141, 104, 131, 107, 105, 98, 111, 0, 143, 131, 51, 138, 108, 69.3, 129};
//double Angle[NDET] = {126, 0, 137, 100, 133, 109, 104, 98, 107, 0 , 139, 124, 47.5, 135, 102, 50, 128};
double Angle[NDET] = {127.5, 0, 136.5, 101, 133.5, 111.5, 105, 97, 108.5, 0, 140, 123, 44, 136, 102.5, 54, 129.5};

float ToF[NDET] = {81.97, 0, 83.6, 76.79, 82.81, 78.79, 77.79, 76.28, 78.29, 79.28, 83.97, 81.53, 32.38, 83.21, 77.29, 32.55, 82.40};

float energy[NDET] = {3.37, 0, 3.24, 3.84, 3.3, 3.6, 3.74, 3.89, 3.69, 3.6, 3.21, 3.41, 4.98, 3.27, 3.79, 4.93, 3.34};

float energyee[NDET] = {770.46, 0, 727.12, 933.65, 747.61, 865.63, 898.6, 951.93, 881.85, 849.98, 717.75, 782.76, 1365.58, 737.06, 915.59, 1345.83, 758.74};

int Channel[NDET] = {7387,1761,4914,10260,7781,8249,8358,12210,9812,16390,8408,8157,18570,8008,11170,12220,8860};

//TH2D *dudu[NDET]; // short vs long
//TH2D *hehe[NDET]; // long vs rf
//TH2D *heheg[NDET];

TH1D *tDiff[NDET];
TH1D *tDiffcut[NDET];
TH1D *tDiffg[NDET];
TH1D *total[NDET];
TH1D *total2[NDET];
TH1D *total3[NDET];
TH1D *total4[NDET];
//TH1D *ex[NDET];
TH2D *totalPSD[NDET];
//TH2D *envslong[NDET];
//TH2D *totenvslong[NDET];
//TH2D *tofvslong[NDET];
//TH2D *tottofvslong[NDET];
TH2D *PSD[NDET];
//TH2D *PSDg[NDET];
//TH2D *totexq[NDET];
TH2D *PSDc[NDET];
//TH2D *exvsq[NDET];
TH2D *totalPSDc[NDET];
TH2D *total2d[NDET];
//TH1D *clone2[NDET];
//TH1D *shifttDiff[NDET];
//TH2D *eL_tDiff[NDET];
TCutG *cuts[NDET];
TH2D *lovstof[NDET];
//TH1D *longgate[NDET];
//TH1D *totallong[NDET];
TH1D *energyplot;
//TH2D *qexplot;
TH1F *qvalues[NDET];
//TH1D *qvalues2[NDET];
TH1F *totq[NDET];
//TH1D *totq1[NDET];
TH1D *cal[NDET];
TH1D *nenergy[NDET];
TH1D *totnenergy[NDET];
TH1 *fithist[NDET];
//TH1D *energyplot1;
//TH2D *tofvq[NDET];
//TH2D *tottofvq[NDET];
//TH2D *alltofvq;

ushort eL[NDET];
ushort eS[NDET];
ushort eTail[NDET];

const float timeResol = 4; //ns
const int timeRange[2] = {200, 800};
const int timeBin = (timeRange[1] - timeRange[0])/timeResol;
const int energyrange[2] = {-6,6};

std::map<int, std::vector<double>> ReadLogFile(const std::string& filename) {
  std::ifstream file(filename);

  std::map<int, std::vector<double>> data;
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream ss(line);
    int carbon;
    int i;
    double peak;
    int isbackground;

    if (ss >> carbon >> i >> peak >> isbackground) {
      if (data[carbon].size() <= static_cast<size_t>(i)) {
        data[carbon].resize(i+1);
      }
      data[carbon][i] = peak;
    }
  }

  file.close();
  return data;
}

struct bounds { 
  int x1;
  int x2;
};

struct bounds outside;
struct bounds inside;

//===========================================================================================================================
//================================================begin function=============================================================
//===========================================================================================================================

void liscript(TString type, TString det, TString calibration, TString range, TString compress, TString target) {

  std::cout << "start for loop" << std::endl;

  double distance[NDET] = {1.97, 0, 1.935, 1.99, 1.99, 2.02, 2.03, 2.08, 2.09, 0, 1.94, 1.98, 1., 1.98, 2.08, 1., 1.94}; //0.85, 0.86

  int x; int y;

  outside.x1 = timeRange[0];
  outside.x2 = timeRange[1];
  inside.x1 = -200;
  inside.x2 = 400;

  if (range == "short" && type != "flip") {
    x = inside.x1;
    y = inside.x2;
  }
  else if (range == "out" && type != "flip") {
    x = timeRange[0];
    y = timeRange[1];
  }
  else if (range == "short" && type == "flip") {
    x = -800;
    y = -200;
  }

  std::cout << "========================================" << std::endl;
  std::cout << "Type " << type << "  Range " << range << std::endl;
  std::cout << "========================================" << std::endl;

  for (int i = 0; i < NDET; i++) {
    //gStyle->SetTitleSize(0.5);
    //dudu[i] = new TH2D(Form("Detector-%d", i), Form("Det-%d", i), 400, 0, 20000, 400, 0, 20000);
    //hehe[i] = new TH2D(Form("Det-%d", i), Form(" Detector %d", ID2Board.at(i)), 500, 0, 1000, 100, 0, 30000);
    //heheg[i] = new TH2D(Form("Number-%d", i), Form(" Detector %d", ID2Board.at(i)), 500, 0, 1000, 100, 0, 30000);
    PSD[i] = new TH2D(Form("PSDnum-%d", i), Form(" Detector %d Channel - %d Angle - %f", ID2Board.at(i), Channel[i], Angle[i]), 4096, 0, 30000, 512, -1, 1);
    //PSDg[i] = new TH2D(Form("PSDgnum-%d", i), Form(" Detector %d", ID2Board.at(i)), 2000, 0, 3500, 512, -0.1, 0.8); // 4096
    PSDc[i] = new TH2D(Form("PSDgnumc-%d", i), Form(" Detector %d", ID2Board.at(i)), 2000, 0, 3500, 512, -0.1, 0.8); // 4096
    //exvsq[i] = new TH2F(Form("exvsq-%d", i), Form(" Detector %d NE - %f Angle - %f ToF - %f", ID2Board.at(i), energyee[i], Angle[i], ToF[i]), 100, 0, 300, 1000, -6, 120);
    //totexq[i] = new TH2D(Form("totexvsq-%d", i), Form(" Detector %d NE - %f Angle - %f ToF - %f", ID2Board.at(i), energyee[i], Angle[i], ToF[i]), 125, -20, 20, 400, -20, 20);
    //exvsq[i] = new TH2D(Form("exvsq-%d", i), Form(" Detector %d NE - %f Angle - %f ToF - %f", ID2Board.at(i), energyee[i], Angle[i], ToF[i]), 125, -20, 20, 400, -20, 20);
    //totexq[i]->GetXaxis()->SetTitle("Excitation Energy (MeV)");
    //totexq[i]->GetYaxis()->SetTitle("Q value (MeV)");
    //totexq[i]->GetXaxis()->SetTitle("Excitation Energy (MeV)");
    //totexq[i]->GetYaxis()->SetTitle("Q value (MeV)");
    //PSDc[i]->SetCanExtend(TH1::kAllAxes);
    //exvsq[i]->SetCanExtend(TH1::kAllAxes);
    //totexq[i]->SetCanExtend(TH1::kAllAxes);
    //ex[i] = new TH1D(Form("excitations %d" , i), Form(" Detector %d", ID2Board.at(i)), 27.6, -20, 20);
    totalPSDc[i] = new TH2D(Form("PSDgnumctot-%d", i), Form(" Detector %d NE - %f Angle - %f ToF - %f", ID2Board.at(i), energyee[i], Angle[i], ToF[i]), 2000, 0, 3500, 512, -0.1, 0.8); //4096
    lovstof[i] = new TH2D(Form("lovstof-%d", i), Form(" Detector %d Angle - %f", ID2Board.at(i), Angle[i]), 125, -20, 20, timeBin, x, y); //4096
    //totalPSDc[i]->SetCanExtend(TH1::kAllAxes);
    //total[i] = new TH1F(Form("totalTdiff - %d",i), Form(" Detector %d NE - %f Angle %f ToF - %f", ID2Board.at(i), energy[i], Angle[i], ToF[i]), 3000, x, y);
    total[i] = new TH1D(Form("totalTdiff - %d",i), Form(" Detector %d NE - %f Angle %f ToF - %f", ID2Board.at(i), energy[i], Angle[i], ToF[i]), timeBin, x, y); //4096
    //total[i]->SetCanExtend(TH1::kAllAxes);
    total2[i] = new TH1D(Form("totalTdiff2 - %d",i), Form(" Detector %d Run %d Angle - %f ToF - %f", ID2Board.at(i), Angle[i], ToF[i]), timeBin, x, y);
    total3[i] = new TH1D(Form("totalTdiff3 - %d",i), Form(" Detector %d Run %d Angle - %f ToF - %f", ID2Board.at(i), Angle[i], ToF[i]), timeBin, x, y);
    total4[i] = new TH1D(Form("totalTdiff4 - %d",i), Form(" Detector %d Run %d Angle - %f ToF - %f", ID2Board.at(i), Angle[i], ToF[i]), timeBin, x, y);
    totalPSD[i] = new TH2D(Form("PSDindex-%d", i), Form(" Detector %d Channel - %d Angle - %f ToF - %f", ID2Board.at(i), Channel[i], Angle[i], ToF[i]), 4096, -1000, 30000, 512, -1, 1);
    //tofvq[i] = new TH2D(Form("tofvsq-%d", i), Form(" Detector %d", ID2Board.at(i)), timeBin, x, y, 125, -20, 20);
    //tottofvq[i] = new TH2D(Form("total tofvsq-%d", i), Form(" Detector %d", ID2Board.at(i)), timeBin, x, y, 125, -20, 20);
    tDiffcut[i] = new TH1D(Form("totalTdiffcut - %d",i), Form(" Detector %d Angle - %f ToF - %f", ID2Board.at(i), Angle[i], ToF[i]), timeBin, x, y);
    if (i == 12 || i == 15) {
      qvalues[i] = new TH1F(Form("energies %d" , i), Form(" Detector %d", ID2Board.at(i)), 27.6, -20, 20); //125 binning for backwards 27.6 for forwards
      fithist[i] = new TH1F(Form("fithist %d" , i), Form(" Detector %d Angle - %f Dis - %f", ID2Board.at(i), Angle[i], distance[i]), 27.6, -20, 20);
      nenergy[i] = new TH1D(Form("n energies %d" , i), Form(" Detector %d Angle %f", ID2Board.at(i), Angle[i]), 27.6, -20, 20);
      totnenergy[i] = new TH1D(Form("tot nenergies %d" , i), Form(" Detector %d Angle %f", ID2Board.at(i), Angle[i]), 27.6, -20, 20);
      totq[i] = new TH1F(Form("energiesq %d" , i), Form(" Detector %d Angle - %f Dis - %f", ID2Board.at(i), Angle[i], distance[i]), 27.6, -20, 20); //139 bins for carbon, -20 to 20
    }
    else {
      qvalues[i] = new TH1F(Form("energies %d" , i), Form(" Detector %d", ID2Board.at(i)), 57, -20, 20); //57 or 125
      fithist[i] = new TH1F(Form("fithist %d" , i), Form(" Detector %d Angle - %f Dis - %f", ID2Board.at(i), Angle[i], distance[i]), 57, -20, 20);
      nenergy[i] = new TH1D(Form("n energies %d" , i), Form(" Detector %d Angle %f", ID2Board.at(i), Angle[i]), 57, -20, 20);
      totnenergy[i] = new TH1D(Form("tot nenergies %d" , i), Form(" Detector %d Angle %f", ID2Board.at(i), Angle[i]), 57, -20, 20);
      totq[i] = new TH1F(Form("energiesq %d" , i), Form(" Detector %d Angle - %f Dis - %f", ID2Board.at(i), Angle[i], distance[i]), 57, -20, 20); //139 bins for carbon, -20 to 20
    }
    //qvalues2[i] = new TH1D(Form("energies2 %d" , i), Form(" Detector %d Angle - %d", ID2Board.at(i), Angle[i]), 27.6, -18, 22);
    total2d[i] = new TH2D(Form("total2d-%d", i), Form(" Detector %d Angle - %f", ID2Board.at(i), Angle[i]), 125, -20, 20, timeBin, x, y); //4096
    //totq1[i] = new TH1D(Form("energiesq1 %d" , i), Form(" Detector %d", ID2Board.at(i)), 27.6, -20, 20);
    //clone2[i] = new TH1D(Form("totalTdiffclone2 - %d",i), Form(" Detector %d Angle - %f ToF - %f", ID2Board.at(i), Angle[i], ToF[i]), timeBin, x, y);
    //envslong[i] = new TH2D(Form("evlong - %d",i),Form("det %d",i),4096, 0, 30000,125, -20, 20);
    //totenvslong[i] = new TH2D(Form("totevlong - %d",i),Form("det %d",i),4096, 0, 30000,125, -20, 20);
    //tofvslong[i] = new TH2D(Form("tofvlong - %d",i),Form("det %d",i),4096, 0, 30000, timeBin, x, y);
    //tottofvslong[i] =new TH2D(Form("tottofvlong - %d",i),Form("det %d",i),4096, 0, 30000, timeBin, x, y);
    //longgate[i] = new TH1D(Form("long %d",i), Form("det %d", i), 4096, 0, 30000);
    //totallong[i] = new TH1D(Form("tot long %d", i), Form("det %d", i), 4096, 0, 30000);
    cal[i] = new TH1D(Form("calibrations - %d",i),"calibrations",512,0,8000);
  }
  energyplot = new TH1D("energies", "energies", 57, -20, 20);
  //energyplot1 = new TH1D("energies1", "energies", 27.6, -20, 20);
  //qexplot = new TH2D("energies 2d", "energies 2d", 27.6, -20, 20, 400, -20, 20);
  //qexplot->GetXaxis()->SetTitle("Excitation Energy");
  //qexplot->GetYaxis()->SetTitle("Q-Value");
  //alltofvq = new TH2D("ToF vs Ex", "ToF vs Ex", timeBin, x, y, 125, -20, 20);

  std::ifstream File;

  TCutG *cut[NDET];

  File.open("lishifts.txt");

  std::map<int, std::vector<double>> data = ReadLogFile("lishifts.txt");

  int carbonblank[12] = {264,276,278,299,302,304,257,261,262,263,322,326};
  //int carbonblank[6] = {264,276,278,299,302,304};
  //int allli[6] = {257,261,262,263,322,326};
  //int carbonblank[1] = {266};

  int carbon[6] = {264,276,278,299,302,304};

  int blank[6] = {257,261,262,263,322,326};

  int lithium0[9] = {132,139,143,144,145,146,147,148,149}; //132, 139,143, 144, 145, 146
  int lithium1[10] = {150,151,152,153,154,155,156,158,159,160}; //158 156 155 154 152
  int lithium2[8] = {161,162,163,164,168,207,208}; // runs 205 and before have sloppy spectra, probably due to buncher phase changing 169
  //218 is first run with sg used throughout experiment. Will be setting this as cutoff for valid li data.
  int lithium3[12] = {218,219,220,223,224,225,228,229,230,232}; //223 weird massive bin with 231
  int lithium4[9] = {233,240,245,246,250,251,252,253,254}; //233,240
  int lithium5[9] = {255,271,272,273,274,275,280,281,282};
  int lithium6[10] = {283,284,285,286,287,288,289,290,291,292}; //286
  int lithium7[10] = {293,294,295,296,297,298,305,308,309,310}; //14.5 hours potentially unusable
  int lithium8[16] = {311,312,313,314,315,316,317,318,319,320,257,261,262,263,322,326};

  //int lithium[8] = {220,224,225,228,229,230,231,268};  //124 for early phos

  int lithium[1] = {312}; //will be used to test individual or arbitrary number of runs

  int allli[72] = {218,219,220,223,224,225,228,229,230,231,232,233,240,245,246,250,251,252,253,254,255,271,272,273,274,275,280,281,282,
  283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,305,308,309,310,311,312,313,314,315,316,317,318,319,320,257,261,262,263,322,326};

  int cali[6] = {350,352,349,339,337,348}; //first three are racks 0, 1, and 2 for 60 Co. Other three are for 137 Cs

  /* to test calibration
  rack 0 - 111, 15, 5
  rack 1 - 105, 114, 106, 107, 9, 14, 11
  rack 2 - 110, 115, 112, 100, 3, 12, 6
  */

  int lisize;
  int size;

  if (type == "calibration") {
    lisize = 1;
  }

  if (type != "calibration" && target == "carbon") {
    lisize = sizeof(carbonblank) / sizeof(carbonblank[0]);
    size = lisize;
  }

  else if (type != "calibration" && target == "li") {
    lisize = sizeof(allli) / sizeof(allli[0]);
    size = lisize;
  }

  int run[lisize];

  if (type == "calibration") {
    run[0] = {349};
    std::cout << run[0] << std::endl; 
    size = 1; 
    std::cout << "woah" << std::endl;
  }

  else if (type != "calibration" && target == "carbon") {
    for (int i = 0; i < lisize; i++) {
      run[i]=carbonblank[i];
    }
  }

  else if (type != "calibration" && target == "li") {
    for (int i = 0; i < lisize; i++) {
      run[i]=allli[i];
    }
  }

  for (int i = 0; i < size; i++) {
    std::cout << run[i] << std::endl;
  }

  int yo[size];

  TH2D *PSDclone[NDET];
  TH1D *histograms[20][NDET];
  TH1D *clone[NDET];

  //int lithium0[10] = {132,   139,   143,     144,      145,     146,    147,   148,        149,           0};
  int colors[11] = {kBlack, kGreen, kBlue, kYellow, kMagenta, kOrange, kBlack, kPink, kGreenPink, kBlueYellow, kRed};
  //, kBlack, kBlue, kYellow, kMagenta, kOrange};

  double entries[NDET];

  double entries2[NDET];

  float norm;

  //float norm1[NDET];

  //=============================================================================================

  for (int i = 0; i < NDET; i++) {
    if (target == "carbon" ) {
      //if (isbackground == true) {
        norm = 0.61; //0.61 is the normalization used for carbon. Found by comparing peak heights
        //for li8 use 0.77. In instance of event normalization, use 0.692
        //try 6.75 for li 218-320
      //}
    }
    else if (target == "li") {
      //if (isbackground == true) {
        norm = 6.75;
        //norm1[i] = 8;
      //}
    }
    //if (isbackground == false) {
      //norm = 1;
    //}
  }

  //=============================================================================================

  float psd[NDET];

  TCanvas *canvas = new TCanvas();

  if ( (type == "add" || type == "addbig" || type == "allsmall" || type == "tDiff" || type == "tDiffg" || type == "totaltDiff"
    || type == "totalPSD" || type == "totalsubtraction" || type == "totalsubtractiong" || type == "normtest" ||
    type == "addbackground" || type == "addq" || type == "totaltDiffg" || type == "addg" || type == "flip" || type == "excitation" || type == "individualq" || type == "totalenergy") && det == "all") {
    //canvas = new TCanvas;
    canvas->Divide(5,4);
  }

  double energy = 0.;
  double tdf2 = 0.;
  double mn = 939.57;
  //double d[NDET];
  //for (int i = 0; i < NDET; i++) {
    //d[i] = 2;
  //}
  double energyMeV;
  double beamenergy = 7.;
  //double Q = 0.;
  double Q0 = -1.15;
  double Eex = 0.;
  double m3 = 3.0160 * 931.5;
  double m9 = 9.0133 * 931.5;
  double m14 = 14.0086 * 931.5;
  double mnsi = 1.6749e-27;

  double unifiedtshift[NDET];

  if (range != "short") {
    unifiedtshift[NDET] = {};
  }

  for (int i = 0; i < NDET; i++) {
    if (target == "carbon") {
    //carbon
    if (i == 13) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.185);
      cuts[i]->SetPoint(1,820,0.21);
      cuts[i]->SetPoint(2,1150,0.34);
      cuts[i]->SetPoint(3,1150,0.36);
      cuts[i]->SetPoint(4,650,0.27);
      cuts[i]->SetPoint(5,650,0.185);
    }
    else if (i == 11) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.17); //650
      cuts[i]->SetPoint(1,820,0.18);
      cuts[i]->SetPoint(2,1150,0.25);
      cuts[i]->SetPoint(3,1150,0.29);
      cuts[i]->SetPoint(4,820,0.248);
      cuts[i]->SetPoint(5,650,0.24);
      cuts[i]->SetPoint(6,650,0.17);
    }
    else if (i == 10) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.165);
      cuts[i]->SetPoint(1,820,0.2);
      cuts[i]->SetPoint(2,1150,0.36);
      cuts[i]->SetPoint(3,1150,0.36);
      cuts[i]->SetPoint(4,650,0.27);
      cuts[i]->SetPoint(5,650,0.165);
    }
    else if (i == 7 || i == 12 || i == 14 || i == 16) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.175);
      cuts[i]->SetPoint(1,820,0.19);
      cuts[i]->SetPoint(2,1150,0.275);
      cuts[i]->SetPoint(3,1150,0.36);
      cuts[i]->SetPoint(4,650,0.27);
      cuts[i]->SetPoint(5,650,0.175);
    }
    else if (i == 0 || i == 3 || i == 4 || i == 6) {
    //else {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.15);
      cuts[i]->SetPoint(1,820,0.17);
      cuts[i]->SetPoint(2,1150,0.255);
      cuts[i]->SetPoint(3,1150,0.3);
      cuts[i]->SetPoint(4,650,0.24);
      cuts[i]->SetPoint(5,650,0.15);      
    }
    else if (i == 5) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      //cuts[i]->SetPoint(0,300,0.14); // 650
      cuts[i]->SetPoint(0,650,.145);
      cuts[i]->SetPoint(1,820,0.165);
      cuts[i]->SetPoint(2,1150,0.245);
      cuts[i]->SetPoint(3,1150,0.255);
      cuts[i]->SetPoint(4,820,0.212);
      cuts[i]->SetPoint(5,650,0.21);
      cuts[i]->SetPoint(6,650,0.145);    
    }
    else if (i == 8) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.14);
      cuts[i]->SetPoint(1,820,0.16);
      cuts[i]->SetPoint(2,1150,0.22);
      cuts[i]->SetPoint(3,1150,0.28);
      cuts[i]->SetPoint(4,650,0.27);
      cuts[i]->SetPoint(5,650,0.14);
    }
    //else if (i == 2 || i == 15) {
    else {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,650,0.13);
      cuts[i]->SetPoint(1,820,0.13);
      cuts[i]->SetPoint(2,1150,0.15);
      cuts[i]->SetPoint(3,1150,0.21);
      cuts[i]->SetPoint(4,650,0.21);
      cuts[i]->SetPoint(5,650,0.13);  
    }
    }
    
// ===================================================================================================
else if (target == "li") {
//lithium
   if (i == 13) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.21);
      cuts[i]->SetPoint(1,720,0.23);
      cuts[i]->SetPoint(2,1150,0.33);
      cuts[i]->SetPoint(3,1800,0.45);
      cuts[i]->SetPoint(4,1800,0.47);
      cuts[i]->SetPoint(5,1150,0.36);
      cuts[i]->SetPoint(6,720,0.27);
      cuts[i]->SetPoint(7,720,0.21);
    }
    else if (i == 11) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.17); //650
      cuts[i]->SetPoint(1,720,0.18);
      
      cuts[i]->SetPoint(2,1150,0.25);
      cuts[i]->SetPoint(3,1800,0.38);
      cuts[i]->SetPoint(4,1800,0.45);
      cuts[i]->SetPoint(5,1150,0.32);
      
      cuts[i]->SetPoint(6,720,0.248);
      cuts[i]->SetPoint(7,720,0.24);
      cuts[i]->SetPoint(8,720,0.17);
    }
    else if (i == 10) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.19);
      cuts[i]->SetPoint(1,720,0.19);
      cuts[i]->SetPoint(2,1150,0.28);
      cuts[i]->SetPoint(3,1600,0.40);
      cuts[i]->SetPoint(4,1600,0.45);
      cuts[i]->SetPoint(5,1150,0.36);
      cuts[i]->SetPoint(6,720,0.27);
      cuts[i]->SetPoint(7,720,0.19);
    }
    else if (i == 7 || i == 12 || i == 16) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.19);
      cuts[i]->SetPoint(1,720,0.19);
      
      cuts[i]->SetPoint(2,1150,0.275);
      cuts[i]->SetPoint(3,1800,0.37);
      cuts[i]->SetPoint(4,2050,0.38);
      cuts[i]->SetPoint(5,2050,0.44);
      cuts[i]->SetPoint(6,1800,0.41);
      cuts[i]->SetPoint(7,1150,0.36);
      
      cuts[i]->SetPoint(8,720,0.27);
      cuts[i]->SetPoint(9,720,0.19);
    }
    else if (i == 14) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.19);
      cuts[i]->SetPoint(1,720,0.19);
      
      cuts[i]->SetPoint(2,1150,0.295);
      cuts[i]->SetPoint(3,1800,0.57);
      cuts[i]->SetPoint(4,2050,0.57);
      cuts[i]->SetPoint(5,2050,0.57);
      cuts[i]->SetPoint(6,1800,0.557);
      cuts[i]->SetPoint(7,1150,0.36);
      
      cuts[i]->SetPoint(8,720,0.27);
      cuts[i]->SetPoint(9,720,0.19);
    }
    else if (i == 4) {
    //else {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.172);
      cuts[i]->SetPoint(1,720,0.172);
      
      cuts[i]->SetPoint(2,1150,0.24);
      cuts[i]->SetPoint(3,1600,0.38);
      cuts[i]->SetPoint(4,1600,0.4);
      cuts[i]->SetPoint(5,1150,0.3);
      cuts[i]->SetPoint(6,820,0.22);
      
      cuts[i]->SetPoint(7,720,0.22);
      cuts[i]->SetPoint(8,720,0.172);      
    }    
    else if (i == 0) {
    //else {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.172);
      cuts[i]->SetPoint(1,720,0.172);
      
      cuts[i]->SetPoint(2,1150,0.25);
      cuts[i]->SetPoint(3,1600,0.42);
      cuts[i]->SetPoint(4,1600,0.46);
      cuts[i]->SetPoint(5,1150,0.3);
      cuts[i]->SetPoint(6,720,0.22);
      
      cuts[i]->SetPoint(7,720,0.22);
      cuts[i]->SetPoint(8,720,0.172);      
    }
    else if (i == 6) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.164);
      cuts[i]->SetPoint(1,820,0.164);
      
      cuts[i]->SetPoint(2,1150,0.23);
      cuts[i]->SetPoint(3,1600,0.33);
      cuts[i]->SetPoint(4,1800,0.35);
      cuts[i]->SetPoint(5,1800,0.4);
      cuts[i]->SetPoint(6,1150,0.3);
      cuts[i]->SetPoint(7,820,0.22);
      
      cuts[i]->SetPoint(8,820,0.22);
      cuts[i]->SetPoint(9,720,0.164);  
    }
    else if (i == 3) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      //cuts[i]->SetPoint(0,700,0.11);
      cuts[i]->SetPoint(0,720,0.162);
      
      cuts[i]->SetPoint(1,1150,0.24);
      cuts[i]->SetPoint(2,1800,0.38);
      cuts[i]->SetPoint(3,1800,0.4);
      cuts[i]->SetPoint(4,1150,0.3);
      cuts[i]->SetPoint(5,720,0.22);
      cuts[i]->SetPoint(6,720,0.162);
      
      //cuts[i]->SetPoint(6,700,0.22);
      //cuts[i]->SetPoint(7,700,0.11);   
    }
    else if (i == 5) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      //cuts[i]->SetPoint(0,300,0.14); // 650
      cuts[i]->SetPoint(0,720,.15);
      cuts[i]->SetPoint(1,820,0.15);
      
      cuts[i]->SetPoint(2,1150,0.22);
      cuts[i]->SetPoint(3,1800,0.38);
      cuts[i]->SetPoint(4,1800,0.4);
      cuts[i]->SetPoint(5,1150,0.28);
      
      cuts[i]->SetPoint(6,820,0.212);
      cuts[i]->SetPoint(7,720,0.2);
      cuts[i]->SetPoint(8,720,0.15);    
    }
    else if (i == 8) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.16);
      cuts[i]->SetPoint(1,720,0.16);
      
      cuts[i]->SetPoint(2,1150,0.22);
      cuts[i]->SetPoint(3,1800,0.315);
      cuts[i]->SetPoint(4,2100,0.35);
      cuts[i]->SetPoint(5,2500,0.4);
      cuts[i]->SetPoint(6,2500,0.47);
      cuts[i]->SetPoint(7,2100,0.42);
      cuts[i]->SetPoint(8,1800,0.38);
      cuts[i]->SetPoint(9,1150,0.3);
      
      cuts[i]->SetPoint(10,720,0.27);
      cuts[i]->SetPoint(11,720,0.16);
    }
    else if (i == 2) {
    //else {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.11);
      cuts[i]->SetPoint(1,820,0.115);
      
      cuts[i]->SetPoint(2,1150,0.14);
      cuts[i]->SetPoint(3,1690,0.18);
      cuts[i]->SetPoint(4,2200,0.26);
      cuts[i]->SetPoint(5,2200,0.31);
      cuts[i]->SetPoint(6,1700,0.24);
      cuts[i]->SetPoint(7,1150,0.21);
      
      cuts[i]->SetPoint(8,720,0.23);
      cuts[i]->SetPoint(9,720,0.11);  
    }
    else if (i == 15) {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.11);
      cuts[i]->SetPoint(1,820,0.115);
      
      cuts[i]->SetPoint(2,1150,0.14);
      cuts[i]->SetPoint(3,1690,0.21);
      cuts[i]->SetPoint(4,2200,0.29);
      cuts[i]->SetPoint(5,2700,0.36);
      cuts[i]->SetPoint(6,2700,0.4);
      cuts[i]->SetPoint(7,2200,0.35);
      cuts[i]->SetPoint(8,1700,0.27);
      cuts[i]->SetPoint(9,1150,0.21);
      
      cuts[i]->SetPoint(10,720,0.23);
      cuts[i]->SetPoint(11,720,0.11);  
    }
    else {
      cuts[i] = new TCutG(Form("mycut %d",i),5); 
      cuts[i]->SetVarX("eL"); // fall back to threshcut if not working
      cuts[i]->SetVarY("eTail");
      cuts[i]->SetPoint(0,720,0.11);
      cuts[i]->SetPoint(1,820,0.115);
      
      cuts[i]->SetPoint(2,1150,0.14);
      cuts[i]->SetPoint(3,1690,0.21);
      cuts[i]->SetPoint(4,2200,0.29);
      cuts[i]->SetPoint(5,2700,0.36);
      cuts[i]->SetPoint(6,2700,0.4);
      cuts[i]->SetPoint(7,2200,0.35);
      cuts[i]->SetPoint(8,1700,0.27);
      cuts[i]->SetPoint(9,1150,0.21);
      
      cuts[i]->SetPoint(10,720,0.23);
      cuts[i]->SetPoint(11,720,0.11);  
    }
   }
    //=========================================
  }

  //=============================================================================================
  //=============================================================================================
  //=============================================================================================

    for (int current_run = 0; current_run < size; current_run++) {
  
        std::cout << run[current_run] << std::endl;
        //std::cout << "yo" << std::endl;
  
        if (run[current_run] == 0) {
          continue;
        }
  
        else {
          for (int i = 0; i<NDET; i++) {
            //PSD[i] = new TH2D(Form("PSD-%d", i), Form(" Detector %d", ID2Board.at(i)), 2000, 0, 3500, 512, -0.1, 0.8);
            tDiff[i] = new TH1D(Form("Tdiff-%d", i), Form(" Detector %d", ID2Board.at(i)), timeBin, x, y); // -100, 400
            tDiffg[i] = new TH1D(Form("Tdiffg-%d", i), Form(" Detector %d", ID2Board.at(i)), timeBin, x, y);
            //tDiffg[i]->SetCanExtend(TH1::kAllAxes);
          }
      
          int run_start = run[current_run];
  
          //std::cout << run_start << std::endl;

          double blankshift[NDET] = {50,0,-44,54,16,52,14,38,0,0,0,18,48,0,0,36,42};

          double carbonshift[NDET] = {2,-2,-38,2,-38,2,-36,2,-36,0,-36,-36,2,-36,-38,2,2};

          //double yup[NDET] = {507,543,485,505,505,507,509,519,519,500,520,503,512,523,521,480.3,521};

          double yup[NDET] = {442, 0, 418, 438, 440, 442, 443, 456, 454, 0, 454, 438, 445, 456, 456, 416, 452};

          //double yup1[NDET] = {359, 0, 334, 353, 354, 360, 356, 368, 364, 0, 368, 351, 361, 371, 370, 330, 370}; 
          double yup1[NDET] = {442, 0, 418, 438, 440, 444, 443, 453, 451, 0, 454, 434, 445, 456, 456, 416, 452};

          double gamshift[NDET] = {6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 6.6, 3.3, 6.6, 6.6, 3.3, 6.6};
      
          double shifts[NDET];
  
          if (type == "flip") {
            for (int i = 0; i<NDET; i++) {
              unifiedtshift[i] = {0};
            }
          }

          else {
            if (run_start > 231) {
              for (int i = 0; i < NDET; i++) {
                unifiedtshift[i] = yup[i];
              }
            }
            else if (run_start < 231) {
              for (int i = 0; i < NDET; i++) {
                unifiedtshift[i] = yup1[i];  //due to changes in settings, position of gamma peaks on tof spectrum changes
              }
            }
          }

          if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
            for (int i = 0; i < NDET; i++) {
              shifts[i] = data[run[current_run]][i] + blankshift[i]; //data aligns all blank runs and blankshift aligns blank runs to li
            }
          }

          else if (run_start == 336 || run_start == 352 || run_start == 349 || run_start == 339 || run_start == 337 || run_start == 348 || run_start == 350) {
            for (int i = 0; i< NDET; i++) {
              shifts[i] = 0;
            }
          }
      
          else if (run_start == 264 || run_start == 276 || run_start == 278 || run_start == 299 || run_start == 302 || run_start == 304) {
            for(int i = 0; i < 17; i++) {
              shifts[i] = data[run[current_run]][i] + carbonshift[i];             
            }
          }

          else if (run_start == 215 || run_start == 301  || run_start == 124 || run_start == 266 || run_start == 267 || run_start == 268 || run_start == 300) {
            for (int i = 0; i < NDET; i++) {
              shifts[i] = 0;
            }
          }
          
          else {
            for (int i = 0; i < NDET; i++) {
              shifts[i] = data[run[current_run]][i];
              
            }
          }
          
          TString fileName;
      
          fileName.Form("catrina_%d_3000.root", run[current_run]);
      
          TFile *filename = new TFile(fileName);
      
          TTree *tree = (TTree *)filename->Get("tree");
      
          std::cout << "Pulling data from TTree..." << std::endl;
      
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
      
          std::cout << "Filling histograms..." << std::endl;
      
          std::ifstream file;
      
          file.open("calibration.txt");
          float numbers[51];
      
          int count = 0;
      
          float temp;
          char comma;
      
          while (file >> temp) {
          if (count < 51) {
            numbers[count++] = temp;
           }
           file >> comma;
          }
        
          file.close();
        
          float a[NDET] = {};
          float b[NDET] = {};
        
          for (int i = 0; i<NDET; i++) {
            int j = 3*i + 1;
            a[i] = numbers[j];
          }
        
          for (int i = 0; i<NDET; i++) {
            int k = 3*i + 2;
            b[i] = numbers[k];
          }
  
          while(reader.Next()) {
        
            double Q = 0;
            int count = 0;
            unsigned long long tRF = 0;
            unsigned long long tN[NDET];
            unsigned long long ts[NDET];
            for( int i = 0; i < NDET; i++ ) {
              tN[i] = 0;
              eL[i] = 0;
              eS[i] = 0;
              ts[i] = 0;
            }
        
            for(int i = 0; i < *multi; i++) { 
              if (run_start < 194) {
                int bd = SN2Bd2.at(sn[i]);
                int haha = mapping2[bd][ch[i]];
                if( haha < 0 ) continue;
                int ID = Index2ID.at(haha);
        
                if(ID == 200) {
                  count ++;
                  if (e_f[i] > 20000) {
                    continue;
                    //tRF = e_t[i] * 1000; //in ps
                  }
                  else {
                    tRF = e_t[i] * 1000 + e_f[i];
                  }
                }
        
                if( ID < 0 || ID > NDET ) continue;
        
                //dudu[ID]->Fill(e2[i], (e[i]-e2[i])*1.0/e[i]);
        
                eL[ID] = e[i];
                eS[ID] = e2[i];
                

                if (e_f[i] > 20000) {
                  continue;
                  //tN[ID] = e_t[i] * 1000; //in ps
                }
                else {
                  tN[ID] = e_t[i] * 1000 + e_f[i];
                }
        
              }
              else if (run_start >= 194) {
                int bd = SN2Bd.at(sn[i]);
                int haha = mapping[bd][ch[i]];
                if( haha < 0 ) continue;
                int ID = Index2ID.at(haha);
        
                if( ID == 200)
                {
                  count ++;
                  if (e_f[i] > 20000) {
                    tRF = e_t[i] * 1000; //in ps
                  }
                  else {
                    tRF = e_t[i] * 1000 + e_f[i];
                  }
                }
        
                if( ID < 0 || ID > NDET ) continue;
                //dudu[ID]->Fill(e2[i], (e[i]-e2[i])*1.0/e[i]);
                
                eL[ID] = e[i];
                eS[ID] = e2[i];
        
                if (e_f[i] > 20000) {
                  tN[ID] = e_t[i] * 1000;
                }
                else {
                  tN[ID] = e_t[i] * 1000 + e_f[i];
                }
              }             
            } // end multiplicity for loop

            //std::cout << "yup" << std::endl;
      
            for(int i = 0; i < NDET; i++) {
              if (i == 1 || i == 9) {
                continue;
                }
              else {
              if( tRF != 0 && tN[i] > 0 ) {
              //if (tRF != 0) {
                double tdf = 0.;
                
                if (range == "short") {
                if (run_start >= 231) {
                  if (i == 2) {
                    if(tRF > tN[i]) {
                      if (compress == "compress") {
                        tdf = -((tRF - tN[i])*1./1000. + shifts[i]) + unifiedtshift[i] + gamshift[i];
                        
                        if (tdf < 0.) {
                          tdf = tdf + 165.;
                        }
                        
                        if (tdf > 82.5) {
                          tdf = tdf - 82.5;
                        }
                        
                        
                      }
                      else {
                        tdf = -(((tRF - tN[i])*1./1000.) + shifts[i]) + unifiedtshift[i] + gamshift[i]; // 476 or litargetshift[i]
                      }
                    }
                    else {       
                      if (compress == "compress") {
                        tdf = -(((tN[i] - tRF)*1./1000. ) + shifts[i]) + unifiedtshift[i] + gamshift[i];
                        if (tdf < 0.) {
                          tdf = tdf + 165.;
                        }
                        
                        if (tdf > 82.5) {
                          tdf = tdf - 82.5;
                        }
                        
                      }
                      else {
                        tdf = -(((tN[i] - tRF)*1./1000. ) + shifts[i])+ unifiedtshift[i] + gamshift[i]; // 476
                      }
                    }
                  }
  
                  //================================================================================================================
                  else {
                    if(tRF > tN[i]) {
                      if (compress == "compress") {
                        tdf = -(((tRF - tN[i])*1./1000.) + shifts[i]) + unifiedtshift[i] + gamshift[i]; //558 for carbon include litargetshift
                        
                        if (tdf < 0.) {
                          tdf = tdf + 165.;
                        }                  
                        
                        if (tdf > 82.5) {
                          tdf = tdf - 82.5;
                        }
                        
                        
                      }
                      else {
                         tdf = -( (tRF - tN[i])*1./1000.+ shifts[i]) + unifiedtshift[i] + gamshift[i]; // 558
                      }
                    }
                    else {
  
                      if (compress == "compress") {
                        tdf = -((tN[i] - tRF)*1./1000. + shifts[i]) + unifiedtshift[i] + gamshift[i];
                        if (tdf < 0.) {
                          tdf = tdf + 165.;
                        }
                        
                        if (tdf > 82.5) {
                          tdf = tdf - 82.5;
                        }
                        
                        
                      }
                      else {
                        tdf = -( (tN[i] - tRF)*1./1000. + shifts[i]) + unifiedtshift[i] + gamshift[i]; //558
                      }
                    }
                  }
                } else if (run_start < 231) {
                  if (tN[i] < tRF) {
                    if (compress == "compress") {
                      tdf = -(((tRF - tN[i])*1./1000.) + shifts[i]) + unifiedtshift[i] + gamshift[i];   
                        if (tdf < 0.) {
                          tdf = tdf + 165.;
                        }                  
                        
                        if (tdf > 82.5) {
                          tdf = tdf - 82.5;
                        }
                      }
                      else {
                         tdf = -( (tRF - tN[i])*1./1000.+ shifts[i]) + unifiedtshift[i] + gamshift[i]; // 558
                      }
                  } else {
                    if (compress == "compress") {
                      tdf = -((tN[i] - tRF)*1./1000. + shifts[i]) + unifiedtshift[i] + gamshift[i];
                      if (tdf < 0.) {
                        tdf = tdf + 165.;
                      }
                      
                      if (tdf > 82.5) {
                        tdf = tdf - 82.5;
                      }                 
                    }
                    else {
                      tdf = -( (tN[i] - tRF)*1./1000. + shifts[i]) + unifiedtshift[i] + gamshift[i]; //558
                    }
                  }
                }
                //==========================================================================================================================
              }

                if (range == "out") {
                  if(tRF > tN[i]) {
                    tdf = (tRF - tN[i])*1./1000. + shifts[i];
                  }
                  else {
                    tdf = (tN[i] - tRF)*1./1000. + shifts[i];
                  }
                }
  
                if(calibration == "yes") {
                  if (compress == "selective") {
                  if (tdf < 0 || tdf > 82.5) {
                    continue;
                  }
                  }
                  
                   
                  PSDc[i]->Fill( ((a[i]*eL[i]) + b[i]), ((eL[i]-eS[i])*1.0/eL[i]));
                  tDiff[i]->Fill(tdf);
                    /*
                    if (target == "li") {
                      tdf2 = tdf * 1.e-9;
                      energyMeV = 6.241509e12 * ( (0.5) * mnsi * ((d[i] * d[i]) / (tdf2 * tdf2)) );
                      Q = energyMeV - beamenergy + ( (1/m9) * ( (m3 * beamenergy) + (mn * energyMeV) - (2 * sqrt(m3*mn*beamenergy*energyMeV) * cos( (3.14159 * Angle[i]) / 180. )) )); 
                      //std::cout << Q << std::endl;
                      Q = 9.35 - Q;
                      //std::cout << Q << std::endl;
                    }

                     if (i == 1 || i == 9 || i == 12 || i == 15) {
                    //if (i != 14 && i != 6 && i != 5 && i != 13) {
                      continue;
                    } else {
                      qvalues[i]->Fill(Q);
                      nenergy[i]->Fill(energyMeV);
                      lovstof[i]->Fill( Q , tdf );
                    }
                    */
                  
                  if(cuts[i]->IsInside(((a[i]*eL[i]) + b[i]), ((eL[i]-eS[i])*1.0/eL[i]))) {
                    tDiffg[i]->Fill(tdf);
                    //tdf = 39;
                    tdf2 = tdf * 1.e-9;
                    energyMeV = 6.241509e12 * ( (0.5) * mnsi * ((distance[i] * distance[i]) / (tdf2 * tdf2)) );
                    //if (energyMeV > 20 || energyMeV < -20) {
                      //continue;
                    //}
                    if (target == "carbon") {
                      Q = energyMeV - beamenergy + ( (1/m14) * ( (m3 * beamenergy) + (mn * energyMeV) - (2 * sqrt(m3*mn*beamenergy*energyMeV) * cos((3.14159 * Angle[i])/ 180.)) )); 
                      Q = -1.15 - Q;
                      //Q = energyMeV - beamenergy + ( (1/m9) * ( (m3 * beamenergy) + (mn * energyMeV) - (2 * sqrt(m3*mn*beamenergy*energyMeV) * cos( (3.14159 * Angle[i]) / 180. )) )); 
                      //Q = 9.35 - Q;
                    } else if (target == "li") {
                      Q = energyMeV - beamenergy + ( (1/m9) * ( (m3 * beamenergy) + (mn * energyMeV) - (2 * sqrt(m3*mn*beamenergy*energyMeV) * cos( (3.14159 * Angle[i]) / 180. )) )); 
                      Q = 9.35 - Q;
                      //if (i == 0) {
                        //std::cout << "time of flight " << tdf << " q value " << Q << std::endl;
                      //}
                    }
                    //if (Q < -20 || Q > 20) {
                      //continue;
                    //}
                    cal[i]->Fill((a[i]*eL[i])+b[i]);

                    //std::cout << Q << std::endl;
                    if (i == 1 || i == 9) {
                      continue;
                    //} else if (i == 7 || i == 8 || i == 4 || i == 13 ) { // corresponds to angles 97, 108.5, 133.5, 136. also, d = 2.08, 2.09, 1.99, 1.98
                    } else {
                      qvalues[i]->Fill( Q );
                      nenergy[i]->Fill(energyMeV);
                      lovstof[i]->Fill( Q , tdf );
                    }
                    //else {continue;}
                  }
                }
              }
              }
            }
          } //while reader end

      //for (int i = 0; i<NDET; i++) {
	//tof[i] = &tDiff[i];
      //}

      std::cout << "Plotting..." << std::endl;
      
      if(det == "all") {
        if (type == "energy" || type == "totalenergy" || type == "individualq") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              totq[i]->Add(qvalues[i],-norm);
            }
            else {
              totq[i]->Add(qvalues[i],1.0);
            }
          }
        }
        if (type == "nenergy") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              totnenergy[i]->Add(nenergy[i],-norm);
            }
            else {
              totnenergy[i]->Add(nenergy[i],1.0);
            }
          }
        }
        if (type == "lovstof") {
          for (int i = 0; i<NDET; i++) {
            total2d[i]->Add(lovstof[i],1.0);
          }
        }

       /*
        if (type == "envslong") {
          for (int i = 0; i < NDET; i++) {
            totenvslong[i]->Add(envslong[i],1.0);
          }
        }

        if (type == "long") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              //totallong[i]->Add(longgate[i],-norm[i]);
              continue;
            }
            else {
              totallong[i]->Add(longgate[i],1.0);
              //continue;
            }
          }
        }

        if (type == "tofvslong") {
          for (int i = 0; i < NDET; i++) {
            tottofvslong[i]->Add(tofvslong[i],1.0);
          }
        }

        if (type == "tofvsq") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              //continue;
              tottofvq[i]->Add(tofvq[i],-norm[i]);
            }
            else {
              tottofvq[i]->Add(tofvq[i],1.0);
              //continue;
            }
          }
        }

        else if (type == "excitation") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              totq1[i]->Add(ex[i],-norm[i]);
            }
            else {
              totq[i]->Add(ex[i],1.0);
            }
          }
          
        }

        else if (type == "exq") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              totexq[i]->Add(exvsq[i],-norm[i]);
            }
            else {
              totexq[i]->Add(exvsq[i],1.0);
              //continue;
            }
          }
        }

        else if (type == "addq") {
           for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              totq1[i]->Add(qvalues[i],-norm[i]);
            }
            else {
              totq[i]->Add(qvalues[i],1.0);
            }
          }
        }
        */
        else if (type == "add") {
          for (int i = 0; i<NDET; i++) {
            canvas->cd(i+1);
            histograms[current_run][i] = (TH1D *)tDiff[Det2AngleOrder.at(i)]->Clone(Form("histnew - %d", i));
            histograms[current_run][i]->SetLineColor(colors[current_run]);
            histograms[current_run][i]->Draw("same");
          }
        }
        /*
        else if (type == "addg") {
          for (int i = 0; i<NDET; i++) {
            canvas->cd(i+1);
            histograms[current_run][i] = (TH1D *)tDiffg[i]->Clone(Form("histnew - %d", i));
            entries[i] += histograms[current_run][i]->GetEntries();
            histograms[current_run][i]->SetLineColor(colors[current_run]);
            histograms[current_run][i]->Draw("same");
          }
        }
        else if (type == "flip") {
          for (int i = 0; i < NDET; i++) {
            canvas->cd(i+1);
            histograms[current_run][i] = (TH1D *)tDiff[i]->Clone(Form("histnew - %d", i));
            entries[i] += histograms[current_run][i]->GetEntries();
            histograms[current_run][i]->SetLineColor(colors[current_run]);
            histograms[current_run][i]->Draw("same");
          }
        }
        else if (type == "addbig") {
          for (int i = 0; i<7; i++) {
            canvas->cd(i+1);
            histograms[current_run][i] = (TH1D *)tDiff[i]->Clone(Form("histnew - %d", i));
            entries[i] += histograms[current_run][i]->GetEntries();
            histograms[current_run][i]->SetLineColor(colors[current_run]);
            histograms[current_run][i]->Draw("same");
          }
        }
        else if (type == "addsmall") {
          for (int i = 7; i<NDET; i++) {
            canvas->cd(i-6);
            histograms[current_run][i] = (TH1D *)tDiff[i]->Clone(Form("histnew - %d", i));
            entries[i] += histograms[current_run][i]->GetEntries();
            histograms[current_run][i]->SetLineColor(colors[current_run]);
            histograms[current_run][i]->Draw("same");
          }
        }
        */
        else if (type == "totalsubtractiong") {//for (int i = 0; i<NDET; i++) {total[i]=totaltof(NDET, run[current_run], tDiff[NDET], total[NDET], isbackground)};}
          for (int i = 0; i<NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              total[i]->Add(tDiffg[i],-norm);
            }
            else {
              total[i]->Add(tDiffg[i],1);
            }
          }
        }
        /*
        else if (type == "addbackground") {
          for (int i = 0; i<NDET; i++) {
            if (run_start == 264 || run_start == 276 || run_start == 278 || run_start == 299 || run_start == 302 || run_start == 304) {
              total[i]->Add(tDiffg[i],1.);
            }
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              total2[i]->Add(tDiffg[i],norm[i]);
            }
          }
        } 
        
        else if (type == "totalsubtraction") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 305 || run_start == 308 || run_start == 309 || run_start == 310 || run_start == 311 || run_start == 312 || run_start == 313 || run_start == 314 ||
          run_start == 315 || run_start == 316 || run_start == 317 || run_start == 318 || run_start == 319 || run_start == 320) {
              total[i]->Add(tDiff[i],1.);
              entries[i] += tDiff[i]->GetEntries();
            }
            if (run_start == 264 || run_start == 276 || run_start == 278 || run_start == 299 || run_start == 302 || run_start == 304) {
              total[i]->Add(tDiff[i],1.);
              entries[i] += tDiff[i]->GetEntries();
            }
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              total[i]->Add(tDiff[i],-norm[i]);
              entries[i] += tDiff[i]->GetEntries();
            }
          }
        }
        */
        if (type == "normtest") {
          for (int i = 0; i < NDET; i++) {
            if (run_start == 264 || run_start == 276 || run_start == 278 || run_start == 299 || run_start == 302 || run_start == 304) {
              total2[i]->Add(tDiff[i],norm);
              total4[i]->Add(tDiffg[i],norm);
            }
            else {
              total[i]->Add(tDiff[i]);
              total3[i]->Add(tDiffg[i]);
            }
          }
        }
        /*
        else if (type == "PSD") {
          for(int i=0; i<NDET;i++) {
            PSD[i]->Draw();
	          cuts[i]->Draw("same");
          }
        }
        */
        if(type == "totaltDiff") {
          for(int i = 0; i<NDET; i++) {
            total[i]->Add(tDiff[i]);
            total2[i]->Add(tDiffg[i]);
            //entries[i] += tDiff[i]->GetEntries();
          }
        }
        /*
        if(type == "totaltDiffg") {
          for(int i = 0; i<NDET; i++) {
            total[i]->Add(tDiffg[i]);
          }
        }
        
        if(type == "tDiffg") {
          for(int i = 0; i<NDET; i++) {
            canvas->cd(i+1);
            //tDiff[i]->Draw();
            tDiffg[i]->Draw();
          }
        }
        */
        if (calibration == "yes") {
          if (type == "totalPSD") {
            for (int i = 0; i < NDET; i++) {
              totalPSDc[i]->Add(PSDc[i]);
            }
          }
        }
        if (calibration == "no") {
          if(type == "totalPSD") {
            for(int i = 0; i<NDET; i++) {
              totalPSD[i]->Add(PSD[i]);
            }
          }
        }
      }

      if(det != "all") {
        int k = det.Atoi();
        int i = Channel2ID.at(k);
        int channel = Det2Channel.at(i);
        int board = Det2Board.at(i);
        
        if (type == "normtest") {
          if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
            total2[i]->Add(tDiff[i],norm);
            total4[i]->Add(tDiffg[i],norm);
          }
          else {
            total[i]->Add(tDiff[i],1);
            total3[i]->Add(tDiffg[i],1);
          }
        }
        if (type == "nenergy") {
          //for (int i = 0; i < NDET; i++) {
            if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              totnenergy[i]->Add(nenergy[i],-norm);
            }
            else {
              totnenergy[i]->Add(nenergy[i],1.0);
            }
          //}
        }
        /*
        if (type == "normtestg") {
          if (run_start == 264 || run_start == 276 || run_start == 278 || run_start == 299 || run_start == 302 || run_start == 304) {
            total[i]->Add(tDiffg[i]);
          }
          else if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
            total3[i]->Add(tDiffg[i]);
          }
          else {
            total[i]->Add(tDiffg[i]);
          }
        }
        if (type == "flip") {
          histograms[current_run][i] = (TH1D *)tDiff[i]->Clone(Form("histnew - %d", i));
          entries[i] += histograms[current_run][i]->GetEntries();
          histograms[current_run][i]->SetLineColor(colors[current_run]);
          histograms[current_run][i]->Draw("same");
        }
        if (type == "calibration") {
          //cal[i]->Draw();
          if (calibration == "no") {
            tree->Draw("e>>canvas(400,0,20000,512,0,10000)",Form("ch == %d && sn == %d",channel,board));
          }
          if (calibration == "yes") {
            tree->Draw(Form("( (%f*e)+%f )>>canvas(400,0,2000,512,0,6000)",a[i],b[i]),Form("ch == %d && sn == %d",channel,board));
          }
        }
        
        if (type == "add") {
          if (run_start == 215 || run_start == 301 || run_start == 124 || run_start == 266 || run_start == 267 || run_start == 268 || run_start == 300) {
            histograms[current_run][i] = (TH1D *)tDiff[i]->Clone(Form("histnew - %d",i));
          }
          else {
            histograms[current_run][i] = (TH1D *)tDiff[i]->Clone(Form("histnew - %d",i));
          }
          entries[i] += histograms[current_run][i]->GetEntries();
          histograms[current_run][i]->SetLineColor(colors[current_run]);
          histograms[current_run][i]->Draw("same");
        }
        
        if (type == "totalsubtraction") {
            if (run_start == 264 || run_start == 276 || run_start == 278 || run_start == 299 || run_start == 302 || run_start == 304) {
              total[i]->Add(tDiff[i],1.0);
            }
            else if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
              total[i]->Add(tDiff[i],-norm[i]);
            }

        }
        
        if (type == "totalsubtractiong") {
          if (run_start == 257 || run_start == 261 || run_start == 262 || run_start == 263 || run_start == 322 || run_start == 326) {
            total[i]->Add(tDiffg[i],-norm[i]);
          }
          else {
            total[i]->Add(tDiffg[i],1.0);
          }
        }
        */
        if (type == "totaltDiff") {
          total[i]->Add(tDiff[i]);
          total2[i]->Add(tDiffg[i]);
        }
        /*
        if (type == "totaltDiffg") {
          total[i]->Add(tDiffg[i]);
        }
        if (type == "tDiff") {
          tDiff[i]->Draw();
        }
        if(type == "subtract") {
          if(run[current_run] == 264) {
            total[i]->Add(tDiff[i]);
          }
          total[i]->Draw();
        }
        if(type == "subtractcarbon") {
          if(run[current_run] == 264) {
            total[i]->Add(tDiffg[i],1.);
          }
          if(run[current_run] == 261) {
            total[i]->Add(tDiffg[i],-norm[i]);
          }
          else {
            total[i]->Add(tDiffg[i],1.0);
          }
        }
        if (type == "tDiffg") {
          tDiffg[i]->Draw();
        }
        */
        if (calibration == "yes") {
          if (type == "totalPSD") {
            //totalPSDc[i]->SetMarkerColor(2);
            totalPSDc[i]->Add(PSDc[i]);
          }
        }
        if (calibration == "no") {
          if (type == "totalPSD") {
            totalPSD[i]->Add(PSD[i]);
          }
        }
        /*
        if (type == "heheg") {
          heheg[i]->Draw();
        }
        */
      }

      if (type == "totaltDiff" || type == "totaltDiffg" || type == "add" || type == "totalPSD" || type == "PSD" 
      || type == "totalsubtractiong" || type == "subtractcarbon" || type == "subtract" || type == "totalsubtraction" || type == "normtest" 
      || type == "normtestg" || type == "energy" || type == "nenergy" || type == "addbackground" || type == "addq" || type == "tofvsq" || type == "envslong" || type == "individualq" || type == "totalenergy") {
        for(int i = 0; i < NDET; i++) {
          //delete tDiff[i];
          tDiff[i]->Reset();
          tDiffg[i]->Reset();
          //delete tDiffg[i];
          PSD[i]->Reset();
          //PSDc[i]->Reset();
          //delete qvalues[i];
          qvalues[i]->Reset();
          //delete nenergy[i];
          nenergy[i]->Reset();
          //ex[i]->Reset();
          //tofvq[i]->Reset();
          //envslong[i]->Reset();
        }
      }
    } 
  }

  std::cout << "end for loop" << std::endl;
  
  //=============================================================================================
  //=============================================================================================
  //=============================================================================================

  if (det != "all") {
    TFile *outputhist = new TFile("outputhist.root","UPDATE");
    int k = det.Atoi();
    int i = Channel2ID.at(k);
    if (type == "normtest" || type == "normtestg") {
      total[i]->Draw();
      total2[i]->Draw("same");
      total3[i]->Draw("same");
      total4[i]->Draw("same");
    }
    if (type == "nenergy") {
      totnenergy[i]->Draw();
    }
    
    if (type == "totaltDiff") {
      total[i]->Draw();
      total2[i]->Draw("same");
    }
    /*
    if (type == "totaltDiffg") {
      total[i]->Draw();
    }
    if (type == "tDiff") {
      tDiff[i]->Draw();
    }
    if (type == "tDiffg") {
      tDiffg[i]->Draw();
    }
    if (type == "totalsubtraction") {
      total[i]->Draw();
    }
    if (type == "totalsubtractiong") {
      total[i]->Draw();
    }
    */
    if (calibration == "yes") {
      if (type == "totalPSD") {
        totalPSDc[i]->Draw();
        cuts[i]->Draw("same");
      }
    }
    if (calibration == "no") {
      if (type == "totalPSD") {
        totalPSD[i]->Draw();
        cuts[i]->Draw("same");
      }
    }
  }
  
  std::string path;
  const char *end = "fits/";
  gSystem->mkdir(end, kTRUE);

  if (det == "all") {
    if (type == "individualq") {
      TCanvas *canvas = new TCanvas();
      
      canvas->Divide(5,4);
      //float a[NDET] = {0,0,2,8,.5,4,1,8,1,4,4,2,.5,4,1,0,0};
      float a[NDET] = {4000,20000,100,400,50,200,100,250,70,250,250,120,30,250,40,0,0}; //gs amp
      //float b[NDET] = {4000,25000,250,400,80,300,120,200, 80,  200,350,120,20,325,60,0,0}; //1.5 amp
      float c[NDET] = {4000,25000,100,275,25,115,55,  150,51,150,115,110,20,130,45,0,0}; //2.345 amp
      float d[NDET] = {3500,15000,100,200,35,175,70,225,50,100,175,100,20,150,50,0,0}; //2.751 amp
      //float e[NDET] = {}; //2.78 amp
      float f[NDET] = {3500,15000,300,600,125,500,100,200,100,200,200,200,20,200,100,0,0}; //4.8 amp
      float g[NDET] = {10000,60000,450,1000,250,1200,250,700,200,650,500,450,90,700,280,0,0}; //6.985 amp
      float gsintegral[NDET]; //gs
      //float firstsint[NDET]; //1.5
      float ssint[NDET]; //2.345
      float tsint[NDET]; //2.751
      float fsint[NDET]; //4.8
      float sixstateint[NDET]; //6.985

      Double_t * fit[NDET];
 
      //spectroscopic factor of 2.345 - 0.8
      //spectroscopic factor of 11.64 - 

        TF1 *gs = new TF1("groundstate","gaus",-200,400);
        //TF1 *first = new TF1("first","gaus",-200,400);
        //first->SetLineColor(kOrange);
        TF1 *second = new TF1("second","gaus",-200,400);
        second->SetLineColor(kGreen);
        TF1 *third = new TF1("third","gaus",-200,400);
        third->SetLineColor(kBlue);
        TF1 *fourth = new TF1("fourth","gaus",-200,400);
        TF1 *fifth = new TF1("fifth","gaus",-200,400);
        fifth->SetLineColor(kYellow);
        TF1 *sixth = new TF1("sixth","gaus",-200,400);
        sixth->SetLineColor(kLake);
        //TF1 *seventh = new TF1("sixth","gaus",-200,400);
        //seventh->SetLineColor(kCopper);
        //TF1 *eight = new TF1("sixth","gaus",-200,400);
        //eight->SetLineColor(kCoffee);
        TF1 *totalstate = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)",-200,400);
        totalstate->SetLineColor(kBlack);

        //TH1 * fithist[NDET];

      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        totq[Det2AngleOrder.at(i)]->Draw();
        //totq[Det2AngleOrder.at(i)]->Background();
        
        gs->SetParameters(a[i],0,0.35); //0
        gs->SetNpx(5000);
        //first->SetParameters(b[i],1.5,0.6);
        //first->SetNpx(5000);
        second->SetParameters(c[i],2.345,0.35); //2.345
        second->SetNpx(5000);
        third->SetParameters(d[i],2.78,1.57); //2.78
        third->SetNpx(5000);
        //fourth->SetParameters(e[i],2.78,1.57); //2.78
        //fourth->SetNpx(5000);
        fifth->SetParameters(f[i],4.8,0.6); //4.8
        fifth->SetNpx(5000);
        sixth->SetParameters(g[i],6.985,1.09); //6.985
        sixth->SetNpx(5000);
        //seventh->SetParameters(,seventhstate[i],23);  //12.16
        //seventh->SetNpx(5000);
        //eight->SetParameters(a[i]/4,48.8,2);
        double pars[15] = {
            a[i],0,.35, c[i],2.345,0.35, d[i],2.78,1.57, f[i],4.8,0.6, g[i],6.985,1.09
        };
        totalstate->SetParameters(pars);
        totalstate->SetNpx(5000);
        //sixth->SetLineStyle(kDashed);
        //seventh->SetLineStyle(kDashed);
        totalstate->SetLineStyle(kDashed);
        totalstate->SetLineWidth(1);
        /*
        totalstate->Draw("same");
        gs->Draw("same");
        gsintegral[i] = gs->Integral(-1,1);
        //first->Draw("same");
        //firstsint[i] = first->Integral(0,4);
        second->Draw("same");
        ssint[i] = second->Integral(2,4);
        third->Draw("same");
        tsint[i] = third->Integral(-2,8);
        //fourth->Draw("same");
        fifth->Draw("same");
        fsint[i] = fifth->Integral(3,7);
        sixth->Draw("same");
        sixstateint[i] = sixth->Integral(2,12);
        */
        for (int l = 1; l <= totq[Det2AngleOrder.at(i)]->GetNbinsX(); l++) {
          double x = totq[Det2AngleOrder.at(i)]->GetBinCenter(l);
          double y = totalstate->Eval(x);
          fithist[Det2AngleOrder.at(i)]->SetBinContent(l, y);
        }
        
        //fithist[i] = totalstate->GetHistogram();
        //fithist[Det2AngleOrder.at(i)]->SetLineColor(kRed);
        //fithist[Det2AngleOrder.at(i)]->Draw("same");
        totq[Det2AngleOrder.at(i)]->Add(fithist[Det2AngleOrder.at(i)],-1.0);
        totq[Det2AngleOrder.at(i)]->Draw();
      }
      //for (int i = 0; i < NDET; i++) {
        //printf("Angle: %f gs: %f second: %f Third: %f fifth: %f sixth: %f \n", Angle[Det2AngleOrder.at(i)], gsintegral[i], ssint[i], tsint[i], fsint[i], sixstateint[i]);
      //}       
        //totq[13]->Draw();
        /*
        TF1 *gs = new TF1("groundstate","gaus",-20,20);
        TF1 *first = new TF1("first","gaus",-20,20);
        TF1 *second = new TF1("second","gaus",-20,20);
        TF1 *third = new TF1("third","gaus",-20,20);
        TF1 *fourth = new TF1("fourth","gaus",-20,20);
        TF1 *fifth = new TF1("fifth","gaus",-20,20);
        TF1 *sixth = new TF1("sixth","gaus",-20,20);
        TF1 *seventh = new TF1("sixth","gaus",-20,20);
        TF1 *eight = new TF1("sixth","gaus",-20,20);
        TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)+gaus(21)+gaus(24)",-20,20);
        
        gs->SetParameters(326.5/5,0,0.16);
        gs->SetNpx(5000);
        first->SetParameters(43.8/5,1.5,0.6);
        second->SetParameters(85.7/5,2.35,0.16);
        second->SetNpx(5000);
        //third->SetParameters(1371/16,2.751,0.307);
        //fourth->SetParameters(1371/16,2.78,1.57);
        fourth->SetParameters(171.38/5,2.8,1.57);
        fifth->SetParameters(200/5,4.8,0.6);
        fifth->SetNpx(5000);
        sixth->SetParameters(445/5,6.985,1.09);
        seventh->SetParameters(.25/5,11.64,0.39);
        eight->SetParameters(.25/5,12.16,0.228);
        double pars[27] = {
            326.5,0,0.16, 43.8,1.5,0.6, 85.7,2.35,0.16, 171.38,2.8,1.57, 200,4.8,0.6, 455,6.985,1.09, 0.25,11.64,0.39, 0.25,12.16,0.228
        };
        for (int i = 0; i < 8; i++) {
          pars[3*i] = pars[3*i] / 5;
        }

        total->SetParameters(pars);
        total->SetNpx(5000);
    
        //TCanvas *c = new TCanvas();
        //c->SetYAxis();
    
        //c->cd();
        total->Draw("same");
        gs->Draw("same");
        //gs->GetYaxis()->SetRangeUser(0,7000);
        first->Draw("same");
        second->Draw("same");
        third->Draw("same");
        fourth->Draw("same");
        fifth->Draw("same");
        sixth->Draw("same");
        seventh->Draw("same");
        eight->Draw("same");
        //total->Draw("same");
        */
    }
    if (type == "totalenergy") {
      TCanvas *canvas1 = new TCanvas();
      //canvas1->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        energyplot->Add(totq[i]);
        //totq[i]->Draw("same");
        totq[i]->Reset();
        //canvas1->cd(i+1);
        //totq[i]->Draw();
        
        //totq[]->Draw();
      }      
        energyplot->Draw();
        
        TF1 *gs = new TF1("groundstate","gaus",-20,20);
        TF1 *first = new TF1("first","gaus",-20,20);
        TF1 *second = new TF1("second","gaus",-20,20);
        TF1 *third = new TF1("third","gaus",-20,20);
        TF1 *fourth = new TF1("fourth","gaus",-20,20);
        TF1 *fifth = new TF1("fifth","gaus",-20,20);
        TF1 *sixth = new TF1("sixth","gaus",-20,20);
        TF1 *seventh = new TF1("sixth","gaus",-20,20);
        TF1 *eight = new TF1("sixth","gaus",-20,20);
        TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)+gaus(21)+gaus(24)",-20,20);
    
        gs->SetParameters(400,0,0.16); //1306
        gs->SetNpx(3000);
        first->SetParameters(300,1.5,.6);
        first->SetNpx(3000);
        second->SetParameters(50,2.345,0.16);
        second->SetNpx(3000);
        third->SetParameters(200,2.751,0.306);
        third->SetNpx(3000);
        fourth->SetParameters(200,2.78,1.57);
        fourth->SetNpx(3000);
        fifth->SetParameters(400,4.8,.6);
        fifth->SetNpx(3000);
        sixth->SetParameters(1200,6.985,1.09);
        sixth->SetNpx(3000);
        seventh->SetParameters(1.,11.64,0.39);
        eight->SetParameters(1.,12.16,0.228);
        double pars[27] = {
            400,0,0.16, 300,1.5,.6, 50,2.345,0.16, 200,2.751,0.306, 200,2.78,1.57, 400,4.8,.6, 1200,6.985,1.09, 1.,11.64,0.39, 1.,12.16,0.228
        };
        //for (int i = 0; i < 8; i++) {
          //pars[3*i] = pars[3*i] / 40.;
        //}
        total->SetParameters(pars);
        total->SetNpx(3000);
    
        //TCanvas *c = new TCanvas();
        //c->SetYAxis();
    
        //c->cd();
        gs->Draw("same");
        //gs->GetYaxis()->SetRangeUser(0,7000);
        first->Draw("same");
        second->Draw("same");
        third->Draw("same");
        fourth->Draw("same");
        fifth->Draw("same");
        sixth->Draw("same");
        seventh->Draw("same");
        eight->Draw("same");
        total->Draw("same");
        
    }
    if (type == "nenergy") {
      TCanvas *canvas1 = new TCanvas();
      canvas1->Divide(5,4);
      /*
      TF1 *nbody1 = new TF1("2a + n + p", "gaus", 9.94, 16.6);
        nbody1 -> SetLineColor(kAzure);
        TF1 *nbody2 = new TF1("8Be + n + p", "gaus", 9.86, 16.5);
        nbody2 -> SetLineColor(kAzure);
        TF1 *nbody3 = new TF1("a + n + 5Li", "gaus", 11.07, 14.59);
        nbody3 -> SetLineColor(kAzure);
        TF1 *gs = new TF1("gs", "gaus", -20, 20);
        nbody1->SetParameters(400,13,1.5);
        nbody2->SetParameters(400,13,1.5);
        nbody3->SetParameters(400,13,1.5);
        gs->SetParameters(200,10,1);
        */
      for (int i = 0; i < NDET; i++) {
        //energyplot->Add(totq[i]);
        //totq[i]->Reset();
        canvas1->cd(i+1);
        totnenergy[Det2AngleOrder.at(i)]->Draw();
        //nbody1->Draw("same");
        //nbody2->Draw("same");
        //nbody3->Draw("same");
        //gs->Draw("same");
      }

      //energyplot->Draw();
    }
    if (type == "lovstof") {
      TCanvas *c = new TCanvas();
      c->Divide(5,4);
      for (int i = 0; i<NDET; i++) {
        c->cd(i+1);
        total2d[Det2AngleOrder.at(i)]->Draw();
      }
    }
    /*
    if (type == "tofvsq") {
      canvas->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        tottofvq[i]->Draw();
        //alltofvq->Add(tottofvq[i],1.0);
        //tottofvq[i]->Reset();
      }
      //alltofvq->Draw();
    }
    if(type == "tDiff") {
      for(int i = 0; i<NDET; i++) {
        canvas->cd(i+1);
        tDiff[i]->Draw();
      }
    }
    if (type == "tofvslong") {
      canvas->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        tottofvslong[i]->Draw();
      }
    }
    if (type == "envslong") {
      canvas->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        totenvslong[i]->Draw();
      }
    }
    if (type == "excitation") {
      TCanvas *canvas1 = new TCanvas();
      canvas1->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        canvas1->cd(i+1);
        //totq[i]->Draw();
        //canvas->cd(i+1);
        //totq1[i]->Draw();
        //energyplot->Add(totq[i]);
        //energyplot->Add(totq1[i]);
        //totq[i]->Reset();
        //totq1[i]->Reset();
        //canvas1->cd(i+1);
        //totq[i]->Draw();
      }
      energyplot->Draw();
    }
    if (type == "exq") {
      TCanvas *canvas1 = new TCanvas();
      for (int i = 0; i < NDET; i++) {
        qexplot->Add(exvsq[i]);
        exvsq[i]->Reset();
        //exvsq[i]->Draw();
      }
      qexplot->Draw();
    }
    if (type == "nenergy") {
      TCanvas *canvas2 = new TCanvas();
      canvas2->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        canvas2->cd(i+1);
        totq[i]->Draw();
      }
    }
    if (type == "addbackground") {
      for (int i = 0; i<NDET; i++) {
        canvas->cd(i+1);
        total[i]->SetLineColor(kYellow);
        total[i]->Draw("same");
        total2[i]->SetLineColor(kBlack);
        total2[i]->Draw("same");
      }
    }
    if (type == "addq") {
      for (int i = 0; i<NDET; i++) {
        energyplot1->Add(totq1[i]);
        energyplot->Add(totq[i]);
      }
      energyplot1->Draw();
      energyplot->Draw("same");
    }
    if (type == "long") {
      canvas->Divide(5,4);
      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        totallong[i]->Draw();
      }
    }
    if (type == "addbig") {
      canvas->SaveAs("all_runs_overlapbig.jpg");
    }
    if (type == "addsmall") {
      canvas->SaveAs("all_runs_overlapsmall.jpg");
    }
    */
    if (type == "totaltDiff") {
      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        //std::cout << "yup" << std::endl;
        total[Det2AngleOrder.at(i)]->Draw();
        total2[Det2AngleOrder.at(i)]->Draw("same");
        //std::cout << entries2[i] << std::endl;
      }
    }
    
    if (type == "normtest" ) {
      for (int i = 0; i < NDET; i++) {
        canvas->cd(i+1);
        total[Det2AngleOrder.at(i)]->Draw();
        total3[Det2AngleOrder.at(i)]->Draw("same");
        total3[Det2AngleOrder.at(i)]->SetLineColor(colors[1]);
        total2[Det2AngleOrder.at(i)]->Draw("same");
        total2[Det2AngleOrder.at(i)]->SetLineColor(colors[0]);
        total4[Det2AngleOrder.at(i)]->Draw("same");
      }
    }
    
    if (type == "totalsubtractiong" || type == "totalsubtraction") {
      
      //double a[NDET] = {0,0,300,500,150,500,150,400,120,300,350,250,50,350,120,0,0};
      double ground[NDET] = {15.77,16.23,43.04,41.55,43.57,42.76,44.36,43.15,43.28,43.42,42.91,44.32,44.27,43.3,43.64,0,0}; //0
      double secondstate[NDET] = {17.13,17.66,47.23,45.63,47.87,47,48.8,47.49,47.74,47.94,47.39,48.97,48.94,47.87,48.27,0,0}; //2.345
      double thirdstate[NDET] = {17.41,17.95,48.1,46.48,48.76,47.88,49.72,48.4,48.67,48.88,48.32,49.94,49.91,48.82,49.24,0,0}; //2.751
      double fourthstate[NDET] = {19.04,19.67,53.29,51.55,54.1,53.16,55.24,53.81,54.27,54.55,53.95,55.81,55.8,54.58,55.08,0,0};  //4.8
      double fifthstate[NDET] = {21.43,22.21,61.17,59.26,62.23,61.21,63.7,62.12,62.9,63.37,63.32,62.67,64.9,64.93,63.53,0,0}; //6.985
      double sixthstate[NDET] = {33.63,35.43,24.6,22.2,27.8,26.6,31.9,29.8,33.9,35.6,34.8,39.8,40.4,37.8,39.6,0,0}; //11.64
      double seventhstate[NDET] = {36.97,39.16,39.3,37,43.5,42.4,48.8,46.6,52.2,54.6,53.8,59.9,60.7,57.7,60.1,0,0}; //12.16

      float a[NDET] = {4000,20000,100,400,50,200,100,250,70,250,250,120,30,250,40,0,0}; //gs amp
      //float b[NDET] = {4000,25000,250,400,80,300,120,200, 80,  200,350,120,20,325,60,0,0}; //1.5 amp
      float c[NDET] = {4000,25000,100,275,25,115,55,  150,51,150,115,110,20,130,45,0,0}; //2.345 amp
      float d[NDET] = {3500,15000,100,200,35,175,70,225,50,100,175,100,20,150,50,0,0}; //2.751 amp
      //float e[NDET] = {}; //2.78 amp
      float f[NDET] = {3500,15000,300,600,125,500,100,200,100,200,200,200,20,200,100,0,0}; //4.8 amp
      float g[NDET] = {10000,60000,450,1000,250,1200,250,700,200,650,500,450,90,700,280,0,0}; //6.985 amp

      float h[NDET]; //12.16 amp (since the 11.64 MeV state comes before the ground state and will not appear in spectrum)
      
      for (int i = 0; i <NDET; i++) {
        canvas->cd(i+1);
        //total[i]->SetEntries(entries[i]);
        //std::cout << entries[i] << std::endl;
        total[Det2AngleOrder.at(i)]->Draw();
        
        TF1 *gs = new TF1("groundstate","gaus",-200,400);
        TF1 *first = new TF1("first","gaus",-200,400);
        first->SetLineColor(kOrange);
        TF1 *second = new TF1("second","gaus",-200,400);
        second->SetLineColor(kGreen);
        TF1 *third = new TF1("third","gaus",-200,400);
        third->SetLineColor(kBlue);
        TF1 *fourth = new TF1("fourth","gaus",-200,400);
        TF1 *fifth = new TF1("fifth","gaus",-200,400);
        fifth->SetLineColor(kYellow);
        TF1 *sixth = new TF1("sixth","gaus",-200,400);
        sixth->SetLineColor(kLake);
        //TF1 *seventh = new TF1("sixth","gaus",-200,400);
        //seventh->SetLineColor(kCopper);
        //TF1 *eight = new TF1("sixth","gaus",-200,400);
        //eight->SetLineColor(kCoffee);
        TF1 *totalstate = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)",-200,400);
        totalstate->SetLineColor(kBlack);

        TF1 *nbody1 = new TF1("2a + n + p", "gaus", -200, 400);
        nbody1 -> SetLineColor(kAzure);
        TF1 *nbody2 = new TF1("8Be + n + p", "gaus", -200, 400);
        nbody2 -> SetLineColor(kAzure);
        TF1 *nbody3 = new TF1("a + n + 5Li", "gaus", -200, 400);
        nbody3 -> SetLineColor(kAzure);
        
        gs->SetParameters(a[i],ground[i],1); //0
        gs->SetNpx(5000);
        first->SetParameters(c[i],secondstate[i],1); //2.345
        first->SetNpx(5000);
        //second->SetParameters(d[i],thirdstate[i],1.5); //2.751
        //second->SetNpx(5000);
        //fourth->SetParameters(d[i],thirdstate[i],7.5); //2.78
        //fifth->SetParameters(f[i],fourthstate[i],4); //4.8
        if (Det2AngleOrder.at(i) == 0 || Det2AngleOrder.at(i) == 1) {
        fourth->SetParameters(d[i],thirdstate[i],5); //2.78
        fifth->SetParameters(f[i],fourthstate[i],2.5); //4.8
        sixth->SetParameters(g[i],fifthstate[i],7); //6.985
        }
        else {
        fourth->SetParameters(d[i],thirdstate[i],7.5); //2.78
        fifth->SetParameters(f[i],fourthstate[i],5); //4.8
        sixth->SetParameters(g[i],fifthstate[i],12); //6.985
        }
        fourth->SetNpx(5000);
        fifth->SetNpx(5000);
        sixth->SetNpx(5000);
        //sixth->SetParameters(,sixthstate[i],25); //11.64
        //sixth->SetNpx(5000);
        //seventh->SetParameters(,seventhstate[i],23);  //12.16
        //seventh->SetNpx(5000);
        //eight->SetParameters(a[i]/4,48.8,2);
        double pars[15];
        double pars1[15] = {a[i],ground[i],1, c[i],secondstate[i],1, d[i],thirdstate[i],5, f[i],fourthstate[i],2.5, g[i],fifthstate[i],7 };
        double pars2[15] = {a[i],ground[i],1, c[i],secondstate[i],1, d[i],thirdstate[i],7.5, f[i],fourthstate[i],5, g[i],fifthstate[i],12};
        if (Det2AngleOrder.at(i) == 0 || Det2AngleOrder.at(i) == 1) {
          for (int i = 0; i<15; i++) {
          pars[i] = pars1[i];
          }
        }
        else {
          for (int i = 0; i < 15; i++) {
          pars[i] = pars2[i];
          }
        }
        totalstate->SetParameters(pars);
        totalstate->SetNpx(5000);
        sixth->SetLineStyle(kDashed);
        //seventh->SetLineStyle(kDashed);
        totalstate->SetLineStyle(kDashed);
        totalstate->SetLineWidth(1);

        gs->Draw("same");
        //gs->GetYaxis()->SetRangeUser(0,7000);
        first->Draw("same");
        second->Draw("same");
        third->Draw("same");
        fourth->Draw("same");
        fifth->Draw("same");
        sixth->Draw("same");
        //seventh->Draw("same");
        totalstate->Draw("same");
        
      }
    
    }
    /*
    if (type == "totaltDiffg") {
      for (int i = 0 ; i<NDET; i++) {
        canvas->cd(i+1);
        total[i]->Draw();
      }
    }
    if (type == "totaltDiff") {
      for (int i = 0; i<NDET; i++) {
        canvas->cd(i+1);
        total[i]->Draw();
        std::cout << entries[i] << std::endl;
      }
    }
    */
    if (type == "totalPSD") {
      if (calibration == "no") {
        for (int i = 0; i<NDET; i++) {
          canvas->cd(i+1);
          totalPSD[Det2AngleOrder.at(i)]->Draw();
          cuts[Det2AngleOrder.at(i)]->Draw("same");
        }
      }
      if (calibration == "yes") {
        for (int i = 0; i<NDET; i++) {
          canvas->cd(i+1);
          //total[i] = totalPSDc[i]->ProjectionX();
          totalPSDc[Det2AngleOrder.at(i)]->Draw();
          //totalPSDc[i]->Draw();
          cuts[Det2AngleOrder.at(i)]->Draw("same");
        }
      }
    } 
  }
}
