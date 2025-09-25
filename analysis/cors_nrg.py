import numpy as np
import matplotlib.pyplot as plt
import ROOT

#Enable implicit multi-threading
ROOT.ROOT.EnableImplicitMT()

gamma_count=np.ones((1000,99))
gamma_errors=np.ones((1000,99))
bins_ed=np.logspace(0.5*np.log10(1e-1), np.log10(1e1), 100)

for i in range(1000):
    i = i + 1  # Adjusting index to match file naming convention
    p_dat=np.load(f"nrg/particles-{i:04d}.npy")
    p_arr=np.array(p_dat.tolist())
    p_arr = p_arr[p_arr[:, 0] == 13]
    
    hist, bin_edges = np.histogram(p_arr[:,5], bins=bins_ed)
    bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2
    bin_widths = np.diff(bin_edges)
    dNdE = hist / bin_widths  # [counts per GeV]
    errors = np.sqrt(hist) / bin_widths

    gamma_count[i-1,:]=dNdE
    gamma_errors[i-1,:]=errors


gamma_mean=np.ones(99)
gamma_std=np.ones(99)
for i in range(99):
    gamma_mean[i] = gamma_count[:, i].mean()
    gamma_std[i] = gamma_errors[:, i].mean()


#plt.errorbar(bin_centers, gamma_mean, yerr=gamma_std, fmt='o', label='Mean Spectrum with Std Dev')
plt.step(bin_centers, gamma_mean, where='mid', label='Mean Spectrum', color='blue')
#plt.fill_between(bin_centers, gamma_mean - gamma_std, gamma_mean + gamma_std, color='blue', alpha=0.3, label='Standard Deviation')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Energy (GeV)')
plt.ylabel('dN/dE (counts per GeV)')
plt.title('Mean Energy Spectrum of Particles')
plt.legend()
plt.grid(True, which="both", ls="--", lw=0.5)
plt.savefig("nrg_spectrum.png", dpi=300)
plt.show()

#Save the bin centers, final_mean, and final_std to a file
with open("energy_distribution.txt", "w") as f:
    f.write("# Energy Distribution Data\n")
    f.write("# Bin Centers (GeV), Muon Mean, Muon Std\n")
    for center, mean, std in zip(bin_centers, gamma_mean, gamma_std):
        f.write(f"{center}, {mean}, {std}\n")