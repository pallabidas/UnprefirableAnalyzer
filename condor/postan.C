#define postan_cxx
#include "postan.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

float phiAbs(float phi1, float phi2){
  float dp = abs(phi1-phi2);
  if (dp > M_PI){
    dp -= 2*M_PI;
  }
  return abs(dp);
}

int main(int argc, char *argv[])
{

  if(argc > 1)
    {
      postan t(argv[1], argv[2]);
      t.Loop();
    }
  return 0;
}

using namespace std;

void postan::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if (Cut(ientry) < 0) continue;

      bool preHCAL =  (run_num < 368822) ? true : false;
      //std::cout<<run_num<<"\t"<<preHCAL<<std::endl;

      if(reco_jets->size() > 1){
         TLorentzVector j1;
         j1.SetPtEtaPhiE((*reco_jets)[0].Pt(), (*reco_jets)[0].Eta(), (*reco_jets)[0].Phi(), (*reco_jets)[0].E());
         TLorentzVector j2;
         j2.SetPtEtaPhiE((*reco_jets)[1].Pt(), (*reco_jets)[1].Eta(), (*reco_jets)[1].Phi(), (*reco_jets)[1].E());
         if(((j1+j2).M() > 500.) && (phiAbs(j1.Phi(), j2.Phi()) > 2.7) && (abs(j1.Eta() - j2.Eta()) < 1.3)){
            float threshold_bx0 = 180.;

            if(isUnprefirable == 1){
               for(unsigned int i = 0; i < reco_jets->size(); i++){
                  if(match_l1_bx0->size() > 0){
                     if((*match_l1_bx0)[i].Pt() > threshold_bx0 && preHCAL) { 
                        h_prehcal_jetet_bx0_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bx0)[i].Pt() > threshold_bx0 && !preHCAL) { 
                        h_posthcal_jetet_bx0_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }
                  if(match_l1_bxm1->size() > 0){
                     if((*match_l1_bxm1)[i].Pt() > 60. && preHCAL) { 
                        h_prehcal_jetet_bxm1_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm1_60_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm1_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm1)[i].Pt() > 60. && !preHCAL) { 
                        h_posthcal_jetet_bxm1_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm1_60_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm1_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm1)[i].Pt() > 120. && preHCAL) { 
                        h_prehcal_jetet_bxm1_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm1_120_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm1_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm1)[i].Pt() > 120. && !preHCAL) { 
                        h_posthcal_jetet_bxm1_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm1_120_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm1_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm1)[i].Pt() > 180. && preHCAL) { 
                        h_prehcal_jetet_bxm1_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm1_180_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm1_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm1)[i].Pt() > 180. && !preHCAL) { 
                        h_posthcal_jetet_bxm1_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm1_180_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm1_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }
                  if(match_l1_bx0->size() > 0 && match_l1_bxm1->size() > 0){
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 60.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm1_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm1_60_u->Fill((*reco_jets)[i].Eta());  
                        h_prehcal_jetetaphi_bx0_bxm1_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 60.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm1_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm1_60_u->Fill((*reco_jets)[i].Eta());  
                        h_posthcal_jetetaphi_bx0_bxm1_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 120.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm1_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm1_120_u->Fill((*reco_jets)[i].Eta());  
                        h_prehcal_jetetaphi_bx0_bxm1_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 120.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm1_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm1_120_u->Fill((*reco_jets)[i].Eta());  
                        h_posthcal_jetetaphi_bx0_bxm1_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 180.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm1_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm1_180_u->Fill((*reco_jets)[i].Eta());  
                        h_prehcal_jetetaphi_bx0_bxm1_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 180.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm1_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm1_180_u->Fill((*reco_jets)[i].Eta());  
                        h_posthcal_jetetaphi_bx0_bxm1_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }
                  if(match_l1_bxm2->size() > 0){
                     if((*match_l1_bxm2)[i].Pt() > 60. && preHCAL) { 
                        h_prehcal_jetet_bxm2_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm2_60_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm2_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm2)[i].Pt() > 60. && !preHCAL) { 
                        h_posthcal_jetet_bxm2_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm2_60_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm2_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm2)[i].Pt() > 120. && preHCAL) { 
                        h_prehcal_jetet_bxm2_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm2_120_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm2_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm2)[i].Pt() > 120. && !preHCAL) { 
                        h_posthcal_jetet_bxm2_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm2_120_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm2_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm2)[i].Pt() > 180. && preHCAL) { 
                        h_prehcal_jetet_bxm2_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm2_180_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm2_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm2)[i].Pt() > 180. && !preHCAL) { 
                        h_posthcal_jetet_bxm2_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm2_180_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm2_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                  }
                  if(match_l1_bx0->size() > 0 && match_l1_bxm2->size() > 0){
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 60.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm2_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm2_60_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_bxm2_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 60.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm2_60_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm2_60_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_bxm2_60_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 120.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm2_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm2_120_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_bxm2_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 120.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm2_120_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm2_120_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_bxm2_120_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 180.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm2_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm2_180_u->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_bxm2_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 180.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm2_180_u->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm2_180_u->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_bxm2_180_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }
               }
            } // unprefirable
            if(isFirstBunchInTrain == 1){
               for(unsigned int i = 0; i < reco_jets->size(); i++){
                  if(match_l1_bx0->size() > 0){
                     if((*match_l1_bx0)[i].Pt() > threshold_bx0 && preHCAL) {
                        h_prehcal_jetet_bx0_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bx0_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bx0_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bx0)[i].Pt() > threshold_bx0 && !preHCAL) {
                        h_posthcal_jetet_bx0_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bx0_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bx0_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                  }
                  if(match_l1_bxm1->size() > 0){
                     if((*match_l1_bxm1)[i].Pt() > 60. && preHCAL) {
                        h_prehcal_jetet_bxm1_60_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bxm1_60_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bxm1_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm1)[i].Pt() > 60. && !preHCAL) {
                        h_posthcal_jetet_bxm1_60_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bxm1_60_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bxm1_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm1)[i].Pt() > 120. && preHCAL) {
                        h_prehcal_jetet_bxm1_120_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bxm1_120_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bxm1_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm1)[i].Pt() > 120. && !preHCAL) {
                        h_posthcal_jetet_bxm1_120_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bxm1_120_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bxm1_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm1)[i].Pt() > 180. && preHCAL) {
                        h_prehcal_jetet_bxm1_180_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bxm1_180_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bxm1_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                     if((*match_l1_bxm1)[i].Pt() > 180. && !preHCAL) {
                        h_posthcal_jetet_bxm1_180_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bxm1_180_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bxm1_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                     }
                  }
                  if(match_l1_bx0->size() > 0 && match_l1_bxm1->size() > 0){
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 60.) && preHCAL) {
                        h_prehcal_jetet_bx0_bxm1_60_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bx0_bxm1_60_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bx0_bxm1_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 60.) && !preHCAL) {
                        h_posthcal_jetet_bx0_bxm1_60_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bx0_bxm1_60_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bx0_bxm1_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 120.) && preHCAL) {
                        h_prehcal_jetet_bx0_bxm1_120_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bx0_bxm1_120_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bx0_bxm1_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 120.) && !preHCAL) {
                        h_posthcal_jetet_bx0_bxm1_120_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bx0_bxm1_120_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bx0_bxm1_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 180.) && preHCAL) {
                        h_prehcal_jetet_bx0_bxm1_180_f->Fill((*reco_jets)[i].Pt());
                        h_prehcal_jeteta_bx0_bxm1_180_f->Fill((*reco_jets)[i].Eta());
                        h_prehcal_jetetaphi_bx0_bxm1_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm1)[i].Pt() > 180.) && !preHCAL) {
                        h_posthcal_jetet_bx0_bxm1_180_f->Fill((*reco_jets)[i].Pt());
                        h_posthcal_jeteta_bx0_bxm1_180_f->Fill((*reco_jets)[i].Eta());
                        h_posthcal_jetetaphi_bx0_bxm1_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }
                  if(match_l1_bxm2->size() > 0){
                     if((*match_l1_bxm2)[i].Pt() > 60. && preHCAL) { 
                        h_prehcal_jetet_bxm2_60_f->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm2_60_f->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm2_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm2)[i].Pt() > 60. && !preHCAL) { 
                        h_posthcal_jetet_bxm2_60_f->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm2_60_f->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm2_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm2)[i].Pt() > 120. && preHCAL) { 
                        h_prehcal_jetet_bxm2_120_f->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm2_120_f->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm2_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm2)[i].Pt() > 120. && !preHCAL) { 
                        h_posthcal_jetet_bxm2_120_f->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm2_120_f->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm2_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm2)[i].Pt() > 180. && preHCAL) { 
                        h_prehcal_jetet_bxm2_180_f->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bxm2_180_f->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bxm2_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if((*match_l1_bxm2)[i].Pt() > 180. && !preHCAL) { 
                        h_posthcal_jetet_bxm2_180_f->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bxm2_180_f->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bxm2_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }  
                  if(match_l1_bx0->size() > 0 && match_l1_bxm2->size() > 0){
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 60.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm2_60_f->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm2_60_f->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_bxm2_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 60.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm2_60_f->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm2_60_f->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_bxm2_60_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 120.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm2_120_f->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm2_120_f->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_bxm2_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 120.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm2_120_f->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm2_120_f->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_bxm2_120_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 180.) && preHCAL) { 
                        h_prehcal_jetet_bx0_bxm2_180_f->Fill((*reco_jets)[i].Pt()); 
                        h_prehcal_jeteta_bx0_bxm2_180_f->Fill((*reco_jets)[i].Eta()); 
                        h_prehcal_jetetaphi_bx0_bxm2_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                     if(((*match_l1_bx0)[i].Pt() > threshold_bx0 || (*match_l1_bxm2)[i].Pt() > 180.) && !preHCAL) { 
                        h_posthcal_jetet_bx0_bxm2_180_f->Fill((*reco_jets)[i].Pt()); 
                        h_posthcal_jeteta_bx0_bxm2_180_f->Fill((*reco_jets)[i].Eta()); 
                        h_posthcal_jetetaphi_bx0_bxm2_180_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                     }
                  }
               }
            } // firstbunchintrain
         } // dijet condition
      } //njet condition
   }
}

