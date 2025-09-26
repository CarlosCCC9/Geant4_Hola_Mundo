#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1I.h>
#include <TCanvas.h>

void analysis(){

    TFile *file = new TFile("output.root", "READ");
    //print contents
    //file->ls();

    TTree *tree = (TTree*)file->Get("Water");
    //print contents
    //tree->Print();

    TBranch *branch = tree->GetBranch("fProc_Type");
    TBranch *branch2 = tree->GetBranch("fEvent");

    int fProc_Type;
    int evt;
    branch->SetAddress(&fProc_Type);
    branch2->SetAddress(&evt);
    Long64_t nentries = branch->GetEntries();

    //empty vector to store values
    std::vector<int> fProc_Type_values;
    std::vector<int> fEvent_values;

    for(int i=0; i<nentries; i++){
        branch->GetEntry(i);
        branch2->GetEntry(i);

        if (fProc_Type == 1){
            //fProc_Type_values.push_back(fProc_Type);
            fEvent_values.push_back(evt);
        }
        //std::cout << fProc_Type << std::endl;
    }

    //print size of vector
    std::cout << "Number of decay events: " << fEvent_values.size() << std::endl;
    //print unique values in vector
    std::set<int> s_event(fEvent_values.begin(), fEvent_values.end());
    std::cout << "Number of unique decay events: " << s_event.size() << std::endl;
    //print values in vector
    //for(auto i : s_event) std::cout << i << " ";
    //for (auto i : fEvent_values) std::cout << i << " ";

    TTree *tree2 = (TTree*)file->Get("Detector");
    TBranch *det_evt = tree2->GetBranch("fEvent");
    TBranch *det_time = tree2->GetBranch("fTime");

    int det_evt_value;
    double det_time_value;
    int det_correct_value=-1;

    det_evt->SetAddress(&det_evt_value);
    det_time->SetAddress(&det_time_value);
    Long64_t nentries2 = det_evt->GetEntries();

    //new root file
    TFile *file2 = new TFile("analysis.root", "RECREATE");
    TTree *tree3 = new TTree("DecayTime", "DecayTime");
    tree3->Branch("fEvent", &det_evt_value, "fEvent/I");
    tree3->Branch("fCorrect", &det_correct_value, "fCorrect/I");
    tree3->Branch("fTime", &det_time_value, "fTime/D");

    int temp = -1;
    for(int i=0; i<nentries2; i++){
        det_evt->GetEntry(i);
        det_time->GetEntry(i);

        //cout<<"Event: "<<det_evt_value<<" Corrected Event: "<<det_correct_value<<" Time: "<<det_time_value<<endl;

        if (s_event.find(det_evt_value) != s_event.end()){
            if(det_evt_value != temp){
            det_correct_value++;
            temp = det_evt_value;
            }
            tree3->Fill();
        }
    }

    cout<<"Number of unique decay events in detector: "<<det_correct_value<<endl;

    file2->Write();
    file2->Close();
    file->Close();


    /*
    TFile *f = new TFile("analysis.root");
    TTree *t = (TTree*)f->Get("DecayTime");
    TBranch *b1 = t->GetBranch("fEvent");

    int event;
    b1->SetAddress(&event);
    Long64_t n = b1->GetEntries();

    int count = 0;
    int temp = -1;
    for(int i=0; i<n; i++){
        b1->GetEntry(i);
        //cout<<event<<endl;
        //rename unique values in branch to 0,1,2,...

        if(event != temp){
            count++;
            temp = event;
        }
        //event = count;
        //t->GetEntry(i);
        //t->SetBranchAddress("fEvent", &event);
        //t->Fill();
    }

    //std::cout << "Number of unique decay events: " << count << std::endl;
*/




    /*
    int count = 0;
    for(int i=0; i<nentries2; i++){
        det_evt->GetEntry(i);
        det_time->GetEntry(i);
        if (s_event.find(det_evt_value) != s_event.end()){
            //Fill event branch wiht count value
            det_evt_value = count;
            tree3->Fill();
            count++;
        }

    }
    file2->Write();
    file2->Close();
    file->Close();
*/

}