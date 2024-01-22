#ifndef postan_h
#define postan_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include <stdio.h>
#include <TString.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TH2F.h>

using namespace std;

#include "vector"

class postan {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TFile *fileName;

   TH1F *h_prehcal_dijet_bx0_u;
   TH1F *h_prehcal_dijet_bx0_bxm1_u;
   TH1F *h_prehcal_dijet_bx0_bxm1_case1_u, *h_prehcal_dijet_bx0_bxm1_case2_u, *h_prehcal_dijet_bx0_bxm1_case3_u, *h_prehcal_dijet_bx0_bxm1_case4_u;
   TH1F *h_prehcal_jetet_bx0_u;
   TH1F *h_prehcal_jetet_bx0_bxm1_u;
   TH1F *h_prehcal_jetet_bx0_bxm1_case1_u, *h_prehcal_jetet_bx0_bxm1_case2_u, *h_prehcal_jetet_bx0_bxm1_case3_u, *h_prehcal_jetet_bx0_bxm1_case4_u;
   TH1F *h_prehcal_jeteta_bx0_u;
   TH1F *h_prehcal_jeteta_bx0_bxm1_u;
   TH1F *h_prehcal_jeteta_bx0_bxm1_case1_u, *h_prehcal_jeteta_bx0_bxm1_case2_u, *h_prehcal_jeteta_bx0_bxm1_case3_u, *h_prehcal_jeteta_bx0_bxm1_case4_u;
   TH2F *h_prehcal_jetetaphi_bx0_u;
   TH2F *h_prehcal_jetetaphi_bx0_bxm1_u;
   TH2F *h_prehcal_jetetaphi_bx0_bxm1_case1_u, *h_prehcal_jetetaphi_bx0_bxm1_case2_u, *h_prehcal_jetetaphi_bx0_bxm1_case3_u, *h_prehcal_jetetaphi_bx0_bxm1_case4_u;
   TH1F *h_posthcal_dijet_bx0_u;
   TH1F *h_posthcal_dijet_bx0_bxm1_u;
   TH1F *h_posthcal_dijet_bx0_bxm1_case1_u, *h_posthcal_dijet_bx0_bxm1_case2_u, *h_posthcal_dijet_bx0_bxm1_case3_u, *h_posthcal_dijet_bx0_bxm1_case4_u;
   TH1F *h_posthcal_jetet_bx0_u;
   TH1F *h_posthcal_jetet_bx0_bxm1_u;
   TH1F *h_posthcal_jetet_bx0_bxm1_case1_u, *h_posthcal_jetet_bx0_bxm1_case2_u, *h_posthcal_jetet_bx0_bxm1_case3_u, *h_posthcal_jetet_bx0_bxm1_case4_u;
   TH1F *h_posthcal_jeteta_bx0_u;
   TH1F *h_posthcal_jeteta_bx0_bxm1_u;
   TH1F *h_posthcal_jeteta_bx0_bxm1_case1_u, *h_posthcal_jeteta_bx0_bxm1_case2_u, *h_posthcal_jeteta_bx0_bxm1_case3_u, *h_posthcal_jeteta_bx0_bxm1_case4_u;
   TH2F *h_posthcal_jetetaphi_bx0_u;
   TH2F *h_posthcal_jetetaphi_bx0_bxm1_u;
   TH2F *h_posthcal_jetetaphi_bx0_bxm1_case1_u, *h_posthcal_jetetaphi_bx0_bxm1_case2_u, *h_posthcal_jetetaphi_bx0_bxm1_case3_u, *h_posthcal_jetetaphi_bx0_bxm1_case4_u;

