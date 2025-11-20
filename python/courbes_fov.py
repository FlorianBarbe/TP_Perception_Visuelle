# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

# Paramètres de l'écran
L = 0.53   # largeur physique en mètres
Nx = 1920  # nombre de pixels horizontaux

# Intervalle de distances œil–écran
ds = np.linspace(0.3, 1.0, 200)

# Fonctions théoriques
FOVh = (180/np.pi) * 2 * np.arctan(L / (2*ds))
s_min = (L / (Nx * ds)) * (180/np.pi) * 60   # minutes d'arc

# Courbe FOVh(ds)
plt.figure()
plt.plot(ds, FOVh)
plt.xlabel("Distance œil–écran $d_s$ (m)")
plt.ylabel("Champ de vision horizontal $FOV_h$ (°)")
plt.title("Champ de vision horizontal en fonction de $d_s$")
plt.grid(True)

# Courbe s(ds)
plt.figure()
plt.plot(ds, s_min)
plt.xlabel("Distance œil–écran $d_s$ (m)")
plt.ylabel("Taille angulaire d’un pixel $s(d_s)$ (minutes d’arc)")
plt.title("Taille angulaire d’un pixel en fonction de $d_s$")
plt.grid(True)

plt.show()
