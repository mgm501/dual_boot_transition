#ifdef "PLOTS"
#define "PLOTS"
#include "variables.h"
#include <TH1.h>
#include <TH2.h>

TH1D *tof[ndet];
TH1D *psd[ndet];
TH1D *total1d[ndet];
TH2D *total2d[ndet];
TH1D *energy[ndet];
TH1D *qval[ndet];
TH1D *totenergy[ndet];
TH1D *nenergy[ndet];
TH1D *excitation[ndet];
TH1D *energyplot;
TH1D *totq[ndet];
TH1D *fithist[ndet];

for (int i = 0; i < ndet; i++) {
  psd[i] = new TH2D(Form("PSD - %d", i), Form(" Detector %d", ID2Board.at(i)), 2000, 0, 3500, 512, -0.1, 0.8);
  total1d[i] = new TH1D(Form("total - %d",i), Form(" Detector %d Angle %f" i, angle[i]), timeBin, x, y);
  total2d[i] = new TH2D(Form("PSDindex-%d", i), Form(" Detector %d Angle - %f", ID2Board.at(i), sortedangle[i]), 2000, 0, 3500, 512, -0.1, 0.8);
  if (i == 0 || i == 1) {
    qvalues[i] = new TH1D(Form("energies %d" , i), Form(" Detector %d", ID2Board.at(i)), 28, -20, 20); //125 binning for backwards 27.6 for forwards
    fithist[i] = new TH1D(Form("fithist %d" , i), Form(" Detector %d Angle - %f", i, sortedangle[i]), 28, -20, 20);
    nenergy[i] = new TH1D(Form("n energies %d" , i), Form(" Detector %d Angle %f", i, Angle[i]), 28, -20, 20);
    totnenergy[i] = new TH1D(Form("tot nenergies %d" , i), Form(" Detector %d Angle %f", i, sortedangle[i]), 28, -20, 20);
    totq[i] = new TH1D(Form("energiesq %d" , i), Form(" Detector %d Angle - %f", i, sortedangle[i]), 28, -20, 20); //139 bins for carbon, -20 to 20
    fithist[i]  = new TH1D(Form("fit %d" , i), Form(" Detector %d", ID2Board.at(i)), 28, -20, 20);
  }
  else {
    qvalues[i] = new TH1D(Form("energies %d" , i), Form(" Detector %d", ID2Board.at(i)), 57, -20, 20); //57 or 125
    fithist[i] = new TH1D(Form("fithist %d" , i), Form(" Detector %d Angle - %f", ID2Board.at(i), sortedangle[i]), 57, -20, 20);
    nenergy[i] = new TH1D(Form("n energies %d" , i), Form(" Detector %d Angle %f", ID2Board.at(i), sortedangle[i]), 57, -20, 20);
    totnenergy[i] = new TH1D(Form("tot nenergies %d" , i), Form(" Detector %d Angle %f", ID2Board.at(i), sortedangle[i]), 57, -20, 20);
    totq[i] = new TH1D(Form("energiesq %d" , i), Form(" Detector %d Angle - %f", ID2Board.at(i), sortedangle[i]), 57, -20, 20); //139 bins for carbon, -20 to 20
    fithist[i]  = new TH1D(Form("fit %d" , i), Form(" Detector %d", ID2Board.at(i)), 57, -20, 20);
  }
}
energyplot = new TH1D("energies", "energies", 57, -20, 20);

def plotfill() {
    for (int i = 0; i < ndet; i++) {
      if (tN[i] > 0 && tRF != 0) {

        if (tN[i] < tRF) {
            tof = tRF - tN[i];
        }
        else {
            tof = tN[i] - tRF;
        }

        tof[i]->Fill(tof);
        psd[i]->Fill((a[i]*eL[i])+b[i], (eL[i]-eS[i])*1.0/eL[i]);

        if(cuts[i]->IsInside(((a[i]*eL[i]) + b[i]), ((eL[i]-eS[i])*1.0/eL[i]))) {
          tDiffg[i]->Fill(tdf);
          tofsec = tof * 1.e-9;
          mev = joules2mev * ( (0.5) * mnsi * ((sorteddistance[i] * sorteddistance[i]) / (tofsec * tofsec)) );
          if (target == "carbon") {
            residualmass = m14o;
            q0 = -1.15;
          } else if (target == "li") {
            residualmass = m9b;
            q0 = 9.35;
          }
          q = mev - beamenergy + ( (1/residualmass) * ( (projectilemass * beamenergy) + (mn * energyMeV) - (2 * sqrt(m3*mn*beamenergy*mev) * cos((3.14159 * angle[i])/ 180.)) )); 
          ex = q0 - q;
          if (Q < -20 || Q > 20 || ex < -20 || ex > 20 || i == 16 || i == 17) {
            continue;
          }
          else {
            qvalues[i]->Fill(Q);
            nenergy[i]->Fill(energyMeV);
          }
        }

      }
    }
}

#endif "PLOTS"