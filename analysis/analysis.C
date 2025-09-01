#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1I.h>
#include <TCanvas.h>

void analysis(){

    TFile *file = new TFile("beam.root", "READ");
    //print contents
    //file->ls();

    TTree *tree = (TTree*)file->Get("Block");
    //print contents
    //tree->Print();

    TBranch *branch = tree->GetBranch("fCopyNo");

    int fCopyNo;
    branch->SetAddress(&fCopyNo);

    TH1I *hist = new TH1I("fCopyNo", "fCopyNo", 10, 0, 10);

    //c1->cd();
    //Make log scale
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    tree->Draw("fCopyNo>>fCopyNo");
    c1->SetLogy();
    //hist->Draw();
    c1->Update();
}