void postan::BookHistos(const char* file2){
   fileName = new TFile(file2, "RECREATE");
   fileName->cd();

   // un prefirable 

   h_prehcal_jetet_bx0_u = new TH1F("h_prehcal_jetet_bx0_u", "h_prehcal_jetet_bx0_u", 40, 0, 1500);

   h_prehcal_jetet_bxm1_60_u = new TH1F("h_prehcal_jetet_bxm1_60_u","h_prehcal_jetet_bxm1_60_u", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm1_60_u = new TH1F("h_prehcal_jetet_bx0_bxm1_60_u", "h_prehcal_jetet_bx0_bxm1_60_u", 40, 0, 1500);
   h_prehcal_jetet_bxm2_60_u = new TH1F("h_prehcal_jetet_bxm2_60_u", "h_prehcal_jetet_bxm2_60_u", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm2_60_u = new TH1F("h_prehcal_jetet_bx0_bxm2_60_u", "h_prehcal_jetet_bx0_bxm2_60_u", 40, 0, 1500);

   h_prehcal_jetet_bxm1_120_u = new TH1F("h_prehcal_jetet_bxm1_120_u","h_prehcal_jetet_bxm1_120_u", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm1_120_u = new TH1F("h_prehcal_jetet_bx0_bxm1_120_u", "h_prehcal_jetet_bx0_bxm1_120_u", 40, 0, 1500);
   h_prehcal_jetet_bxm2_120_u = new TH1F("h_prehcal_jetet_bxm2_120_u", "h_prehcal_jetet_bxm2_120_u", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm2_120_u = new TH1F("h_prehcal_jetet_bx0_bxm2_120_u", "h_prehcal_jetet_bx0_bxm2_120_u", 40, 0, 1500);

   h_prehcal_jetet_bxm1_180_u = new TH1F("h_prehcal_jetet_bxm1_180_u","h_prehcal_jetet_bxm1_180_u", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm1_180_u = new TH1F("h_prehcal_jetet_bx0_bxm1_180_u", "h_prehcal_jetet_bx0_bxm1_180_u", 40, 0, 1500);
   h_prehcal_jetet_bxm2_180_u = new TH1F("h_prehcal_jetet_bxm2_180_u", "h_prehcal_jetet_bxm2_180_u", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm2_180_u = new TH1F("h_prehcal_jetet_bx0_bxm2_180_u", "h_prehcal_jetet_bx0_bxm2_180_u", 40, 0, 1500);

   h_prehcal_jeteta_bx0_u = new TH1F("h_prehcal_jeteta_bx0_u", "h_prehcal_jeteta_bx0_u", 40, -5, 5);

   h_prehcal_jeteta_bxm1_60_u = new TH1F("h_prehcal_jeteta_bxm1_60_u", "h_prehcal_jeteta_bxm1_60_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_60_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_60_u", "h_prehcal_jeteta_bx0_bxm1_60_u", 40, -5, 5);
   h_prehcal_jeteta_bxm2_60_u = new TH1F("h_prehcal_jeteta_bxm2_60_u", "h_prehcal_jeteta_bxm2_60_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm2_60_u = new TH1F("h_prehcal_jeteta_bx0_bxm2_60_u", "h_prehcal_jeteta_bx0_bxm2_60_u", 40, -5, 5);

   h_prehcal_jeteta_bxm1_120_u = new TH1F("h_prehcal_jeteta_bxm1_120_u", "h_prehcal_jeteta_bxm1_120_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_120_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_120_u", "h_prehcal_jeteta_bx0_bxm1_120_u", 40, -5, 5);
   h_prehcal_jeteta_bxm2_120_u = new TH1F("h_prehcal_jeteta_bxm2_120_u", "h_prehcal_jeteta_bxm2_120_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm2_120_u = new TH1F("h_prehcal_jeteta_bx0_bxm2_120_u", "h_prehcal_jeteta_bx0_bxm2_120_u", 40, -5, 5);

   h_prehcal_jeteta_bxm1_180_u = new TH1F("h_prehcal_jeteta_bxm1_180_u", "h_prehcal_jeteta_bxm1_180_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_180_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_180_u", "h_prehcal_jeteta_bx0_bxm1_180_u", 40, -5, 5);
   h_prehcal_jeteta_bxm2_180_u = new TH1F("h_prehcal_jeteta_bxm2_180_u", "h_prehcal_jeteta_bxm2_180_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm2_180_u = new TH1F("h_prehcal_jeteta_bx0_bxm2_180_u", "h_prehcal_jeteta_bx0_bxm2_180_u", 40, -5, 5);

   h_prehcal_jetetaphi_bx0_u = new TH2F("h_prehcal_jetetaphi_bx0_u", "h_prehcal_jetetaphi_bx0_u", 40, -5, 5, 40, -M_PI, M_PI);

   h_prehcal_jetetaphi_bxm1_60_u = new TH2F("h_prehcal_jetetaphi_bxm1_60_u", "h_prehcal_jetetaphi_bxm1_60_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_60_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_60_u", "h_prehcal_jetetaphi_bx0_bxm1_60_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bxm2_60_u = new TH2F("h_prehcal_jetetaphi_bxm2_60_u", "h_prehcal_jetetaphi_bxm2_60_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm2_60_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm2_60_u", "h_prehcal_jetetaphi_bx0_bxm2_60_u", 40, -5, 5, 40, -M_PI, M_PI); 

   h_prehcal_jetetaphi_bxm1_120_u = new TH2F("h_prehcal_jetetaphi_bxm1_120_u", "h_prehcal_jetetaphi_bxm1_120_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_120_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_120_u", "h_prehcal_jetetaphi_bx0_bxm1_120_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bxm2_120_u = new TH2F("h_prehcal_jetetaphi_bxm2_120_u", "h_prehcal_jetetaphi_bxm2_120_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm2_120_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm2_120_u", "h_prehcal_jetetaphi_bx0_bxm2_120_u", 40, -5, 5, 40, -M_PI, M_PI); 

   h_prehcal_jetetaphi_bxm1_180_u = new TH2F("h_prehcal_jetetaphi_bxm1_180_u", "h_prehcal_jetetaphi_bxm1_180_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_180_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_180_u", "h_prehcal_jetetaphi_bx0_bxm1_180_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bxm2_180_u = new TH2F("h_prehcal_jetetaphi_bxm2_180_u", "h_prehcal_jetetaphi_bxm2_180_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm2_180_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm2_180_u", "h_prehcal_jetetaphi_bx0_bxm2_180_u", 40, -5, 5, 40, -M_PI, M_PI); 

   h_posthcal_jetet_bx0_u = new TH1F("h_posthcal_jetet_bx0_u", "h_posthcal_jetet_bx0_u", 40, 0, 1500);

   h_posthcal_jetet_bxm1_60_u = new TH1F("h_posthcal_jetet_bxm1_60_u","h_posthcal_jetet_bxm1_60_u", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm1_60_u = new TH1F("h_posthcal_jetet_bx0_bxm1_60_u", "h_posthcal_jetet_bx0_bxm1_60_u", 40, 0, 1500);
   h_posthcal_jetet_bxm2_60_u = new TH1F("h_posthcal_jetet_bxm2_60_u", "h_posthcal_jetet_bxm2_60_u", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm2_60_u = new TH1F("h_posthcal_jetet_bx0_bxm2_60_u", "h_posthcal_jetet_bx0_bxm2_60_u", 40, 0, 1500);

   h_posthcal_jetet_bxm1_120_u = new TH1F("h_posthcal_jetet_bxm1_120_u","h_posthcal_jetet_bxm1_120_u", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm1_120_u = new TH1F("h_posthcal_jetet_bx0_bxm1_120_u", "h_posthcal_jetet_bx0_bxm1_120_u", 40, 0, 1500);
   h_posthcal_jetet_bxm2_120_u = new TH1F("h_posthcal_jetet_bxm2_120_u", "h_posthcal_jetet_bxm2_120_u", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm2_120_u = new TH1F("h_posthcal_jetet_bx0_bxm2_120_u", "h_posthcal_jetet_bx0_bxm2_120_u", 40, 0, 1500);

   h_posthcal_jetet_bxm1_180_u = new TH1F("h_posthcal_jetet_bxm1_180_u","h_posthcal_jetet_bxm1_180_u", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm1_180_u = new TH1F("h_posthcal_jetet_bx0_bxm1_180_u", "h_posthcal_jetet_bx0_bxm1_180_u", 40, 0, 1500);
   h_posthcal_jetet_bxm2_180_u = new TH1F("h_posthcal_jetet_bxm2_180_u", "h_posthcal_jetet_bxm2_180_u", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm2_180_u = new TH1F("h_posthcal_jetet_bx0_bxm2_180_u", "h_posthcal_jetet_bx0_bxm2_180_u", 40, 0, 1500);

   h_posthcal_jeteta_bx0_u = new TH1F("h_posthcal_jeteta_bx0_u", "h_posthcal_jeteta_bx0_u", 40, -5, 5);

   h_posthcal_jeteta_bxm1_60_u = new TH1F("h_posthcal_jeteta_bxm1_60_u", "h_posthcal_jeteta_bxm1_60_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_60_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_60_u", "h_posthcal_jeteta_bx0_bxm1_60_u", 40, -5, 5);
   h_posthcal_jeteta_bxm2_60_u = new TH1F("h_posthcal_jeteta_bxm2_60_u", "h_posthcal_jeteta_bxm2_60_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm2_60_u = new TH1F("h_posthcal_jeteta_bx0_bxm2_60_u", "h_posthcal_jeteta_bx0_bxm2_60_u", 40, -5, 5);

   h_posthcal_jeteta_bxm1_120_u = new TH1F("h_posthcal_jeteta_bxm1_120_u", "h_posthcal_jeteta_bxm1_120_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_120_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_120_u", "h_posthcal_jeteta_bx0_bxm1_120_u", 40, -5, 5);
   h_posthcal_jeteta_bxm2_120_u = new TH1F("h_posthcal_jeteta_bxm2_120_u", "h_posthcal_jeteta_bxm2_120_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm2_120_u = new TH1F("h_posthcal_jeteta_bx0_bxm2_120_u", "h_posthcal_jeteta_bx0_bxm2_120_u", 40, -5, 5);

   h_posthcal_jeteta_bxm1_180_u = new TH1F("h_posthcal_jeteta_bxm1_180_u", "h_posthcal_jeteta_bxm1_180_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_180_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_180_u", "h_posthcal_jeteta_bx0_bxm1_180_u", 40, -5, 5);
   h_posthcal_jeteta_bxm2_180_u = new TH1F("h_posthcal_jeteta_bxm2_180_u", "h_posthcal_jeteta_bxm2_180_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm2_180_u = new TH1F("h_posthcal_jeteta_bx0_bxm2_180_u", "h_posthcal_jeteta_bx0_bxm2_180_u", 40, -5, 5);

   h_posthcal_jetetaphi_bx0_u = new TH2F("h_posthcal_jetetaphi_bx0_u", "h_posthcal_jetetaphi_bx0_u", 40, -5, 5, 40, -M_PI, M_PI);

   h_posthcal_jetetaphi_bxm1_60_u = new TH2F("h_posthcal_jetetaphi_bxm1_60_u", "h_posthcal_jetetaphi_bxm1_60_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_60_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_60_u", "h_posthcal_jetetaphi_bx0_bxm1_60_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bxm2_60_u = new TH2F("h_posthcal_jetetaphi_bxm2_60_u", "h_posthcal_jetetaphi_bxm2_60_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm2_60_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm2_60_u", "h_posthcal_jetetaphi_bx0_bxm2_60_u", 40, -5, 5, 40, -M_PI, M_PI); 

   h_posthcal_jetetaphi_bxm1_120_u = new TH2F("h_posthcal_jetetaphi_bxm1_120_u", "h_posthcal_jetetaphi_bxm1_120_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_120_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_120_u", "h_posthcal_jetetaphi_bx0_bxm1_120_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bxm2_120_u = new TH2F("h_posthcal_jetetaphi_bxm2_120_u", "h_posthcal_jetetaphi_bxm2_120_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm2_120_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm2_120_u", "h_posthcal_jetetaphi_bx0_bxm2_120_u", 40, -5, 5, 40, -M_PI, M_PI); 

   h_posthcal_jetetaphi_bxm1_180_u = new TH2F("h_posthcal_jetetaphi_bxm1_180_u", "h_posthcal_jetetaphi_bxm1_180_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_180_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_180_u", "h_posthcal_jetetaphi_bx0_bxm1_180_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bxm2_180_u = new TH2F("h_posthcal_jetetaphi_bxm2_180_u", "h_posthcal_jetetaphi_bxm2_180_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm2_180_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm2_180_u", "h_posthcal_jetetaphi_bx0_bxm2_180_u", 40, -5, 5, 40, -M_PI, M_PI); 

   // first bunch in train
   h_prehcal_jetet_bx0_f = new TH1F("h_prehcal_jetet_bx0_f", "h_prehcal_jetet_bx0_f", 40, 0, 1500);

   h_prehcal_jetet_bxm1_60_f = new TH1F("h_prehcal_jetet_bxm1_60_f", "h_prehcal_jetet_bxm1_60_f", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm1_60_f = new TH1F("h_prehcal_jetet_bx0_bxm1_60_f", "h_prehcal_jetet_bx0_bxm1_60_f", 40, 0, 1500);
   h_prehcal_jetet_bxm2_60_f = new TH1F("h_prehcal_jetet_bxm2_60_f", "h_prehcal_jetet_bxm2_60_f", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm2_60_f = new TH1F("h_prehcal_jetet_bx0_bxm2_60_f", "h_prehcal_jetet_bx0_bxm2_60_f", 40, 0, 1500);

   h_prehcal_jetet_bxm1_120_f = new TH1F("h_prehcal_jetet_bxm1_120_f", "h_prehcal_jetet_bxm1_120_f", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm1_120_f = new TH1F("h_prehcal_jetet_bx0_bxm1_120_f", "h_prehcal_jetet_bx0_bxm1_120_f", 40, 0, 1500);
   h_prehcal_jetet_bxm2_120_f = new TH1F("h_prehcal_jetet_bxm2_120_f", "h_prehcal_jetet_bxm2_120_f", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm2_120_f = new TH1F("h_prehcal_jetet_bx0_bxm2_120_f", "h_prehcal_jetet_bx0_bxm2_120_f", 40, 0, 1500);

   h_prehcal_jetet_bxm1_180_f = new TH1F("h_prehcal_jetet_bxm1_180_f", "h_prehcal_jetet_bxm1_180_f", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm1_180_f = new TH1F("h_prehcal_jetet_bx0_bxm1_180_f", "h_prehcal_jetet_bx0_bxm1_180_f", 40, 0, 1500);
   h_prehcal_jetet_bxm2_180_f = new TH1F("h_prehcal_jetet_bxm2_180_f", "h_prehcal_jetet_bxm2_180_f", 40, 0, 1500);
   h_prehcal_jetet_bx0_bxm2_180_f = new TH1F("h_prehcal_jetet_bx0_bxm2_180_f", "h_prehcal_jetet_bx0_bxm2_180_f", 40, 0, 1500);
   
   h_prehcal_jeteta_bx0_f = new TH1F("h_prehcal_jeteta_bx0_f", "h_prehcal_jeteta_bx0_f", 40, -5, 5);

   h_prehcal_jeteta_bxm1_60_f = new TH1F("h_prehcal_jeteta_bxm1_60_f", "h_prehcal_jeteta_bxm1_60_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_60_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_60_f", "h_prehcal_jeteta_bx0_bxm1_60_f", 40, -5, 5);
   h_prehcal_jeteta_bxm2_60_f = new TH1F("h_prehcal_jeteta_bxm2_60_f", "h_prehcal_jeteta_bxm2_60_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm2_60_f = new TH1F("h_prehcal_jeteta_bx0_bxm2_60_f", "h_prehcal_jeteta_bx0_bxm2_60_f", 40, -5, 5);

   h_prehcal_jeteta_bxm1_120_f = new TH1F("h_prehcal_jeteta_bxm1_120_f", "h_prehcal_jeteta_bxm1_120_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_120_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_120_f", "h_prehcal_jeteta_bx0_bxm1_120_f", 40, -5, 5);
   h_prehcal_jeteta_bxm2_120_f = new TH1F("h_prehcal_jeteta_bxm2_120_f", "h_prehcal_jeteta_bxm2_120_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm2_120_f = new TH1F("h_prehcal_jeteta_bx0_bxm2_120_f", "h_prehcal_jeteta_bx0_bxm2_120_f", 40, -5, 5);

   h_prehcal_jeteta_bxm1_180_f = new TH1F("h_prehcal_jeteta_bxm1_180_f", "h_prehcal_jeteta_bxm1_180_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_180_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_180_f", "h_prehcal_jeteta_bx0_bxm1_180_f", 40, -5, 5);
   h_prehcal_jeteta_bxm2_180_f = new TH1F("h_prehcal_jeteta_bxm2_180_f", "h_prehcal_jeteta_bxm2_180_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm2_180_f = new TH1F("h_prehcal_jeteta_bx0_bxm2_180_f", "h_prehcal_jeteta_bx0_bxm2_180_f", 40, -5, 5);

   h_prehcal_jetetaphi_bx0_f= new TH2F("h_prehcal_jetetaphi_bx0_f", "h_prehcal_jetetaphi_bx0_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_prehcal_jetetaphi_bxm1_60_f = new TH2F("h_prehcal_jetetaphi_bxm1_60_f", "h_prehcal_jetetaphi_bxm1_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_60_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_60_f", "h_prehcal_jetetaphi_bx0_bxm1_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bxm2_60_f = new TH2F("h_prehcal_jetetaphi_bxm2_60_f", "h_prehcal_jetetaphi_bxm2_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm2_60_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm2_60_f", "h_prehcal_jetetaphi_bx0_bxm2_60_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_prehcal_jetetaphi_bxm1_120_f = new TH2F("h_prehcal_jetetaphi_bxm1_120_f", "h_prehcal_jetetaphi_bxm1_120_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_120_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_120_f", "h_prehcal_jetetaphi_bx0_bxm1_120_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bxm2_120_f = new TH2F("h_prehcal_jetetaphi_bxm2_120_f", "h_prehcal_jetetaphi_bxm2_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm2_120_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm2_120_f", "h_prehcal_jetetaphi_bx0_bxm2_120_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_prehcal_jetetaphi_bxm1_180_f = new TH2F("h_prehcal_jetetaphi_bxm1_180_f", "h_prehcal_jetetaphi_bxm1_180_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_180_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_180_f", "h_prehcal_jetetaphi_bx0_bxm1_180_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bxm2_180_f = new TH2F("h_prehcal_jetetaphi_bxm2_180_f", "h_prehcal_jetetaphi_bxm2_180_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm2_180_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm2_180_f", "h_prehcal_jetetaphi_bx0_bxm2_180_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_posthcal_jetet_bx0_f = new TH1F("h_posthcal_jetet_bx0_f", "h_posthcal_jetet_bx0_f", 40, 0, 1500);

   h_posthcal_jetet_bxm1_60_f = new TH1F("h_posthcal_jetet_bxm1_60_f", "h_posthcal_jetet_bxm1_60_f", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm1_60_f = new TH1F("h_posthcal_jetet_bx0_bxm1_60_f", "h_posthcal_jetet_bx0_bxm1_60_f", 40, 0, 1500);
   h_posthcal_jetet_bxm2_60_f = new TH1F("h_posthcal_jetet_bxm2_60_f", "h_posthcal_jetet_bxm2_60_f", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm2_60_f = new TH1F("h_posthcal_jetet_bx0_bxm2_60_f", "h_posthcal_jetet_bx0_bxm2_60_f", 40, 0, 1500);

   h_posthcal_jetet_bxm1_120_f = new TH1F("h_posthcal_jetet_bxm1_120_f", "h_posthcal_jetet_bxm1_120_f", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm1_120_f = new TH1F("h_posthcal_jetet_bx0_bxm1_120_f", "h_posthcal_jetet_bx0_bxm1_120_f", 40, 0, 1500);
   h_posthcal_jetet_bxm2_120_f = new TH1F("h_posthcal_jetet_bxm2_120_f", "h_posthcal_jetet_bxm2_120_f", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm2_120_f = new TH1F("h_posthcal_jetet_bx0_bxm2_120_f", "h_posthcal_jetet_bx0_bxm2_120_f", 40, 0, 1500);

   h_posthcal_jetet_bxm1_180_f = new TH1F("h_posthcal_jetet_bxm1_180_f", "h_posthcal_jetet_bxm1_180_f", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm1_180_f = new TH1F("h_posthcal_jetet_bx0_bxm1_180_f", "h_posthcal_jetet_bx0_bxm1_180_f", 40, 0, 1500);
   h_posthcal_jetet_bxm2_180_f = new TH1F("h_posthcal_jetet_bxm2_180_f", "h_posthcal_jetet_bxm2_180_f", 40, 0, 1500);
   h_posthcal_jetet_bx0_bxm2_180_f = new TH1F("h_posthcal_jetet_bx0_bxm2_180_f", "h_posthcal_jetet_bx0_bxm2_180_f", 40, 0, 1500);
   
   h_posthcal_jeteta_bx0_f = new TH1F("h_posthcal_jeteta_bx0_f", "h_posthcal_jeteta_bx0_f", 40, -5, 5);

   h_posthcal_jeteta_bxm1_60_f = new TH1F("h_posthcal_jeteta_bxm1_60_f", "h_posthcal_jeteta_bxm1_60_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_60_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_60_f", "h_posthcal_jeteta_bx0_bxm1_60_f", 40, -5, 5);
   h_posthcal_jeteta_bxm2_60_f = new TH1F("h_posthcal_jeteta_bxm2_60_f", "h_posthcal_jeteta_bxm2_60_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm2_60_f = new TH1F("h_posthcal_jeteta_bx0_bxm2_60_f", "h_posthcal_jeteta_bx0_bxm2_60_f", 40, -5, 5);

   h_posthcal_jeteta_bxm1_120_f = new TH1F("h_posthcal_jeteta_bxm1_120_f", "h_posthcal_jeteta_bxm1_120_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_120_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_120_f", "h_posthcal_jeteta_bx0_bxm1_120_f", 40, -5, 5);
   h_posthcal_jeteta_bxm2_120_f = new TH1F("h_posthcal_jeteta_bxm2_120_f", "h_posthcal_jeteta_bxm2_120_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm2_120_f = new TH1F("h_posthcal_jeteta_bx0_bxm2_120_f", "h_posthcal_jeteta_bx0_bxm2_120_f", 40, -5, 5);

   h_posthcal_jeteta_bxm1_180_f = new TH1F("h_posthcal_jeteta_bxm1_180_f", "h_posthcal_jeteta_bxm1_180_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_180_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_180_f", "h_posthcal_jeteta_bx0_bxm1_180_f", 40, -5, 5);
   h_posthcal_jeteta_bxm2_180_f = new TH1F("h_posthcal_jeteta_bxm2_180_f", "h_posthcal_jeteta_bxm2_180_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm2_180_f = new TH1F("h_posthcal_jeteta_bx0_bxm2_180_f", "h_posthcal_jeteta_bx0_bxm2_180_f", 40, -5, 5);

   h_posthcal_jetetaphi_bx0_f= new TH2F("h_posthcal_jetetaphi_bx0_f", "h_posthcal_jetetaphi_bx0_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_posthcal_jetetaphi_bxm1_60_f = new TH2F("h_posthcal_jetetaphi_bxm1_60_f", "h_posthcal_jetetaphi_bxm1_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_60_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_60_f", "h_posthcal_jetetaphi_bx0_bxm1_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bxm2_60_f = new TH2F("h_posthcal_jetetaphi_bxm2_60_f", "h_posthcal_jetetaphi_bxm2_60_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm2_60_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm2_60_f", "h_posthcal_jetetaphi_bx0_bxm2_60_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_posthcal_jetetaphi_bxm1_120_f = new TH2F("h_posthcal_jetetaphi_bxm1_120_f", "h_posthcal_jetetaphi_bxm1_120_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_120_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_120_f", "h_posthcal_jetetaphi_bx0_bxm1_120_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bxm2_120_f = new TH2F("h_posthcal_jetetaphi_bxm2_120_f", "h_posthcal_jetetaphi_bxm2_120_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm2_120_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm2_120_f", "h_posthcal_jetetaphi_bx0_bxm2_120_f", 40, -5, 5, 40, -M_PI, M_PI);

   h_posthcal_jetetaphi_bxm1_180_f = new TH2F("h_posthcal_jetetaphi_bxm1_180_f", "h_posthcal_jetetaphi_bxm1_180_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_180_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_180_f", "h_posthcal_jetetaphi_bx0_bxm1_180_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bxm2_180_f = new TH2F("h_posthcal_jetetaphi_bxm2_180_f", "h_posthcal_jetetaphi_bxm2_180_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm2_180_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm2_180_f", "h_posthcal_jetetaphi_bx0_bxm2_180_f", 40, -5, 5, 40, -M_PI, M_PI);

}
