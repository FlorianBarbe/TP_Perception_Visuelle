import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Limite de fusion (en degrés)
FUSION_LIMIT = 1.5

# Axes
z = np.linspace(0.2, 5.0, 250)        # distance (m)
e = np.linspace(0.04, 0.08, 250)      # écart interoculaire (m)

Z, E = np.meshgrid(z, e)

# Disparité (°)
D_rad = 2 * np.arctan(E / (2 * Z))
D_deg = np.degrees(D_rad)

# Masques
fusion_mask = D_deg < FUSION_LIMIT
nonfusion_mask = D_deg >= FUSION_LIMIT

fig = plt.figure(figsize=(12, 7))
ax = fig.add_subplot(111, projection="3d")

# -------------------------------
# SURFACE ZONE DE NON-FUSION (ROUGE)
# -------------------------------
nonfusion = np.where(nonfusion_mask, D_deg, np.nan)
ax.plot_surface(
    Z, E*1000, nonfusion,
    cmap="Reds",
    alpha=0.7,
    edgecolor='none'
)

# -------------------------------
# SURFACE ZONE DE FUSION (VERT)
# -------------------------------
fusion = np.where(fusion_mask, D_deg, np.nan)
ax.plot_surface(
    Z, E*1000, fusion,
    cmap="Greens",
    alpha=0.8,
    edgecolor='none'
)

# -------------------------------
# PLAN LIMITE (1.5°)
# -------------------------------
limit_plane = np.ones_like(Z) * FUSION_LIMIT
ax.plot_surface(
    Z, E*1000, limit_plane,
    color='purple',
    alpha=0.25,
    edgecolor='none'
)

# Axes
ax.set_xlabel("Distance z (m)", labelpad=15)
ax.set_ylabel("Écart interoculaire e (mm)", labelpad=15)
ax.set_zlabel("Disparité (°)", labelpad=12)
ax.set_title("Zone de fusion stéréoscopique en fonction de z et e")

# Légende manuelle
from matplotlib.patches import Patch
legend_elements = [
    Patch(facecolor="green", edgecolor="black", alpha=0.6, label="Fusion possible"),
    Patch(facecolor="red", edgecolor="black", alpha=0.6, label="Pas de fusion"),
    Patch(facecolor="purple", edgecolor="black", alpha=0.3, label="Limite 1.5°"),
]
ax.legend(handles=legend_elements, loc="upper right")

plt.tight_layout()
plt.show()