   TH1F *h_prehcal_dijet_bx0_f;
   TH1F *h_prehcal_dijet_bx0_bxm1_f;
   TH1F *h_prehcal_dijet_bx0_bxm1_case1_f, *h_prehcal_dijet_bx0_bxm1_case2_f, *h_prehcal_dijet_bx0_bxm1_case3_f, *h_prehcal_dijet_bx0_bxm1_case4_f;
   TH1F *h_prehcal_jetet_bx0_f;
   TH1F *h_prehcal_jetet_bx0_bxm1_f;
   TH1F *h_prehcal_jetet_bx0_bxm1_case1_f, *h_prehcal_jetet_bx0_bxm1_case2_f, *h_prehcal_jetet_bx0_bxm1_case3_f, *h_prehcal_jetet_bx0_bxm1_case4_f;
   TH1F *h_prehcal_jeteta_bx0_f;
   TH1F *h_prehcal_jeteta_bx0_bxm1_f;
   TH1F *h_prehcal_jeteta_bx0_bxm1_case1_f, *h_prehcal_jeteta_bx0_bxm1_case2_f, *h_prehcal_jeteta_bx0_bxm1_case3_f, *h_prehcal_jeteta_bx0_bxm1_case4_f;
   TH2F *h_prehcal_jetetaphi_bx0_f;
   TH2F *h_prehcal_jetetaphi_bx0_bxm1_f;
   TH2F *h_prehcal_jetetaphi_bx0_bxm1_case1_f, *h_prehcal_jetetaphi_bx0_bxm1_case2_f, *h_prehcal_jetetaphi_bx0_bxm1_case3_f, *h_prehcal_jetetaphi_bx0_bxm1_case4_f;
   TH1F *h_posthcal_dijet_bx0_f;
   TH1F *h_posthcal_dijet_bx0_bxm1_f;
   TH1F *h_posthcal_dijet_bx0_bxm1_case1_f, *h_posthcal_dijet_bx0_bxm1_case2_f, *h_posthcal_dijet_bx0_bxm1_case3_f, *h_posthcal_dijet_bx0_bxm1_case4_f;
   TH1F *h_posthcal_jetet_bx0_f;
   TH1F *h_posthcal_jetet_bx0_bxm1_f;
   TH1F *h_posthcal_jetet_bx0_bxm1_case1_f, *h_posthcal_jetet_bx0_bxm1_case2_f, *h_posthcal_jetet_bx0_bxm1_case3_f, *h_posthcal_jetet_bx0_bxm1_case4_f;
   TH1F *h_posthcal_jeteta_bx0_f;
   TH1F *h_posthcal_jeteta_bx0_bxm1_f;
   TH1F *h_posthcal_jeteta_bx0_bxm1_case1_f, *h_posthcal_jeteta_bx0_bxm1_case2_f, *h_posthcal_jeteta_bx0_bxm1_case3_f, *h_posthcal_jeteta_bx0_bxm1_case4_f;
   TH2F *h_posthcal_jetetaphi_bx0_f;
   TH2F *h_posthcal_jetetaphi_bx0_bxm1_f;
   TH2F *h_posthcal_jetetaphi_bx0_bxm1_case1_f, *h_posthcal_jetetaphi_bx0_bxm1_case2_f, *h_posthcal_jetetaphi_bx0_bxm1_case3_f, *h_posthcal_jetetaphi_bx0_bxm1_case4_f;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_num;
   Int_t           lumi;
   Int_t           event_num;
   Int_t           isUnprefirable;
   Int_t           isFirstBunchInTrain;
   Int_t           L1FinalOR_bxm1;
   Int_t           idx_L1_FirstBunchBeforeTrain;
   vector<bool>    *trigger_bits;
   vector<TLorentzVector> *reco_jets;
   vector<bool>    *reco_jetId;
   vector<TLorentzVector> *bxm1_jets;
   vector<TLorentzVector> *bxm1_taus;
   vector<TLorentzVector> *bxm1_isotaus;
   Double_t bxm1_etmhf_pt;
   Double_t bxm1_etmhf_phi;
   vector<TLorentzVector> *match_l1_bx0;
   vector<TLorentzVector> *match_l1_bxm1;
   vector<TLorentzVector> *match_l1_bxm2;
   vector<TLorentzVector> *match_l1_bx1;
   vector<TLorentzVector> *match_l1_bx2;

