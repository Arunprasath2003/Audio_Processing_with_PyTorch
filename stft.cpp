#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
#include <cmath>

namespace py = pybind11;

class STFTProcessor {
public:
    // Function to compute STFT and return magnitude and phase
    std::pair<std::vector<float>, std::vector<float>> stft(const std::vector<float>& input_waveform, int n_fft, int hop_length, int win_length) {
        int signal_size = input_waveform.size();
        int num_frames = (signal_size - win_length) / hop_length + 1;

        std::vector<float> waveform(input_waveform.begin(), input_waveform.end());  // Make a copy of input waveform

        std::vector<float> magnitude(num_frames * (n_fft / 2 + 1));
        std::vector<float> phase(num_frames * (n_fft / 2 + 1));

        for (int i = 0; i < num_frames; ++i) {
            int start = i * hop_length;
            int end = start + win_length;

            for (int j = start; j < end; ++j) {
                waveform[j] *= 0.5 * (1 - std::cos(2 * M_PI * (j - start) / (win_length - 1)));
            }

            // Perform FFT
            for (int k = 0; k <= n_fft / 2; ++k) {
                float real_part = 0.0;
                float imag_part = 0.0;

                for (int j = start; j < end; ++j) {
                    real_part += waveform[j] * std::cos(-2 * M_PI * k * (j - start) / n_fft);
                    imag_part += waveform[j] * std::sin(-2 * M_PI * k * (j - start) / n_fft);
                }

                magnitude[i * (n_fft / 2 + 1) + k] = std::sqrt(real_part * real_part + imag_part * imag_part);
                phase[i * (n_fft / 2 + 1) + k] = std::atan2(imag_part, real_part);
            }
        }

        return {magnitude, phase};
    }

    // Binding function for Pybind
    py::tuple compute_stft(py::array_t<float> input_waveform, int n_fft, int hop_length, int win_length) {
        // Get pointers to the data
        float* waveform_ptr = input_waveform.mutable_data();

        // Call the STFT function
        auto result = stft(std::vector<float>(waveform_ptr, waveform_ptr + input_waveform.size()), n_fft, hop_length, win_length);

        // Convert results to Python objects
        auto magnitude_array = py::array_t<float>(result.first.size(), result.first.data());
        auto phase_array = py::array_t<float>(result.second.size(), result.second.data());

        return py::make_tuple(magnitude_array, phase_array);
    }
};

// Main module definition
PYBIND11_MODULE(stft_module, m) {
    m.doc() = "STFT Module";

    // Bind class and methods to Python
    py::class_<STFTProcessor>(m, "STFTProcessor")
        .def(py::init<>())
        .def("compute_stft", &STFTProcessor::compute_stft, "Compute STFT and return magnitude and phase");
}

