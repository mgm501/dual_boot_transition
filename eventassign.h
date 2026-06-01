#ifdef "EVENTASSIGN"
#define "EVENTASSIGN"
#include "map.h"
#include "variables.h"
#include <iostream>

#include std::string;
#include std::getline;
#include std::ifstream;
#include std::istringstream;
#include std::cout;
#include std::endl;

def EventAssign(int runnum) { //this is meant to sort events to a given detector. the index of each detector should go in order of increasing angular displacement
  
	for (int i = 0; i < *multi, i++) {

	  if (runnum < 194) {

      int bd = sn2id2.at(sn[i]);
      int haha = channelmap2[bd][ch[i]];
      if( haha < 0 ) continue;
      int ID = id2angleorder.at(index2id.at(haha));
      if(ID == 200) {
        if (e_f[i] > 20000) {
          continue;
        }
        else {
          tRF = e_t[i] * 1000 + e_f[i];
        }
      }
      if( ID < 0 || ID > NDET ) continue;
      el[ID] = e[i];
      es[ID] = e2[i];
      if (e_f[i] > 20000) {
        continue;
      }
      else {
        tN[ID] = e_t[i] * 1000 + e_f[i];
      }

    }

	  else {

      int bd = sn2index1.at(sn[i]);
      int haha = channelmap1[bd][ch[i]];
      if( haha < 0 ) continue;
      int ID = id2angleorder.at(index2id.at(haha));
      if(ID == 200) {
        if (e_f[i] > 20000) {
          continue;
        }
        else {
          tRF = e_t[i] * 1000 + e_f[i];
        }
      }
      if( ID < 0 || ID > NDET ) continue;
      el[ID] = e[i];
      es[ID] = e2[i];
      if (e_f[i] > 20000) {
        continue;
      }
      else {
        tN[ID] = e_t[i] * 1000 + e_f[i];
      }

    } //end if statement

	} //end multiplicity for loop

}//end function

double readcalibration(&string filename) {
    ifstream calibrationfile;
    unsigned short runindex;
    double a[ndet];
    double b[ndet];
    calibrationfile.open(filename);
    if (!calibrationfile.is_open()) {
        cout << "Could not open calibration file\n";
        return;
    }
    string line;
    int count = 0;
    while (getline(calibrationfile, line)) {
        istringstream row(line);
        row(line) >> det >> a[ndet] >> b[ndet];
    }
    infile.close();
    for (int i = 0; i<ndet; i++) {
        cout << a[i] << "  " << b[i] << "\n";
    }
    return a, b;
}

double readshift(&string filename, unsigned short runnum) {
    ifstream shiftfile;
    unsigned short runindex;
    string row;
    unsigned short det;
    double shift;
    double shifts[ndet] = {0};
    shiftfile.open(filename);
    if (!shiftfile.is_open()) {
        cout << "Something went wrong :(\n";
    }
    istringstream row;
    while (getline(shiftfile, line)) {
        row(line) >> runindex >> det >> shift;
    }
    if (runindex == runnum) {
        shifts[det] = shift;
    }
    return shifts;
}

#endif "EVENTASSIGN"