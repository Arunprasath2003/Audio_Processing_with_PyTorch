#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
#include <complex>
#include <fftw3.h>

namespace py = pybind11;

class AudioProcessing {
public:

    // Function to compute STFT and return magnitude and phase
    std::pair<std::vector<float>, std::vector<float>> stft(const std::vector<float>& waveform, int n_fft, int hop_length, int win_length) {
        int signal_size = waveform.size();
        int num_frames = (signal_size - win_length) / hop_length + 1;

        std::vector<float> magnitude(num_frames * (n_fft / 2 + 1));
        std::vector<float> phase(num_frames * (n_fft / 2 + 1));

        fftwf_complex* fft_input = fftwf_alloc_complex(n_fft);
        fftwf_complex* fft_output = fftwf_alloc_complex(n_fft);
        fftwf_plan plan_forward = fftwf_plan_dft_1d(n_fft, fft_input, fft_output, FFTW_FORWARD, FFTW_ESTIMATE);

        // Perform STFT
        for (int i = 0; i < num_frames; ++i) {
            int start = i * hop_length;
            int end = start + win_length;

            // Copy frame to fft_input
            for (int j = start, k = 0; j < end; ++j, ++k) {
                fft_input[k][0] = waveform[j];
                fft_input[k][1] = 0.0;
            }

            // Perform FFT
            fftwf_execute(plan_forward);

            // Compute magnitude and phase
            for (int j = 0, k = i * (n_fft / 2 + 1); j < n_fft / 2 + 1; ++j, ++k) {
                magnitude[k] = std::abs(std::complex<float>(fft_output[j][0], fft_output[j][1]));
                phase[k] = std::arg(std::complex<float>(fft_output[j][0], fft_output[j][1]));
            }
        }

        fftwf_destroy_plan(plan_forward);
        fftwf_free(fft_input);
        fftwf_free(fft_output);

        return {magnitude, phase};
    }

    // Binding function for Pybind
    py::tuple compute_stft(py::array_t<float> waveform, int n_fft, int hop_length, int win_length) {
        // Ensure that the input array is contiguous
        waveform = waveform.ensure();

        // Get pointers to the data
        float* waveform_ptr = static_cast<float*>(waveform.request().ptr);

        // Call the STFT function
        auto result = stft(std::vector<float>(waveform_ptr, waveform_ptr + waveform.size()), n_fft, hop_length, win_length);

        // Convert results to Python objects
        auto magnitude_array = py::array_t<float>(result.first.size(), result.first.data());
        auto phase_array = py::array_t<float>(result.second.size(), result.second.data());

        return py::make_tuple(magnitude_array, phase_array);
    }
};

// Define the module
PYBIND11_MODULE(audio_processing, m) {
    m.doc() = "audio_processing_module";

    // Create an instance of the AudioProcessing class and bind its methods
    py::class_<AudioProcessing>(m, "AudioProcessing")
        .def(py::init<>())
        .def("compute_stft", &AudioProcessing::compute_stft, "Compute STFT and return magnitude and phase");
}

