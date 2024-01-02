import pytest
import numpy as np
from stft_module import compute_stft

def test_stft_comparison():
    # Generate a simple waveform
    waveform = np.sin(2 * np.pi * 440.0 * np.arange(0, 1.0, 1.0 / 44100))

    # Parameters for STFT
    n_fft = 1024
    hop_length = 512
    win_length = 1024

    # Compute STFT using Python
    python_magnitude, python_phase = compute_stft(waveform, n_fft, hop_length, win_length)

    # Compute STFT using reference (NumPy)
    reference_stft = np.abs(np.fft.fft(np.lib.pad(waveform, (0, n_fft - len(waveform))), n_fft)[0:n_fft // 2 + 1])
    reference_magnitude = np.tile(reference_stft, (len(waveform) - win_length) // hop_length + 1)
    reference_phase = np.angle(np.fft.fft(np.lib.pad(waveform, (0, n_fft - len(waveform))), n_fft)[0:n_fft // 2 + 1])

    # Compare magnitudes
    np.testing.assert_allclose(python_magnitude, reference_magnitude, rtol=1e-5)

    # Compare phases
    np.testing.assert_allclose(python_phase, reference_phase, rtol=1e-5)

if __name__ == "__main__":
    pytest.main(["-v", "test_stft.py"])

