import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

gamma_count=np.ones((1000,99))
gamma_errors=np.ones((1000,99))
bins_ed=np.logspace(0.5*np.log10(1e-1), np.log10(1e1), 100)


#Leer los arrays de cada chubasco
for i in range(1000):
    i = i + 1
    p_dat=np.load(f"eas/particle-{i:04d}.npy")
    p_arr=np.array(p_dat.tolist())
    #Solo muones
    #p_arr = p_arr[p_arr[:, 0] == 13]
    #Muones y antimuones
    p_arr = p_arr[(p_arr[:, 0] == 13) | (p_arr[:, 0] == -13)]
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
plt.step(bin_centers, gamma_mean, where='mid', label='Espectro medio', color='blue')
plt.fill_between(bin_centers, gamma_mean - gamma_std, gamma_mean + gamma_std, color='blue', alpha=0.3, label='Desviación Estandar')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Energia (GeV)')
plt.ylabel('dN/dE (conteos por GeV)')
plt.title('Espectro de energía media de los muones a 3650 msnm')
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

# Normalize to PDF
pdf = gamma_mean / np.sum(gamma_mean * bin_widths)

# Compute CDF
cdf = np.cumsum(pdf * bin_widths)
cdf /= cdf[-1]  # Normalize to 1

energy_sampler = interp1d(cdf, bin_centers, kind='linear', bounds_error=False, fill_value=(bin_centers[0], bin_centers[-1]))

# To sample energies:
random_uniforms = np.random.uniform(size=10000)
sampled_energies = energy_sampler(random_uniforms)

# from sampled energies, filter those between 0.01 and 1 GeV
filtered_energies = sampled_energies[(sampled_energies > 0.01) & (sampled_energies < 1.0)]

len_sampled = len(sampled_energies)
len_filtered = len(filtered_energies)
print(f"Total sampled energies: {len_sampled}")
print(f"Filtered energies (0.1-1 GeV): {len_filtered}")

np.savetxt("sampled_energies.dat", sampled_energies)
np.savetxt("filtered_energies.dat", filtered_energies)

#plot the sampled energies
plt.figure(figsize=(10, 6))
plt.hist(sampled_energies, bins=100, density=True, alpha=0.3, color='blue', label='Energías Muestreadas')
plt.hist(filtered_energies, bins=100, density=True, alpha=0.7, color='orange', label='Energías Filtradas (0.01-1 GeV)')
plt.xlabel('Energia (GeV)')
plt.ylabel('Densidad')
plt.title('Distribución de Energía Muestreada')
plt.xscale('log')
plt.yscale('log')
plt.grid(True)
plt.legend()
plt.show()
