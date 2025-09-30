import numpy as np
import matplotlib.pyplot as plt
import ROOT

#Enable implicit multi-threading
ROOT.ROOT.EnableImplicitMT()

name = "analysis.root"

df_decay = ROOT.RDataFrame("DecayTime", name)


for i in range(5):
    #df_dec = df_decay.Filter(f"fCorrect=={i}").Histo1D(("hist", "Decay Time", 30, 0, 20000), "fTime")
    df_dec=df_decay.Filter(f"fCorrect=={i}").Filter("fTime")

    #print(f"Number of events with fCorrect={i}: {df_dec.Count().GetValue()}")
    #from this histogram find if there are two local maxima
    #hist = df_dec.GetValue()
    #get the bin content as a numpy array
    #bin_content = np.array([hist.GetBinContent(j) for j in range(1, hist.GetNbinsX()+1)])
    #find the local maxima
    #local_maxima = (np.diff(np.sign(np.diff(bin_content))) < 0).nonzero()[0] + 1
    #print the local maxima
    #print(f"Local maxima for fCorrect={i}: {local_maxima}")
    #if there are two local maxima, plot the histogram
    #plot the histogram
    del df_dec

"""
c1=ROOT.TCanvas()
hist=df_decay.Filter("fCorrect==1").Histo1D(("hist", "Decay Time", 30, 0, 20000), "fTime")
hist.SetTitle("Decay time; Time (ns); Counts")
hist.SetStats(0)
hist.Draw("HIST")
c1.SetLogz()
c1.Update()
"""