import numpy as np
import ROOT

name = "beam.root"

df=ROOT.RDataFrame("Block", name)

#placa 1
df_layer1 = df.Filter("fCopyNo==1")

#placa 4
df_layer4 = df.Filter("fCopyNo==2")

hist_1 = df_layer1.Histo1D(("hist", "Energia placa 1", 100, 0, 100), "fNrg")

hist_4 = df_layer4.Histo1D(("hist", "Energia placa 4", 100, 0, 100), "fNrg")



c1=ROOT.TCanvas()
hist_1.SetTitle("Energia placas 1 y 2; Counts")
hist_1.SetLineColor(ROOT.kRed)
hist_1.SetLineWidth(2)
hist_1.SetFillColor(ROOT.kRed)
hist_1.SetFillStyle(3001)
hist_1.Draw("HIST")
hist_4.SetLineColor(ROOT.kBlue)
hist_4.SetLineWidth(2)
hist_4.SetFillColor(ROOT.kBlue)
hist_4.SetFillStyle(3001)
hist_4.Draw("SAME")
c1.SetLogy()
c1.Update()
