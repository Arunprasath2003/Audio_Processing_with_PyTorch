**Audio Processing in Python:**
<br>

1. Loaded an audio file using torchaudio.
2. Resampled the audio to a target sample rate.
3. Computed the Short-Time Fourier Transform (STFT) and obtained magnitude and phase components.
3. Reconstructed the audio from magnitude and phase using Inverse STFT (ISTFT).
4. Compared the original and reconstructed audio waveforms.
5. Evaluated the audio using PESQ (Perceptual Evaluation of Speech Quality) and STOI (Short Time Objective Intelligibility) scores.
<br>

**PyTorch to C++ using Pybind11:**
<br>

1. Created a C++ application using Pybind11 for computing STFT and returning magnitude and phase.
2. Built the C++ module using CMake and integrated it with Python.
3. Wrote a Python script to test the C++ module and compared the results with PyTorch.
<br>

**Testing Audio Processing with Pytest:**
<br>

1. Imported the necessary libraries, including torchmetrics for audio quality metrics.
2. Implemented a Pytest script to test the STFT function, comparing the results from Python and C++.
<br>

**Class-based Modularization:**
<br>

1. Organized the Python audio processing code into classes and functions for better modularity and readability.
2. Added multiline comments before each function to explain their purpose and functionality.

**Summary of Classes and Functions:**
<br>

**AudioProcessor Class:**
<br>

1. load_and_resample_audio: Loads and resamples audio.
2. compute_stft: Computes STFT and returns magnitude and phase.
3. compute_istft: Computes ISTFT and reconstructs audio.
4. compare_audio: Compares original and reconstructed audio.
5. evaluate_audio: Evaluates audio using PESQ and STOI.

**CppAudioProcessor Class:**
<br>

1. compute_stft: Computes STFT in C++ using Pybind11.
<br>
**AudioTest Class:**
<br>
1. test_stft: Pytest script to test STFT function.
