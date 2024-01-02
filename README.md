**Python Code for Audio Processing:**
<br>
**Audio Processing Functions:**
<br>

1. Implemented functions in Python for audio processing, including loading and resampling audio, computing the Short-Time Fourier Transform (STFT), and computing the Inverse STFT (ISTFT).
2. The STFT is used to convert the audio signal from the time domain to the frequency domain, and ISTFT is used to reconstruct the audio signal from the frequency domain.
<br>

**STFT and ISTFT Functions:**
<br>

1. load_and_resample_audio: Loads an audio file and resamples it to a target sample rate using linear interpolation.
2. compute_stft: Computes the STFT of an audio waveform and returns magnitude and phase spectrograms.
3. compute_istft: Computes the ISTFT from magnitude and phase spectrograms, reconstructing the audio waveform.
<br>

**Testing and Visualization:**
<br>

1. Tested the functionality by loading an audio file, resampling it, computing the STFT, performing ISTFT, and visualizing the original and reconstructed audio waveforms.

<br>

**PyTorch Metrics Comparison:**
<br>

**PyTorch Metrics:**
<br>

1. Used PyTorch metrics library to compute the Perceptual Evaluation of Speech Quality (PESQ) and Short-Time Objective Intelligibility (STOI) scores for the original and reconstructed audio.
2. PESQ measures speech quality, and STOI measures intelligibility.

**Comparison and Results:**
<br>

1. Compared the original and reconstructed audio using PyTorch tensors, and printed PESQ and STOI scores.
<br>

**C++ Implementation with Pybind11:**
<br>

**C++ STFT Implementation:**
<br>

1. Implemented the STFT in C++ **without using third-party libraries**. The STFT function computes magnitude and phase components of the audio signal.
2. The code is **encapsulated in a class**, STFTProcessor.

**Pybind11 Integration:**
<br>

1. Used Pybind11 to create a Python module (stft_module) that exposes the STFT functionality from C++ to Python.

**Testing with Pytest:**
<br>

1. Wrote Pytest tests to compare the results of the C++ and Python implementations of STFT.
