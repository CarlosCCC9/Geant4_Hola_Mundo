#include "TH1.h"
#include "TSpectrum.h"
#include "TCanvas.h"

void peaks(){

    TFile *file = new TFile("analysis.root", "READ");
    TTree *tree = (TTree*)file->Get("DecayTime");
    TBranch *b_evt = tree->GetBranch("fCorrect");
    TBranch *b_time = tree->GetBranch("fTime");

    int evt;
    double time;
    int selected = 93;
    b_evt->SetAddress(&evt);
    b_time->SetAddress(&time);
    Long64_t nentries = b_evt->GetEntries();



    std::vector<int> fEvent_values;

    for(Long64_t i = 0; i < nentries; i++) {
        b_evt->GetEntry(i);
        fEvent_values.push_back(evt);
    }

    std::set<int> s_event(fEvent_values.begin(), fEvent_values.end());

    //for(auto i : s_event) std::cout << i << " ";
    //std::cout << "Number of unique decay events: " << s_event.size() <<std::endl;


    std::vector<double> time_diff;

    for (size_t i = 0; i < s_event.size(); i++){
        //print values in set
        //std::cout << *std::next(s_event.begin(), i) << " ";
        TH1D *hist = new TH1D(Form("hist_%d", *std::next(s_event.begin(), i)), Form("Decay Time for Event %d; Time (ns); Counts", *std::next(s_event.begin(), i)), 5000, 0, 20000);
        for (Long64_t j = 0; j < nentries; j++) {
            b_evt->GetEntry(j);
            b_time->GetEntry(j);
            if (evt == *std::next(s_event.begin(), i)) {
                hist->Fill(time);
            }
        }
        TSpectrum *s = new TSpectrum(2); // Search for up to 2 peaks
        Int_t nfound = s->Search(hist, 1, "new"); // Sigma=1, use new background estimation
        //printf("For Event %d, Found %d candidate peaks\n", *std::next(s_event.begin(), i), nfound);
        //std::cout << std::endl;
        // Delete histogram to free memory
        if(nfound == 2){
            Double_t *xpeaks = s->GetPositionX();
            //std::cout << "Time difference for event " << *std::next(s_event.begin(), i) << ": " << fabs(xpeaks[1] - xpeaks[0]) << " ns" << std::endl;
            time_diff.push_back(fabs(xpeaks[1] - xpeaks[0]));
        }

        delete hist;
        delete s;
    }

    //store time differences in a .txt file
    std::ofstream outfile("time_differences.txt");
    for (size_t i = 0; i < time_diff.size(); i++) {
        outfile << time_diff[i] << std::endl;
    }
    outfile.close();





    /*
    //create histogram of time differences
    TH1D *hist_diff = new TH1D("hist_diff", "Time Differences between Peaks; Time Difference (ns); Counts", 100, 0, 3000);

    for (size_t i = 0; i < time_diff.size(); i++) {
        hist_diff->Fill(time_diff[i]);
    }
    TCanvas *c2 = new TCanvas("c2", "Time Differences", 800, 600);
    hist_diff->Draw();
    c2->Update();
    */


    /*
    //Estudair un solo caso
    TH1D *hist = new TH1D("hist", "Decay Time; Time (ns); Counts", 5000, 0, 20000);
    for (Long64_t i = 0; i < nentries; i++) {
        b_evt->GetEntry(i);
        b_time->GetEntry(i);
        if (evt == selected) {
            hist->Fill(time);
        }
    }

    TCanvas *c1 = new TCanvas("c1", "Peak Finding", 800, 600);
    hist->Draw();

    // Create TSpectrum object
    TSpectrum *s = new TSpectrum(2); // Search for up to 2 peaks

    // Search for peaks
    Int_t nfound = s->Search(hist, 1, "new"); // Sigma=1, use new background estimation
    printf("Found %d candidate peaks\n", nfound);

    // Get peak positions
    Double_t *xpeaks = s->GetPositionX();
    for (Int_t i = 0; i < nfound; i++) {
        printf("Peak %d: %.2f\n", i+1, xpeaks[i]);
    }

    c1->Update();
    */
}