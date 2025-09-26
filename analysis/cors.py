import numpy as np

eas=np.load("particles-0001.npy")

print(eas.shape)
print(eas[10])

for i in eas:
    if i[0]!=22 and i[0]!=13 and i[0]!=11:
        print(i)
