#include "SoundRecorder.hpp"
#include "AudioDevice.hpp"
#include "ALCheck.hpp"

namespace {
    ALCdevice* captureDevice = NULL;
}

SoundRecorder::SoundRecorder() :
m_thread            (&SoundRecorder::record, this),
m_sampleRate        (0),
m_processingInterval(0.100f),
m_isCapturing       (false) {
	ensureALInit();

    // Set the device name to the default device
    m_deviceName = getDefaultDevice();
}

SoundRecorder::~SoundRecorder() {
    // Nothing to do
}

bool SoundRecorder::start(unsigned int sampleRate) {
    // Check if the device can do audio capture
	if (!isAvailable()) {
		VBE_ASSERT(false, "Failed to start capture : your system cannot capture audio data (call SoundRecorder::isAvailable to check it)");
        return false;
    }

    // Check that another capture is not already running
	if (captureDevice) {
		VBE_ASSERT(!captureDevice, "Trying to start audio capture, but another capture is already running");
        return false;
    }

    // Open the capture device for capturing 16 bits mono samples
    captureDevice = alcCaptureOpenDevice(m_deviceName.c_str(), sampleRate, AL_FORMAT_MONO16, sampleRate);
	if (!captureDevice) {
		VBE_ASSERT(captureDevice, "Failed to open the audio capture device with the name: " << m_deviceName);
        return false;
    }

    // Clear the array of samples
    m_samples.clear();

    // Store the sample rate
    m_sampleRate = sampleRate;

    // Notify derived class
	if (onStart()) {
        // Start the capture
        alcCaptureStart(captureDevice);

        // Start the capture in a new thread, to avoid blocking the main thread
		m_isCapturing = false;
		if(m_thread.joinable()) m_thread.join();
        m_isCapturing = true;
		m_thread = std::thread(&SoundRecorder::record, this);

        return true;
    }

    return false;
}

void SoundRecorder::stop() {
    // Stop the capturing thread
	m_isCapturing = false;
	if(m_thread.joinable()) m_thread.join();

    // Notify derived class
    onStop();
}

unsigned int SoundRecorder::getSampleRate() const {
    return m_sampleRate;
}

std::vector<std::string> SoundRecorder::getAvailableDevices() {
    std::vector<std::string> deviceNameList;

    const ALchar *deviceList = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	if (deviceList) {
		while (*deviceList) {
            deviceNameList.push_back(deviceList);
            deviceList += std::strlen(deviceList) + 1;
        }
    }

    return deviceNameList;
}

std::string SoundRecorder::getDefaultDevice() {
    return alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
}

bool SoundRecorder::setDevice(const std::string& name) {
    // Store the device name
    if (name.empty())
        m_deviceName = getDefaultDevice();
    else
        m_deviceName = name;

	if (m_isCapturing) {
        // Stop the capturing thread
		m_isCapturing = false;
		if(m_thread.joinable()) m_thread.join();

        // Open the requested capture device for capturing 16 bits mono samples
        captureDevice = alcCaptureOpenDevice(name.c_str(), m_sampleRate, AL_FORMAT_MONO16, m_sampleRate);
		if (!captureDevice) {
            // Notify derived class
            onStop();

			VBE_ASSERT(captureDevice, "Failed to open the audio capture device with the name: " << m_deviceName);
            return false;
        }

        // Start the capture
        alcCaptureStart(captureDevice);

        // Start the capture in a new thread, to avoid blocking the main thread
        m_isCapturing = true;
		m_thread = std::thread(&SoundRecorder::record, this);
    }

    return true;
}

const std::string& SoundRecorder::getDevice() const {
    return m_deviceName;
}

bool SoundRecorder::isAvailable() {
	return (AudioDevice::isExtensionSupported("ALC_EXT_CAPTURE") != AL_FALSE) ||
		   (AudioDevice::isExtensionSupported("ALC_EXT_capture") != AL_FALSE); // "bug" in Mac OS X 10.5 and 10.6
}

void SoundRecorder::setProcessingInterval(float interval) {
    m_processingInterval = interval;
}

bool SoundRecorder::onStart() {
    // Nothing to do
    return true;
}

void SoundRecorder::onStop() {
    // Nothing to do
}

void SoundRecorder::record() {
	while (m_isCapturing) {
        // Process available samples
        processCapturedSamples();

        // Don't bother the CPU while waiting for more captured data
		SDL_Delay(m_processingInterval*1000);
    }

    // Capture is finished : clean up everything
    cleanup();
}

void SoundRecorder::processCapturedSamples() {
    // Get the number of samples available
    ALCint samplesAvailable;
    alcGetIntegerv(captureDevice, ALC_CAPTURE_SAMPLES, 1, &samplesAvailable);

	if (samplesAvailable > 0) {
        // Get the recorded samples
        m_samples.resize(samplesAvailable);
        alcCaptureSamples(captureDevice, &m_samples[0], samplesAvailable);

        // Forward them to the derived class
		if (!onProcessSamples(&m_samples[0], m_samples.size())) {
            // The user wants to stop the capture
            m_isCapturing = false;
        }
    }
}

void SoundRecorder::cleanup() {
    // Stop the capture
    alcCaptureStop(captureDevice);

    // Get the samples left in the buffer
    processCapturedSamples();

    // Close the device
    alcCaptureCloseDevice(captureDevice);
    captureDevice = NULL;
}
