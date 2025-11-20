import numpy as np
import matplotlib.pyplot as plt

# Paramètres écran
L = 0.53          # largeur écran (m)
Nx = 1920         # résolution horizontale
p = L / Nx        # pitch pixel (m)
ds = 0.65         # distance oeil-écran (m)

# Parallaxe (pixels)
nx = np.arange(0, 51)

# Disparité
delta_deg = (nx * p / ds) * (180 / np.pi)

plt.figure(figsize=(8,5))
plt.plot(nx, delta_deg, linewidth=2, label=r"Disparité $\delta_x$")

# Seuil 1.5°
plt.axhline(1.5, color='red', linestyle='--', label=r"Seuil $1.5^\circ$")

plt.xlabel(r"Parallaxe $n_x$ (pixels)")
plt.ylabel(r"Disparité $\delta_x$ (°)")
plt.title("Disparité angulaire en fonction de la parallaxe")
plt.grid(True)
plt.legend()
plt.show()
