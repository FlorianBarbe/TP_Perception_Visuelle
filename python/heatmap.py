import numpy as np
import matplotlib.pyplot as plt

z = np.linspace(0.2, 5.0, 400)
e = np.linspace(0.04, 0.08, 400)
Z, E = np.meshgrid(z, e)

D = np.degrees(2 * np.arctan(E / (2 * Z)))

plt.figure(figsize=(8,6))
heat = plt.imshow(D, extent=[0.2,5,40,80], aspect='auto',
                  origin='lower', cmap='turbo')
plt.colorbar(label="Disparité (°)")
plt.contour(Z, E*1000, D, levels=[1.5], colors='white', linewidths=2)

plt.xlabel("Distance z (m)")
plt.ylabel("Écart interoculaire e (mm)")
plt.title("Heatmap de la disparité avec frontière de fusion (1.5°)")
plt.show()
