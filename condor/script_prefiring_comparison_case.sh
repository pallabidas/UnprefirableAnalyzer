for era in pre post;do

if [ ${era} = "pre" ]
then
  run="Run < 368822"
fi

if [ ${era} = "post" ]
then
  run="Run >= 368822"
fi

for type in _u _f; do

if [ ${type} = "_u" ]
then
  name="Unprefirable"
fi

if [ ${type} = "_f" ]
then
  name="First bunch in train"
fi

for var in dijet jetet jeteta; do

if [ ${var} = "dijet" ]
then
  label="m_{jj} [GeV]"
fi

if [ ${var} = "jetet" ]
then
  label="p_{T} [GeV]"
fi

if [ ${var} = "jeteta" ]
then 
  label="#eta"
fi

cat>temp.C<<EOF
{
  TCanvas *c1 =new TCanvas("c1", " ", 0, 0, 700, 700);

  c1->Range(0,0,1,1);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  c1->Draw();
  c1->SetLogy();
  gStyle->SetOptStat(0);

  TFile *g1 = TFile::Open("Jobs_new/histo_JME_20jan.root");
  TH1F *h1 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0_bxm1_case1${type}");
  h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX())+h1->GetBinContent(h1->GetNbinsX()+1));
  TH1F *h2 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0${type}");
  h2->SetBinContent(h2->GetNbinsX(), h2->GetBinContent(h2->GetNbinsX())+h2->GetBinContent(h2->GetNbinsX()+1));

  //TH1F *h0 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0_bxm1_case1${type}");
  TH1F *h0 = (TH1F*)h1->Clone();
  for(int i=0; i<h0->GetNbinsX(); i++){
    h0->SetBinContent(i, 0.);
  }
  h0->SetLineColorAlpha(kWhite, 1.);
  h0->SetTitle("");
  h0->GetXaxis()->SetTitle("Offline ${label}");
  h0->GetXaxis()->SetTitleSize(0.04);
  h0->GetXaxis()->SetTitleOffset(1.0);
  //h0->GetYaxis()->SetTitle("BX=-1/(BX=-1 OR BX=0)");
  h0->GetYaxis()->SetTitle("Fraction in BX=-1");
  h0->GetYaxis()->SetTitleSize(0.04);
  h0->GetYaxis()->SetTitleOffset(1.2);
  h0->GetYaxis()->SetRangeUser(0.00001,20);
  h0->Draw();

  TH1F *h3 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0_bxm1_case2${type}");
  h3->SetBinContent(h3->GetNbinsX(), h3->GetBinContent(h3->GetNbinsX())+h3->GetBinContent(h3->GetNbinsX()+1));
  TH1F *h4 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0${type}");
  h4->SetBinContent(h4->GetNbinsX(), h4->GetBinContent(h4->GetNbinsX())+h4->GetBinContent(h4->GetNbinsX()+1));

  TH1F *h5 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0_bxm1_case3${type}");
  h5->SetBinContent(h5->GetNbinsX(), h5->GetBinContent(h5->GetNbinsX())+h5->GetBinContent(h5->GetNbinsX()+1));
  TH1F *h6 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0${type}");
  h6->SetBinContent(h6->GetNbinsX(), h6->GetBinContent(h6->GetNbinsX())+h6->GetBinContent(h6->GetNbinsX()+1));

  TH1F *h7 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0_bxm1_case4${type}");
  h7->SetBinContent(h7->GetNbinsX(), h7->GetBinContent(h7->GetNbinsX())+h7->GetBinContent(h7->GetNbinsX()+1));
  TH1F *h8 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0${type}");
  h8->SetBinContent(h8->GetNbinsX(), h8->GetBinContent(h8->GetNbinsX())+h8->GetBinContent(h8->GetNbinsX()+1));

  TH1F *h9 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0_bxm1${type}");
  h9->SetBinContent(h9->GetNbinsX(), h9->GetBinContent(h9->GetNbinsX())+h9->GetBinContent(h9->GetNbinsX()+1));
  TH1F *h10 = (TH1F*)g1->Get("h_${era}hcal_${var}_bx0${type}");
  h10->SetBinContent(h10->GetNbinsX(), h10->GetBinContent(h10->GetNbinsX())+h10->GetBinContent(h10->GetNbinsX()+1));

  TEfficiency* pEff0 = 0;
  TEfficiency* pEff1 = 0;
  TEfficiency* pEff2 = 0;
  TEfficiency* pEff3 = 0;
  TEfficiency* pEff4 = 0;
  
  if(TEfficiency::CheckConsistency(*h1,*h2))
  {
    pEff0 = new TEfficiency(*h1,*h2);
    pEff0->SetLineWidth(2.);
    pEff0->SetLineColor(kBlack);
    pEff0->SetMarkerColor(kBlack);
    pEff0->SetMarkerStyle(24);
    pEff0->Draw("same");
  }
  
  if(TEfficiency::CheckConsistency(*h3,*h4))
  {
    pEff1 = new TEfficiency(*h3,*h4);
    pEff1->SetLineWidth(2.);
    pEff1->SetLineColor(kBlue);
    pEff1->SetMarkerColor(kBlue);
    pEff1->SetMarkerStyle(25);
    pEff1->Draw("same");
  }
  
  if(TEfficiency::CheckConsistency(*h5,*h6))
  {
    pEff2 = new TEfficiency(*h5,*h6);
    pEff2->SetLineWidth(2.);
    pEff2->SetLineColor(kRed);
    pEff2->SetMarkerColor(kRed);
    pEff2->SetMarkerStyle(26);
    pEff2->Draw("same");
  }

  if(TEfficiency::CheckConsistency(*h7,*h8))
  {
    pEff3 = new TEfficiency(*h7,*h8);
    pEff3->SetLineWidth(2.);
    pEff3->SetLineColor(kGreen+1);
    pEff3->SetMarkerColor(kGreen+1);
    pEff3->SetMarkerStyle(27);
    pEff3->Draw("same");
  }

  if(TEfficiency::CheckConsistency(*h9,*h10))
  {
    pEff4 = new TEfficiency(*h9,*h10);
    pEff4->SetLineWidth(2.);
    pEff4->SetLineColor(kViolet+1);
    pEff4->SetMarkerColor(kViolet+1);
    pEff4->SetMarkerStyle(28);
    //pEff4->Draw("same");
  }

  //TLegend *legend1 = new TLegend(0.35, 0.6, 0.6, 0.75);
  TLegend *legend1 = new TLegend(0.2, 0.68, 0.45, 0.88);
  legend1->SetTextFont(42);
  legend1->SetLineColor(0);
  legend1->SetTextSize(0.03);
  legend1->SetFillColor(0);
  //legend1->SetHeader("180 GeV (BX=0)");
  legend1->SetHeader("${name}, ${run}");
  legend1->AddEntry(pEff0, "case1", "lp");
  legend1->AddEntry(pEff1, "case2", "lp");
  legend1->AddEntry(pEff2, "case3", "lp");
  legend1->AddEntry(pEff3, "case4", "lp");
  //legend1->AddEntry(pEff4, "L1FinalOR BX=-1", "lp");
  legend1->Draw("same");

  TLatex *t2b = new TLatex(0.35,0.85,"${name}, ${run}");
  t2b->SetNDC();
  t2b->SetTextFont(42);
  t2b->SetTextSize(0.03);
  t2b->SetTextAlign(20);
  //t2b->Draw("same");

  TLatex *t2a = new TLatex(0.5,0.9," #bf{CMS} #it{Preliminary}         28.9 fb^{-1} (2023, 13.6 TeV)");
  t2a->SetNDC();
  t2a->SetTextFont(42);
  t2a->SetTextSize(0.04);
  t2a->SetTextAlign(20);
  t2a->Draw("same");
  c1->SaveAs("/afs/cern.ch/work/p/pdas/www/L1DPG/Prefiring/prefiring_rates_${era}hcal_${var}${type}_20jan.pdf");
  c1->SaveAs("/afs/cern.ch/work/p/pdas/www/L1DPG/Prefiring/prefiring_rates_${era}hcal_${var}${type}_20jan.png");
}

EOF

root -l -b -q temp.C

done

done

done
