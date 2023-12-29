import pytest
import audio_processing

def test_stft():
    waveform = [0.1, 0.2, 0.3, 0.4, 0.5, 0.4, 0.3, 0.2, 0.1]
    n_fft = 4
    hop_length = 2
    win_length = 4

    cpp_magnitude, cpp_phase = audio_processing.compute_stft(waveform, n_fft, hop_length, win_length)

    # Perform STFT using PyTorch
    import torch
    torch_waveform = torch.tensor(waveform, dtype=torch.float32)
    torch_stft = torch.stft(torch_waveform, n_fft=n_fft, hop_length=hop_length, win_length=win_length, window=torch.hann_window(win_length))

    torch_magnitude = torch.abs(torch_stft)
    torch_phase = torch.angle(torch_stft)

    # Compare magnitude and phase
    assert torch.allclose(torch_magnitude.numpy(), cpp_magnitude)
    assert torch.allclose(torch_phase.numpy(), cpp_phase)

if __name__ == "__main__":
    pytest.main(["-v", __file__])

