# Modul za rad sa nizovima
import numpy as np

# Modul za lepe histograme
import seaborn as sns

# Modul za crtanje grafikona
import matplotlib.pyplot as plt

# Čitanje podataka o izvršavanju
with open('chart.txt') as f:
  linije = f.readlines()

# Izdvajanje linija sa vremenima
vremena = [np.log2(eval(linija))
           for linija in linije
           if linija.startswith('[')]

# Odabrani skup oznaka
oznake = 'Naive', 'PrefD', 'DC3', 'SA-IS'

# Odabrana paleta boja
boje = 'skyblue', 'green', 'orange', 'purple'

# Crtanje histograma vremena
for i in range(4):
  sns.histplot(vremena[i],
               element='step',
               label=oznake[i],
               color=boje[i],
               alpha=.5)

# Crtanje legende
plt.legend()

# Brisanje nevažne oznake sa y-ose
plt.ylabel('')

# Čuvanje kvalitetne slike
plt.savefig('histogram', dpi=150)