   // List of branches
   TBranch        *b_run_num;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event_num;   //!
   TBranch        *b_isUnprefirable;   //!
   TBranch        *b_isFirstBunchInTrain;   //!
   TBranch        *b_L1FinalOR_bxm1;   //!
   TBranch        *b_idx_L1_FirstBunchBeforeTrain;   //!
   TBranch        *b_trigger_bits;   //!
   TBranch        *b_reco_jets;   //!
   TBranch        *b_reco_jetId;   //!
   TBranch        *b_bxm1_jets;   //!
   TBranch        *b_bxm1_taus;   //!
   TBranch        *b_bxm1_isotaus;   //!
   TBranch        *b_bxm1_etmhf_pt;   //!
   TBranch        *b_bxm1_etmhf_phi;   //!
   TBranch        *b_match_l1_bx0;   //!
   TBranch        *b_match_l1_bxm1;   //!
   TBranch        *b_match_l1_bxm2;   //!
   TBranch        *b_match_l1_bx1;   //!
   TBranch        *b_match_l1_bx2;   //!

   postan(string fileToOpen, const char* file2);
   virtual ~postan();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     BookHistos(const char* file2);
};

#endif

#ifdef postan_cxx
postan::postan(string fileToOpen, const char* file2) 
{
  
   BookHistos(file2);
   TChain *chain = new TChain("demo/eventTree");
   ifstream file;
   file.open(fileToOpen.c_str(), ifstream::in );
   char filename[2000];
   while (true) {
     file >> filename;
     if( file.eof() ) break;
         chain->Add(filename);
         cout<<"Added "<<filename<<endl;
   }//loop over while
   Init(chain);
}

postan::~postan()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
   fileName->cd();
   fileName->Write();
   fileName->Close();
}

Int_t postan::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t postan::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void postan::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trigger_bits = 0;
   reco_jets = 0;
   reco_jetId = 0;
   bxm1_jets = 0;
   bxm1_taus = 0;
   bxm1_isotaus = 0;
   match_l1_bx0 = 0;
   match_l1_bxm1 = 0;
   match_l1_bxm2 = 0;
   match_l1_bx1 = 0;
   match_l1_bx2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_num", &run_num, &b_run_num);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event_num", &event_num, &b_event_num);
   fChain->SetBranchAddress("isUnprefirable", &isUnprefirable, &b_isUnprefirable);
   fChain->SetBranchAddress("isFirstBunchInTrain", &isFirstBunchInTrain, &b_isFirstBunchInTrain);
   fChain->SetBranchAddress("L1FinalOR_bxm1", &L1FinalOR_bxm1, &b_L1FinalOR_bxm1);
   fChain->SetBranchAddress("idx_L1_FirstBunchBeforeTrain", &idx_L1_FirstBunchBeforeTrain, &b_idx_L1_FirstBunchBeforeTrain);
   fChain->SetBranchAddress("trigger_bits", &trigger_bits, &b_trigger_bits);
   fChain->SetBranchAddress("reco_jets", &reco_jets, &b_reco_jets);
   fChain->SetBranchAddress("reco_jetId", &reco_jetId, &b_reco_jetId);
   fChain->SetBranchAddress("bxm1_jets", &bxm1_jets, &b_bxm1_jets);
   fChain->SetBranchAddress("bxm1_taus", &bxm1_taus, &b_bxm1_taus);
   fChain->SetBranchAddress("bxm1_isotaus", &bxm1_isotaus, &b_bxm1_isotaus);
   fChain->SetBranchAddress("bxm1_etmhf_pt", &bxm1_etmhf_pt, &b_bxm1_etmhf_pt);
   fChain->SetBranchAddress("bxm1_etmhf_phi", &bxm1_etmhf_phi, &b_bxm1_etmhf_phi);
   fChain->SetBranchAddress("match_l1_bx0", &match_l1_bx0, &b_match_l1_bx0);
   fChain->SetBranchAddress("match_l1_bxm1", &match_l1_bxm1, &b_match_l1_bxm1);
   fChain->SetBranchAddress("match_l1_bxm2", &match_l1_bxm2, &b_match_l1_bxm2);
   fChain->SetBranchAddress("match_l1_bx1", &match_l1_bx1, &b_match_l1_bx1);
   fChain->SetBranchAddress("match_l1_bx2", &match_l1_bx2, &b_match_l1_bx2);
   Notify();
}

Bool_t postan::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void postan::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t postan::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef postan_cxx
