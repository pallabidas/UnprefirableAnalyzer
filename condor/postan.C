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

float deltaR(const TLorentzVector& l1jet, const TLorentzVector& recojet) {
  float p1 = l1jet.Phi();
  float p2 = recojet.Phi();
  float e1 = l1jet.Eta();
  float e2 = recojet.Eta();
  float dp = std::abs(p1 - p2);
  if (dp > float(M_PI)) dp -= float(2 * M_PI);
  return sqrt((e1 - e2) * (e1 - e2) + dp * dp);
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
      // L1_SingleJet180: 309, L1_ETMHF90: 420, L1_SingleTau120er2p1: 263, L1_SingleIsoTau32er2p1: 261 (prescale 0), L1_DoubleIsoTau34er2p1: 270

      bool preHCAL =  (run_num < 368822) ? true : false;
      //std::cout<<run_num<<"\t"<<preHCAL<<std::endl;
      //if(L1FinalOR_bxm1 || (*trigger_bits)[309] || (*trigger_bits)[420] || (*trigger_bits)[263] || (*trigger_bits)[261] || (*trigger_bits)[270]) std::cout<<L1FinalOR_bxm1<<"\t"<<(*trigger_bits)[309]<<"\t"<<(*trigger_bits)[420]<<"\t"<<(*trigger_bits)[263]<<"\t"<<(*trigger_bits)[261]<<"\t"<<(*trigger_bits)[270]<<std::endl;

      //bool L1_bxm1 = ((*trigger_bits)[309] || (*trigger_bits)[420] || (*trigger_bits)[263] || (*trigger_bits)[261] || (*trigger_bits)[270]);
      //if(L1_bxm1) std::cout<<"L1_bxm1"<<"\t"<<L1_bxm1<<"\t"<<isUnprefirable<<"\t"<<isFirstBunchInTrain<<"\t"<<L1FinalOR_bxm1<<std::endl;
      bool SingleJet = false;
      float threshold_bx0 = 180.;
      for(unsigned int i = 0; i < match_l1_bx0->size(); i++){
         if((*match_l1_bx0)[i].Pt() > threshold_bx0) SingleJet = true;
      }

      //if (!SingleJet && ((*trigger_bits)[309] || (*trigger_bits)[420] || (*trigger_bits)[263] || (*trigger_bits)[261] || (*trigger_bits)[270])) std::cout<<SingleJet<<"\t"<<L1FinalOR_bxm1<<"\t"<<(*trigger_bits)[309]<<"\t"<<(*trigger_bits)[420]<<"\t"<<(*trigger_bits)[263]<<"\t"<<(*trigger_bits)[261]<<"\t"<<(*trigger_bits)[270]<<std::endl;
      
      if(reco_jets->size() > 1){
         TLorentzVector j1;
         j1.SetPtEtaPhiE((*reco_jets)[0].Pt(), (*reco_jets)[0].Eta(), (*reco_jets)[0].Phi(), (*reco_jets)[0].E());
         TLorentzVector j2;
         j2.SetPtEtaPhiE((*reco_jets)[1].Pt(), (*reco_jets)[1].Eta(), (*reco_jets)[1].Phi(), (*reco_jets)[1].E());
         if(((j1+j2).M() > 500.) && (phiAbs(j1.Phi(), j2.Phi()) > 2.7)){

            vector<bool> bxm1_jet, bxm1_tau, bxm1_isotau, bxm1_etm;
            bxm1_jet.clear(); bxm1_tau.clear(); bxm1_isotau.clear(); bxm1_etm.clear();
            bool bxm1_jet_temp, bxm1_tau_temp, bxm1_isotau_temp, bxm1_etm_temp;
            for(unsigned int i = 0; i < reco_jets->size(); i++){
               bxm1_jet_temp = false; bxm1_tau_temp = false; bxm1_isotau_temp = false; bxm1_etm_temp = false;
               for(unsigned int j = 0; j < bxm1_jets->size(); j++){
                  if(deltaR((*reco_jets)[i], (*bxm1_jets)[j]) < 0.4) bxm1_jet_temp = true;
               }
               for(unsigned int j = 0; j < bxm1_taus->size(); j++){
                  if(deltaR((*reco_jets)[i], (*bxm1_taus)[j]) < 0.4) bxm1_tau_temp = true;
               }
               for(unsigned int j = 0; j < bxm1_isotaus->size(); j++){
                  if(deltaR((*reco_jets)[i], (*bxm1_isotaus)[j]) < 0.4) bxm1_isotau_temp = true;
               }
               if(phiAbs((*reco_jets)[i].Phi(), bxm1_etmhf_phi) < 0.4) bxm1_etm_temp = true;
               bxm1_jet.push_back(bxm1_jet_temp);
               bxm1_tau.push_back(bxm1_tau_temp);
               bxm1_isotau.push_back(bxm1_isotau_temp);
               bxm1_etm.push_back(bxm1_etm_temp);
            }

            if(isUnprefirable == 1){
               if(preHCAL) {
                  h_prehcal_dijet_bx0_u->Fill((j1+j2).M());
               }
               if(!preHCAL) {
                  h_posthcal_dijet_bx0_u->Fill((j1+j2).M());
               }
               if(L1FinalOR_bxm1 && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_u->Fill((j1+j2).M());
               }
               if(L1FinalOR_bxm1 && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_u->Fill((j1+j2).M());
               }
               if((*trigger_bits)[420] && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case1_u->Fill((j1+j2).M());
               }
               if((*trigger_bits)[420] && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case1_u->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && (*trigger_bits)[309] && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case2_u->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && (*trigger_bits)[309] && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case2_u->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case3_u->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case3_u->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && (bxm1_isotau[0] || bxm1_isotau[1]) && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case4_u->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && (bxm1_isotau[0] || bxm1_isotau[1]) && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case4_u->Fill((j1+j2).M());
               }
               
               for(unsigned int i = 0; i < reco_jets->size(); i++){
                  //bool bxm1_jet = false;
                  //for(unsigned int j = 0; j < bxm1_jets->size(); j++){
                  //   if(deltaR((*reco_jets)[i], (*bxm1_jets)[j]) < 0.4) bxm1_jet = true;
                  //}
                  //bool bxm1_tau = false;
                  //for(unsigned int j = 0; j < bxm1_taus->size(); j++){
                  //   if(deltaR((*reco_jets)[i], (*bxm1_taus)[j]) < 0.4) bxm1_tau = true;
                  //}
                  //bool bxm1_etm = false;
                  //if(phiAbs((*reco_jets)[i].Phi(), bxm1_etmhf_phi) < 0.4) bxm1_etm = true;
                  if(preHCAL) { 
                     h_prehcal_jetet_bx0_u->Fill((*reco_jets)[i].Pt()); 
                     h_prehcal_jeteta_bx0_u->Fill((*reco_jets)[i].Eta()); 
                     h_prehcal_jetetaphi_bx0_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(!preHCAL) {
                     h_posthcal_jetet_bx0_u->Fill((*reco_jets)[i].Pt()); 
                     h_posthcal_jeteta_bx0_u->Fill((*reco_jets)[i].Eta()); 
                     h_posthcal_jetetaphi_bx0_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(L1FinalOR_bxm1 && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_u->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_u->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(L1FinalOR_bxm1 && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_u->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_u->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if((*trigger_bits)[420] && bxm1_etm[i] && preHCAL) { 
                     h_prehcal_jetet_bx0_bxm1_case1_u->Fill((*reco_jets)[i].Pt()); 
                     h_prehcal_jeteta_bx0_bxm1_case1_u->Fill((*reco_jets)[i].Eta());  
                     h_prehcal_jetetaphi_bx0_bxm1_case1_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if((*trigger_bits)[420] && bxm1_etm[i] && !preHCAL) { 
                     h_posthcal_jetet_bx0_bxm1_case1_u->Fill((*reco_jets)[i].Pt()); 
                     h_posthcal_jeteta_bx0_bxm1_case1_u->Fill((*reco_jets)[i].Eta());  
                     h_posthcal_jetetaphi_bx0_bxm1_case1_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(!(*trigger_bits)[420] && (*trigger_bits)[309] && bxm1_jet[i] && preHCAL) { 
                     h_prehcal_jetet_bx0_bxm1_case2_u->Fill((*reco_jets)[i].Pt()); 
                     h_prehcal_jeteta_bx0_bxm1_case2_u->Fill((*reco_jets)[i].Eta());  
                     h_prehcal_jetetaphi_bx0_bxm1_case2_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(!(*trigger_bits)[420] && (*trigger_bits)[309] && bxm1_jet[i] && !preHCAL) { 
                     h_posthcal_jetet_bx0_bxm1_case2_u->Fill((*reco_jets)[i].Pt()); 
                     h_posthcal_jeteta_bx0_bxm1_case2_u->Fill((*reco_jets)[i].Eta());  
                     h_posthcal_jetetaphi_bx0_bxm1_case2_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && bxm1_tau[i] && preHCAL) { 
                     h_prehcal_jetet_bx0_bxm1_case3_u->Fill((*reco_jets)[i].Pt()); 
                     h_prehcal_jeteta_bx0_bxm1_case3_u->Fill((*reco_jets)[i].Eta());  
                     h_prehcal_jetetaphi_bx0_bxm1_case3_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && bxm1_tau[i] && !preHCAL) { 
                     h_posthcal_jetet_bx0_bxm1_case3_u->Fill((*reco_jets)[i].Pt()); 
                     h_posthcal_jeteta_bx0_bxm1_case3_u->Fill((*reco_jets)[i].Eta());  
                     h_posthcal_jetetaphi_bx0_bxm1_case3_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi()); 
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && bxm1_isotau[i] && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_case4_u->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_case4_u->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_case4_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && bxm1_isotau[i] && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_case4_u->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_case4_u->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_case4_u->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
               } // jet loop
            } // unprefirable
            if(isFirstBunchInTrain == 1){
               if(preHCAL) {
                     h_prehcal_dijet_bx0_f->Fill((j1+j2).M());
               }
               if(!preHCAL) {
                  h_posthcal_dijet_bx0_f->Fill((j1+j2).M());
               }
               if(L1FinalOR_bxm1 && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_f->Fill((j1+j2).M());
               }
               if(L1FinalOR_bxm1 && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_f->Fill((j1+j2).M());
               }
               if((*trigger_bits)[420] && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case1_f->Fill((j1+j2).M());
               }
               if((*trigger_bits)[420] && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case1_f->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && (*trigger_bits)[309] && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case2_f->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && (*trigger_bits)[309] && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case2_f->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case3_f->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case3_f->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && (bxm1_isotau[0] || bxm1_isotau[1]) && preHCAL) {
                  h_prehcal_dijet_bx0_bxm1_case4_f->Fill((j1+j2).M());
               }
               if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && (bxm1_isotau[0] || bxm1_isotau[1]) && !preHCAL) {
                  h_posthcal_dijet_bx0_bxm1_case4_f->Fill((j1+j2).M());
               }

               for(unsigned int i = 0; i < reco_jets->size(); i++){
                  if(preHCAL) {
                     h_prehcal_jetet_bx0_f->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_f->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!preHCAL) {
                     h_posthcal_jetet_bx0_f->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_f->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(L1FinalOR_bxm1 && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_f->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_f->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(L1FinalOR_bxm1 && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_f->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_f->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if((*trigger_bits)[420] && bxm1_etm[i] && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_case1_f->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_case1_f->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_case1_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if((*trigger_bits)[420] && bxm1_etm[i] && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_case1_f->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_case1_f->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_case1_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && (*trigger_bits)[309] && bxm1_jet[i] && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_case2_f->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_case2_f->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_case2_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && (*trigger_bits)[309] && bxm1_jet[i] && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_case2_f->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_case2_f->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_case2_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && bxm1_tau[i] && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_case3_f->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_case3_f->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_case3_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && (*trigger_bits)[263] && bxm1_tau[i] && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_case3_f->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_case3_f->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_case3_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && bxm1_isotau[i] && preHCAL) {
                     h_prehcal_jetet_bx0_bxm1_case4_f->Fill((*reco_jets)[i].Pt());
                     h_prehcal_jeteta_bx0_bxm1_case4_f->Fill((*reco_jets)[i].Eta());
                     h_prehcal_jetetaphi_bx0_bxm1_case4_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
                  if(!(*trigger_bits)[420] && !(*trigger_bits)[309] && !(*trigger_bits)[263] && bxm1_isotau[i] && !preHCAL) {
                     h_posthcal_jetet_bx0_bxm1_case4_f->Fill((*reco_jets)[i].Pt());
                     h_posthcal_jeteta_bx0_bxm1_case4_f->Fill((*reco_jets)[i].Eta());
                     h_posthcal_jetetaphi_bx0_bxm1_case4_f->Fill((*reco_jets)[i].Eta(), (*reco_jets)[i].Phi());
                  }
               } // jet loop
            } // firstbunchintrain
         } // dijet condition
      } // /njet condition
   } 
}

void postan::BookHistos(const char* file2){
   fileName = new TFile(file2, "RECREATE");
   fileName->cd();
   float mvalues[11] = {1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500};
   float ptvalues[21] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 900, 1000, 1200, 1500, 2000, 3000};

   // un prefirable 
   h_prehcal_dijet_bx0_u = new TH1F("h_prehcal_dijet_bx0_u", "h_prehcal_dijet_bx0_u", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_u = new TH1F("h_prehcal_dijet_bx0_bxm1_u", "h_prehcal_dijet_bx0_bxm1_u", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case1_u = new TH1F("h_prehcal_dijet_bx0_bxm1_case1_u", "h_prehcal_dijet_bx0_bxm1_case1_u", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case2_u = new TH1F("h_prehcal_dijet_bx0_bxm1_case2_u", "h_prehcal_dijet_bx0_bxm1_case2_u", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case3_u = new TH1F("h_prehcal_dijet_bx0_bxm1_case3_u", "h_prehcal_dijet_bx0_bxm1_case3_u", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case4_u = new TH1F("h_prehcal_dijet_bx0_bxm1_case4_u", "h_prehcal_dijet_bx0_bxm1_case4_u", 10, mvalues);
   h_prehcal_jetet_bx0_u = new TH1F("h_prehcal_jetet_bx0_u", "h_prehcal_jetet_bx0_u", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_u = new TH1F("h_prehcal_jetet_bx0_bxm1_u", "h_prehcal_jetet_bx0_bxm1_u", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case1_u = new TH1F("h_prehcal_jetet_bx0_bxm1_case1_u", "h_prehcal_jetet_bx0_bxm1_case1_u", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case2_u = new TH1F("h_prehcal_jetet_bx0_bxm1_case2_u", "h_prehcal_jetet_bx0_bxm1_case2_u", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case3_u = new TH1F("h_prehcal_jetet_bx0_bxm1_case3_u", "h_prehcal_jetet_bx0_bxm1_case3_u", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case4_u = new TH1F("h_prehcal_jetet_bx0_bxm1_case4_u", "h_prehcal_jetet_bx0_bxm1_case4_u", 20, ptvalues);
   h_prehcal_jeteta_bx0_u = new TH1F("h_prehcal_jeteta_bx0_u", "h_prehcal_jeteta_bx0_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_u", "h_prehcal_jeteta_bx0_bxm1_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case1_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_case1_u", "h_prehcal_jeteta_bx0_bxm1_case1_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case2_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_case2_u", "h_prehcal_jeteta_bx0_bxm1_case2_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case3_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_case3_u", "h_prehcal_jeteta_bx0_bxm1_case3_u", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case4_u = new TH1F("h_prehcal_jeteta_bx0_bxm1_case4_u", "h_prehcal_jeteta_bx0_bxm1_case4_u", 40, -5, 5);
   h_prehcal_jetetaphi_bx0_u = new TH2F("h_prehcal_jetetaphi_bx0_u", "h_prehcal_jetetaphi_bx0_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_u", "h_prehcal_jetetaphi_bx0_bxm1_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case1_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case1_u", "h_prehcal_jetetaphi_bx0_bxm1_case1_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case2_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case2_u", "h_prehcal_jetetaphi_bx0_bxm1_case2_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case3_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case3_u", "h_prehcal_jetetaphi_bx0_bxm1_case3_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case4_u = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case4_u", "h_prehcal_jetetaphi_bx0_bxm1_case4_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_dijet_bx0_u = new TH1F("h_posthcal_dijet_bx0_u", "h_posthcal_dijet_bx0_u", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_u = new TH1F("h_posthcal_dijet_bx0_bxm1_u", "h_posthcal_dijet_bx0_bxm1_u", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case1_u = new TH1F("h_posthcal_dijet_bx0_bxm1_case1_u", "h_posthcal_dijet_bx0_bxm1_case1_u", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case2_u = new TH1F("h_posthcal_dijet_bx0_bxm1_case2_u", "h_posthcal_dijet_bx0_bxm1_case2_u", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case3_u = new TH1F("h_posthcal_dijet_bx0_bxm1_case3_u", "h_posthcal_dijet_bx0_bxm1_case3_u", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case4_u = new TH1F("h_posthcal_dijet_bx0_bxm1_case4_u", "h_posthcal_dijet_bx0_bxm1_case4_u", 10, mvalues);
   h_posthcal_jetet_bx0_u = new TH1F("h_posthcal_jetet_bx0_u", "h_posthcal_jetet_bx0_u", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_u = new TH1F("h_posthcal_jetet_bx0_bxm1_u", "h_posthcal_jetet_bx0_bxm1_u", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case1_u = new TH1F("h_posthcal_jetet_bx0_bxm1_case1_u", "h_posthcal_jetet_bx0_bxm1_case1_u", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case2_u = new TH1F("h_posthcal_jetet_bx0_bxm1_case2_u", "h_posthcal_jetet_bx0_bxm1_case2_u", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case3_u = new TH1F("h_posthcal_jetet_bx0_bxm1_case3_u", "h_posthcal_jetet_bx0_bxm1_case3_u", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case4_u = new TH1F("h_posthcal_jetet_bx0_bxm1_case4_u", "h_posthcal_jetet_bx0_bxm1_case4_u", 20, ptvalues);
   h_posthcal_jeteta_bx0_u = new TH1F("h_posthcal_jeteta_bx0_u", "h_posthcal_jeteta_bx0_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_u", "h_posthcal_jeteta_bx0_bxm1_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case1_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_case1_u", "h_posthcal_jeteta_bx0_bxm1_case1_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case2_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_case2_u", "h_posthcal_jeteta_bx0_bxm1_case2_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case3_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_case3_u", "h_posthcal_jeteta_bx0_bxm1_case3_u", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case4_u = new TH1F("h_posthcal_jeteta_bx0_bxm1_case4_u", "h_posthcal_jeteta_bx0_bxm1_case4_u", 40, -5, 5);
   h_posthcal_jetetaphi_bx0_u = new TH2F("h_posthcal_jetetaphi_bx0_u", "h_posthcal_jetetaphi_bx0_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_u", "h_posthcal_jetetaphi_bx0_bxm1_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case1_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case1_u", "h_posthcal_jetetaphi_bx0_bxm1_case1_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case2_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case2_u", "h_posthcal_jetetaphi_bx0_bxm1_case2_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case3_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case3_u", "h_posthcal_jetetaphi_bx0_bxm1_case3_u", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case4_u = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case4_u", "h_posthcal_jetetaphi_bx0_bxm1_case4_u", 40, -5, 5, 40, -M_PI, M_PI);
   // first bunch in train
   h_prehcal_dijet_bx0_f = new TH1F("h_prehcal_dijet_bx0_f", "h_prehcal_dijet_bx0_f", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_f = new TH1F("h_prehcal_dijet_bx0_bxm1_f", "h_prehcal_dijet_bx0_bxm1_f", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case1_f = new TH1F("h_prehcal_dijet_bx0_bxm1_case1_f", "h_prehcal_dijet_bx0_bxm1_case1_f", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case2_f = new TH1F("h_prehcal_dijet_bx0_bxm1_case2_f", "h_prehcal_dijet_bx0_bxm1_case2_f", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case3_f = new TH1F("h_prehcal_dijet_bx0_bxm1_case3_f", "h_prehcal_dijet_bx0_bxm1_case3_f", 10, mvalues);
   h_prehcal_dijet_bx0_bxm1_case4_f = new TH1F("h_prehcal_dijet_bx0_bxm1_case4_f", "h_prehcal_dijet_bx0_bxm1_case4_f", 10, mvalues);
   h_prehcal_jetet_bx0_f = new TH1F("h_prehcal_jetet_bx0_f", "h_prehcal_jetet_bx0_f", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_f = new TH1F("h_prehcal_jetet_bx0_bxm1_f", "h_prehcal_jetet_bx0_bxm1_f", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case1_f = new TH1F("h_prehcal_jetet_bx0_bxm1_case1_f", "h_prehcal_jetet_bx0_bxm1_case1_f", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case2_f = new TH1F("h_prehcal_jetet_bx0_bxm1_case2_f", "h_prehcal_jetet_bx0_bxm1_case2_f", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case3_f = new TH1F("h_prehcal_jetet_bx0_bxm1_case3_f", "h_prehcal_jetet_bx0_bxm1_case3_f", 20, ptvalues);
   h_prehcal_jetet_bx0_bxm1_case4_f = new TH1F("h_prehcal_jetet_bx0_bxm1_case4_f", "h_prehcal_jetet_bx0_bxm1_case4_f", 20, ptvalues);
   h_prehcal_jeteta_bx0_f = new TH1F("h_prehcal_jeteta_bx0_f", "h_prehcal_jeteta_bx0_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_f", "h_prehcal_jeteta_bx0_bxm1_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case1_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_case1_f", "h_prehcal_jeteta_bx0_bxm1_case1_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case2_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_case2_f", "h_prehcal_jeteta_bx0_bxm1_case2_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case3_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_case3_f", "h_prehcal_jeteta_bx0_bxm1_case3_f", 40, -5, 5);
   h_prehcal_jeteta_bx0_bxm1_case4_f = new TH1F("h_prehcal_jeteta_bx0_bxm1_case4_f", "h_prehcal_jeteta_bx0_bxm1_case4_f", 40, -5, 5);
   h_prehcal_jetetaphi_bx0_f = new TH2F("h_prehcal_jetetaphi_bx0_f", "h_prehcal_jetetaphi_bx0_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_f", "h_prehcal_jetetaphi_bx0_bxm1_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case1_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case1_f", "h_prehcal_jetetaphi_bx0_bxm1_case1_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case2_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case2_f", "h_prehcal_jetetaphi_bx0_bxm1_case2_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case3_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case3_f", "h_prehcal_jetetaphi_bx0_bxm1_case3_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_prehcal_jetetaphi_bx0_bxm1_case4_f = new TH2F("h_prehcal_jetetaphi_bx0_bxm1_case4_f", "h_prehcal_jetetaphi_bx0_bxm1_case4_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_dijet_bx0_f = new TH1F("h_posthcal_dijet_bx0_f", "h_posthcal_dijet_bx0_f", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_f = new TH1F("h_posthcal_dijet_bx0_bxm1_f", "h_posthcal_dijet_bx0_bxm1_f", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case1_f = new TH1F("h_posthcal_dijet_bx0_bxm1_case1_f", "h_posthcal_dijet_bx0_bxm1_case1_f", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case2_f = new TH1F("h_posthcal_dijet_bx0_bxm1_case2_f", "h_posthcal_dijet_bx0_bxm1_case2_f", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case3_f = new TH1F("h_posthcal_dijet_bx0_bxm1_case3_f", "h_posthcal_dijet_bx0_bxm1_case3_f", 10, mvalues);
   h_posthcal_dijet_bx0_bxm1_case4_f = new TH1F("h_posthcal_dijet_bx0_bxm1_case4_f", "h_posthcal_dijet_bx0_bxm1_case4_f", 10, mvalues);
   h_posthcal_jetet_bx0_f = new TH1F("h_posthcal_jetet_bx0_f", "h_posthcal_jetet_bx0_f", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_f = new TH1F("h_posthcal_jetet_bx0_bxm1_f", "h_posthcal_jetet_bx0_bxm1_f", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case1_f = new TH1F("h_posthcal_jetet_bx0_bxm1_case1_f", "h_posthcal_jetet_bx0_bxm1_case1_f", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case2_f = new TH1F("h_posthcal_jetet_bx0_bxm1_case2_f", "h_posthcal_jetet_bx0_bxm1_case2_f", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case3_f = new TH1F("h_posthcal_jetet_bx0_bxm1_case3_f", "h_posthcal_jetet_bx0_bxm1_case3_f", 20, ptvalues);
   h_posthcal_jetet_bx0_bxm1_case4_f = new TH1F("h_posthcal_jetet_bx0_bxm1_case4_f", "h_posthcal_jetet_bx0_bxm1_case4_f", 20, ptvalues);
   h_posthcal_jeteta_bx0_f = new TH1F("h_posthcal_jeteta_bx0_f", "h_posthcal_jeteta_bx0_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_f", "h_posthcal_jeteta_bx0_bxm1_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case1_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_case1_f", "h_posthcal_jeteta_bx0_bxm1_case1_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case2_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_case2_f", "h_posthcal_jeteta_bx0_bxm1_case2_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case3_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_case3_f", "h_posthcal_jeteta_bx0_bxm1_case3_f", 40, -5, 5);
   h_posthcal_jeteta_bx0_bxm1_case4_f = new TH1F("h_posthcal_jeteta_bx0_bxm1_case4_f", "h_posthcal_jeteta_bx0_bxm1_case4_f", 40, -5, 5);
   h_posthcal_jetetaphi_bx0_f = new TH2F("h_posthcal_jetetaphi_bx0_f", "h_posthcal_jetetaphi_bx0_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_f", "h_posthcal_jetetaphi_bx0_bxm1_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case1_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case1_f", "h_posthcal_jetetaphi_bx0_bxm1_case1_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case2_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case2_f", "h_posthcal_jetetaphi_bx0_bxm1_case2_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case3_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case3_f", "h_posthcal_jetetaphi_bx0_bxm1_case3_f", 40, -5, 5, 40, -M_PI, M_PI);
   h_posthcal_jetetaphi_bx0_bxm1_case4_f = new TH2F("h_posthcal_jetetaphi_bx0_bxm1_case4_f", "h_posthcal_jetetaphi_bx0_bxm1_case4_f", 40, -5, 5, 40, -M_PI, M_PI);

}
