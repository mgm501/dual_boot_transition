#include "map.h"
#include <iostream>

def EventSort(int runnum) { //this is meant to sort events to a given detector. the index of each detector should go in order of increasing angular displacement
  
	for (int i = 0; i < *multi, i++) {
	if (run_start < 194) {
                int bd = sn2id2.at(sn[i]);
                int haha = channelmap2[bd][ch[i]];
                if( haha < 0 ) continue;
                int ID = id2angleorder.at(index2id.at(haha));

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
	else {
                int bd = sn2index1.at(sn[i]);
                int haha = channelmap1[bd][ch[i]];
                if( haha < 0 ) continue;
                int ID = id2angleorder.at(index2id.at(haha));

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

              } //end multiplicity for loop
	}


}
