#include "TH1.h"
#include "TF1.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "ATLASStyle/AtlasStyle.C"
#include "ATLASStyle/AtlasUtils.C"
#include "ATLASStyle/AtlasLabels.C"

using namespace std;
TCanvas *c = new TCanvas("c","c",1100,750);
TFile *f2 = new TFile("mjj.root");

void draw(TString name, float xmin, float xmax, int Truth, int frac);
void text(double ymax, float labelx, float labley, int Truth);

int main(int argc,char **argv) {
    SetAtlasStyle ();
    TString dataset = argv[1];
    
    if(dataset=="MC"){
        TH1D* HistNTrkl = (TH1D*) f2->Get("HistNTrkl");
        TH1D* HistNTrkl_G = (TH1D*) f2->Get("HistNTrkl_G");
        TH1D* HistNTrkl_Q = (TH1D*) f2->Get("HistNTrkl_Q");
        TH1D* HistNTrks = (TH1D*) f2->Get("HistNTrks");
        TH1D* HistNTrks_G = (TH1D*) f2->Get("HistNTrks_G");
        TH1D* HistNTrks_Q = (TH1D*) f2->Get("HistNTrks_Q");
    
        draw("HistMjj", 400, 12000, 1, 0);
        text(0.85, 0.2, 0.2, 1);
        c->SaveAs(".mjjt.png");
    
        draw("HistMjj", 400, 12000, 1, 1);
        text(0.75, 0.6, 0.4, 1);
        c->SaveAs(".frat.png");
    
        draw("HistMjj", 400, 12000, 0, 0);
        text(0.85, 0.2, 0.2, 0);
        c->SaveAs(".mjj.png");
    
        draw("HistMjj", 400, 12000, 0, 1);
        text(0.85, 0.2, 0.85, 0);
        c->SaveAs(".fra.png");
    
        draw("HistLeadingJetPt", 400, 8200, 1, 0);
        text(0.85, 0.2, 0.2, 1);
        c->SaveAs(".LPtt.png");
      
        draw("HistLeadingJetPt", 400, 8200, 0, 0);
        text(0.85, 0.2, 0.2, 0);
        c->SaveAs(".LPt.png");
    
        draw("HistSubJetPt", 400, 8200, 1, 0);
        text(0.85, 0.2, 0.2, 1);
        c->SaveAs(".SPtt.png");
    
        draw("HistSubJetPt", 400, 8200, 0, 0);
        text(0.85, 0.2, 0.2, 0);
        c->SaveAs(".SPt.png");

        gPad->SetLogy(0);
        gPad->SetTopMargin(0.05);
        gPad->SetRightMargin(0.05);
        gPad->SetBottomMargin(0.16);
        gPad->SetLeftMargin(0.16);
        HistNTrkl_Q->SetLineColor(7);
        HistNTrkl_Q->SetMarkerColor(7);
        HistNTrkl_Q->Draw();
        HistNTrkl_G->SetLineColor(2);
        HistNTrkl_G->SetMarkerColor(2);
        HistNTrkl_G->Draw("same");
        myText(       0.7,  0.85, 1, "#sqrt{s}= 13 TeV");
        myMarkerText( 0.7, 0.75, 2, 20, "G",1);
        myMarkerText( 0.7, 0.65, 7, 20, "Q",1);
        ATLASLabel(0.6,0.2,"Preliminary");
        c->SaveAs(".NTrkl.png");
        
        HistNTrks_Q->SetLineColor(7);
        HistNTrks_Q->SetMarkerColor(7);
        HistNTrks_Q->Draw();
        HistNTrks_G->SetLineColor(2);
        HistNTrks_G->SetMarkerColor(2);
        HistNTrks_G->Draw("same");
        myText(       0.7,  0.85, 1, "#sqrt{s}= 13 TeV");
        myMarkerText( 0.7, 0.75, 2, 20, "G",1);
        myMarkerText( 0.7, 0.65, 7, 20, "Q",1);
        ATLASLabel(0.6,0.2,"Preliminary");
        c->SaveAs(".NTrks.png");
    }
    
    if(dataset=="data"){
        draw("HistMjj", 400, 12000, 0, 0);
        text(0.85, 0.2, 0.2, 0);
        c->SaveAs(".mjj.png");
    
        draw("HistMjj", 400, 12000, 0, 1);
        text(0.85, 0.2, 0.85, 0);
        c->SaveAs(".fra.png");
      
        draw("HistLeadingJetPt", 400, 8200, 0, 0);
        text(0.85, 0.2, 0.2, 0);
        c->SaveAs(".LPt.png");

        draw("HistSubJetPt", 400, 8200, 0, 0);
        text(0.85, 0.2, 0.2, 0);
        c->SaveAs(".SPt.png");
    }
}

void draw(TString name, float xmin, float xmax, int Truth, int frac){
    gPad->SetTopMargin(0.05);
    gPad->SetRightMargin(0.05);
    gPad->SetBottomMargin(0.16);
    gPad->SetLeftMargin(0.16);
    TString nameGG;
    TString nameQG;
    TString nameQQ;
    if(Truth==0){
        nameGG = name + "_GG";
        nameQG = name + "_QG";
        nameQQ = name + "_QQ";
    }
    if(Truth==1){
        nameGG = name + "_TruthGG";
        nameQG = name + "_TruthQG";
        nameQQ = name + "_TruthQQ";
    }
    
    TH1D* Hist = (TH1D*) f2->Get(name);
    TH1D* Hist_GG = (TH1D*) f2->Get(nameGG);
    TH1D* Hist_QG = (TH1D*) f2->Get(nameQG);
    TH1D* Hist_QQ = (TH1D*) f2->Get(nameQQ);
    
    gStyle->SetOptStat(0);
    Hist->SetAxisRange(xmin, xmax, "X");
    Hist->SetLineColor(0);
    Hist->SetMarkerColor(0);
    Hist_GG->SetLineColor(2);
    Hist_GG->SetMarkerColor(2);
    Hist_QG->SetLineColor(3);
    Hist_QG->SetMarkerColor(3);
    Hist_QQ->SetLineColor(7);
    Hist_QQ->SetMarkerColor(7);
    if(frac==1){
        gPad->SetLogy(0);
        Hist_GG->Divide(Hist);
        Hist_QG->Divide(Hist);
        Hist_QQ->Divide(Hist);
        Hist_QG->SetYTitle("fraction");
        Hist_QG->SetAxisRange(0, 1,"Y");
        Hist_QG->Draw();
    }
    else{
        gPad->SetLogy(1);
        Hist->Draw();
        Hist_QG->Draw("same");
    }
    Hist_GG->Draw("same");
    Hist_QQ->Draw("same");
}

void text(double ymax, float labelx, float labley, int Truth){
    myText(       0.7, ymax, 1, "#sqrt{s}= 13 TeV");
    if(Truth==0){
        myMarkerText( 0.7, ymax-0.05, 2, 20, "GG",1);
        myMarkerText( 0.7, ymax-0.1, 3, 20, "QG",1);
        myMarkerText( 0.7, ymax-0.15, 7, 20, "QQ",1);
    }
    if(Truth==1){
        myMarkerText( 0.7, ymax-0.05, 2, 20, "TruthGG",1);
        myMarkerText( 0.7, ymax-0.1, 3, 20, "TruthQG",1);
        myMarkerText( 0.7, ymax-0.15, 7, 20, "TruthQQ",1);
    }
    ATLASLabel(labelx, labley, "Preliminary");
}
