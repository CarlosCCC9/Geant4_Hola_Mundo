import numpy as np
import matplotlib.pyplot as plt

"""
name="eas/particle-0001.npy"
data = np.load(name)

arr=np.array(data.tolist())
#Solo muones
muons = arr[(arr[:, 0] == 13) | (arr[:, 0] == -13)]
elec=arr[(arr[:, 0] == 11) | (arr[:, 0] == -11)]

m1_time=muons[0][1]
m1_x=muons[0][2]
m1_y=muons[0][3]

#electrons in time and space window
#inter_part=elec[(elec[:, 1] < m1_time + 3000)]  #& (elec[:, 2] < m1_x + 0.8) & (elec[:, 2] > m1_x - 0.8) & (elec[:, 3] < m1_y + 0.8) & (elec[:, 3] > m1_y - 0.8)]
#print(len(inter_part))
"""

time,nrg=[],[]

for i in range(1000):
    i = i + 1
    p_dat=np.load(f"eas/particle-{i:04d}.npy")
    p_arr=np.array(p_dat.tolist())
    #Solo muones
    muons = p_arr[(p_arr[:, 0] == 13) | (p_arr[:, 0] == -13)]
    elec = p_arr[(p_arr[:, 0] == 11) | (p_arr[:, 0] == -11)]
    #loop over muons
    for j in muons:
        m_time=j[1]
        m_x=j[2]
        m_y=j[3]
        inter_part = elec[(elec[:, 1] > m_time) & (elec[:, 1] < m_time + 3000) & (elec[:, 2] < m_x + 0.8) & (elec[:, 2] > m_x - 0.8) & (elec[:, 3] < m_y + 0.8) & (elec[:, 3] > m_y - 0.8)]
        if(len(inter_part)>0):
            for k in inter_part:
                #print(m_time, k[1], k[1]-m_time)
                time.append(k[1]-m_time)
                nrg.append(k[5])
            #print(inter_part)
            #print("----")
    #print()

time=np.array(time)
nrg=np.array(nrg)

time_bins = np.linspace(0, 3000, 61)  # 60 bins from 0 to 3000 ns
nrg_bins = np.logspace(np.log10(1e-3), np.log10(1e1), 100)

time_hist, time_bin_edges = np.histogram(time, bins=time_bins)
nrg_hist, nrg_bin_edges = np.histogram(nrg, bins=nrg_bins)


plt.plot(time_bin_edges[:-1], time_hist, drawstyle='steps-mid')
plt.yscale('log')
plt.xlabel('Time (ns)')
plt.ylabel('Counts')
plt.title('Time Distribution of Electrons near Muons')
plt.grid(True, which="both", ls="--", lw=0.5)
plt.show()

plt.plot(nrg_bin_edges[:-1], nrg_hist, drawstyle='steps-mid')
plt.yscale('log')
plt.xlabel('Energy (GeV)')
plt.ylabel('Counts')
plt.title('Energy Distribution of Electrons near Muons')
plt.grid(True, which="both", ls="--", lw=0.5)
plt.show()


"""
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.imshow(time_hist[None, :], aspect='auto', cmap='Blues', extent=[time_bin_edges[0], time_bin_edges[-1], 0, 1])
plt.colorbar(label='Counts')
plt.xlabel('Time (ns)')
plt.ylabel('Events')
plt.title('Time Distribution')

plt.subplot(1, 2, 2)
plt.imshow(nrg_hist[None, :], aspect='auto', cmap='Blues', extent=[nrg_bin_edges[0], nrg_bin_edges[-1], 0, 1])
plt.colorbar(label='Counts')
plt.xlabel('Energy (GeV)')
plt.ylabel('Events')
plt.title('Energy Distribution')

plt.tight_layout()
plt.show()
"""