import numpy as np
import matplotlib.pyplot as plt
import ROOT

#Enable implicit multi-threading
ROOT.ROOT.EnableImplicitMT()

name = "analysis.root"

df_decay = ROOT.RDataFrame("DecayTime", name)


c1=ROOT.TCanvas()
hist=df_decay.Filter("fCorrect==0").Histo1D(("hist", "Decay Time", 30, 0, 20000), "fTime")
hist.SetTitle("Decay time; Time (ns); Counts")
hist.SetStats(0)
hist.Draw("HIST")
c1.SetLogz()
c1.Update()



"""
#open an empty root file to store the histograms
output_file = ROOT.TFile("histograms.root", "RECREATE")
#Add a branch called Id to the file and another called fTime
output_file.mkdir("DecayEvents")
output_file.cd("DecayEvents")
output_tree = ROOT.TTree("DecayTree", "DecayTree")
output_tree.Branch("Id", ROOT.std.vector("int")())
output_tree.Branch("fTime", ROOT.std.vector("float")())


c=0
for i in s_event:
    df_evt = df_detec.Filter(f"fEvent=={i}")
    fTime_values = df_evt.AsNumpy(columns=["fTime"])["fTime"]
    #store in the root file the event id and the fTime values
    Id = ROOT.std.vector("int")()
    fTime = ROOT.std.vector("float")()
    Id.push_back(c)
    for t in fTime_values:
        fTime.push_back(t)
    output_tree.Fill()
    c+=1

output_tree.Write()
output_file.Close()
"""


""""
evt=9

df_detec = df_detec.Filter(f"fEvent=={evt}")
#From the filtered dataframe store the values of fTime in a numpy array
fTime_values = df_detec.AsNumpy(columns=["fTime"])["fTime"]

l_evt=len(fTime_values)
#print(f"Number of photons detected in event {evt}: {l_evt}")
#print(fTime_values)
"""


"""
hist=np.histogram(fTime_values, bins=30, range=(0,20000))
plt.hist(fTime_values, bins=30, range=(0,20000))
plt.yscale("log")
plt.xlabel("Arrival Time (ns)")
plt.ylabel("Counts")
plt.title(f"Arrival Time for event {evt} with {l_evt} photons")
plt.grid()
plt.show()
"""




#print(f"Arrival times for event {evt}: {fTime_values}")


"""
c1=ROOT.TCanvas()
bins=10
hist = df_detec.Filter("fEvent==783").Histo1D(("hist", "Arrival Time", bins, 0, 3000), "fTime")
hist.SetTitle("Arrival time; Time (ns); Counts")
hist.SetStats(0)
hist.Draw("HIST")
c1.SetLogz()
c1.Update()
"""