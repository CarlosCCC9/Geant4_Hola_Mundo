import numpy as np
import ROOT


name="analysis.root"

time_inter=np.arange(0,20000,2)
bin_div=len(time_inter)-1

df = ROOT.RDataFrame("DecayTime", name)

#get values of fCorrect into a numpy array
fCorrect_values = np.array(df.AsNumpy(columns=["fCorrect"])["fCorrect"])
#turn into a set to get unique values
unique_fCorrect = set(fCorrect_values)
l=len(unique_fCorrect)


with open("histogram_data.txt", "w") as f:
    for i in unique_fCorrect:
        df_temp = df.Filter(f"fCorrect=={i}").Histo1D(("hist", f"Decay Time fCorrect={i}", bin_div, 0, 20000), "fTime")
        hist_temp = df_temp.GetValue()
        for j in range(1, hist_temp.GetNbinsX()+1):
            f.write(f"{hist_temp.GetBinCenter(j):.3f} {int(hist_temp.GetBinContent(j))}\n")
        del df_temp
        del hist_temp




#df = df.Filter("fCorrect==1").Histo1D(("hist", "Decay Time", bin_div, 0, 20000), "fTime")


"""
#for each bin store in a txt file the bin center and the bin content
with open("histogram_data.txt", "w") as f:
    for i in range(1, df.GetNbinsX()+1):
        #format the bin center to have 3 decimal places
        #format the bin content to have no decimal places
        f.write(f"{df.GetBinCenter(i):.3f} {int(df.GetBinContent(i))}\n")
"""

#print the histogram the time interval and the number of counts
#hist = df.GetValue()
#print(f"Time interval: {hist.GetXaxis().GetXmin()} - {hist.GetXaxis().GetXmax()}")
#print(f"Number of counts: {hist.GetEntries()}")











"""
#read a txt file
name = "time_differences.txt"
data = np.loadtxt(name)

#make a histogram of the data
hist, bins = np.histogram(data, bins=500, range=(0, 5000))
#make a ROOT histogram
h = ROOT.TH1D("h", "Time Differences; Time (ns); Counts", 500, 0, 5000)
#fill the histogram
for i in range(len(hist)):
    h.SetBinContent(i+1, hist[i])
#draw the histogram
c1 = ROOT.TCanvas("c1", "Time Differences", 800, 600)
h.Draw()
c1.Update()
"""