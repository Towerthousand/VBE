#include "SoundBufferRecorder.hpp"
#include <algorithm>
#include <iterator>


bool SoundBufferRecorder::onStart()
{
    m_samples.clear();
    m_buffer = SoundBuffer();

    return true;
}



bool SoundBufferRecorder::onProcessSamples(const short* samples, std::size_t sampleCount)
{
    std::copy(samples, samples + sampleCount, std::back_inserter(m_samples));

    return true;
}



void SoundBufferRecorder::onStop()
{
    if (!m_samples.empty())
        m_buffer.loadFromSamples(&m_samples[0], m_samples.size(), 1, getSampleRate());
}



const SoundBuffer& SoundBufferRecorder::getBuffer() const
{
    return m_buffer;
}
