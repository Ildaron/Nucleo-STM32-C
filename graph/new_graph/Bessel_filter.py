# https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.bessel.html

from scipy import signal
import matplotlib.pyplot as plt
import numpy as np
5
b, a = signal.butter(4, 100, 'low', analog=True)
w, h = signal.freqs(b, a)
plt.semilogx(w, 20 * np.log10(np.abs(h)), color='silver', ls='dashed')
b, a = signal.bessel(4, 100, 'low', analog=True, norm='phase')
w, h = signal.freqs(b, a)
plt.semilogx(w, 20 * np.log10(np.abs(h)))
plt.title('Bessel filter magnitude response (with Butterworth)')
plt.xlabel('Frequency [radians / second]')
plt.ylabel('Amplitude [dB]')
plt.margins(0, 0.1)
plt.grid(which='both', axis='both')
plt.axvline(100, color='green')  # cutoff frequency
plt.show()
