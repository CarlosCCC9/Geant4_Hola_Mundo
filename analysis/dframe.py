import numpy as np
import matplotlib.pyplot as plt
import ROOT

#Enable implicit multi-threading
ROOT.ROOT.EnableImplicitMT()

name = "output.root"

df_water = ROOT.RDataFrame("Block", name)
df_detec = ROOT.RDataFrame("Detector", name)


df_decay = df_water.Filter("fProc_Type==1")
#From the filtered dataframe store the values of fEvent in a numpy array
fEvent_values = df_decay.AsNumpy(columns=["fEvent"])["fEvent"]
s_event=set(fEvent_values)
#print(f"Number of decay events: {len(s_event)}")
#print(s_event)

evt=42

df_detec = df_detec.Filter(f"fEvent=={evt}")
#From the filtered dataframe store the values of fTime in a numpy array
fTime_values = df_detec.AsNumpy(columns=["fTime"])["fTime"]

print(f"Arrival times for event {evt}: {fTime_values}")

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