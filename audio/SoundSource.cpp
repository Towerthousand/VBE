#include "SoundSource.hpp"
#include "ALCheck.hpp"

SoundSource::SoundSource() {
	ensureALInit();

    alCheck(alGenSources(1, &m_source));
    alCheck(alSourcei(m_source, AL_BUFFER, 0));
}

SoundSource::SoundSource(const SoundSource& copy) {
	ensureALInit();

    alCheck(alGenSources(1, &m_source));
    alCheck(alSourcei(m_source, AL_BUFFER, 0));

    setPitch(copy.getPitch());
    setVolume(copy.getVolume());
    setPosition(copy.getPosition());
    setRelativeToListener(copy.isRelativeToListener());
    setMinDistance(copy.getMinDistance());
    setAttenuation(copy.getAttenuation());
}

SoundSource::~SoundSource() {
    alCheck(alSourcei(m_source, AL_BUFFER, 0));
    alCheck(alDeleteSources(1, &m_source));
}

void SoundSource::setPitch(float pitch) {
    alCheck(alSourcef(m_source, AL_PITCH, pitch));
}

void SoundSource::setVolume(float volume) {
    alCheck(alSourcef(m_source, AL_GAIN, volume * 0.01f));
}

void SoundSource::setPosition(float x, float y, float z) {
    alCheck(alSource3f(m_source, AL_POSITION, x, y, z));
}

void SoundSource::setPosition(const vec3f& position) {
    setPosition(position.x, position.y, position.z);
}

void SoundSource::setRelativeToListener(bool relative) {
    alCheck(alSourcei(m_source, AL_SOURCE_RELATIVE, relative));
}

void SoundSource::setMinDistance(float distance) {
    alCheck(alSourcef(m_source, AL_REFERENCE_DISTANCE, distance));
}

void SoundSource::setAttenuation(float attenuation) {
    alCheck(alSourcef(m_source, AL_ROLLOFF_FACTOR, attenuation));
}

float SoundSource::getPitch() const {
    ALfloat pitch;
    alCheck(alGetSourcef(m_source, AL_PITCH, &pitch));

    return pitch;
}

float SoundSource::getVolume() const {
    ALfloat gain;
    alCheck(alGetSourcef(m_source, AL_GAIN, &gain));

    return gain * 100.f;
}

vec3f SoundSource::getPosition() const {
	vec3f position;
    alCheck(alGetSource3f(m_source, AL_POSITION, &position.x, &position.y, &position.z));

    return position;
}

bool SoundSource::isRelativeToListener() const {
    ALint relative;
    alCheck(alGetSourcei(m_source, AL_SOURCE_RELATIVE, &relative));

    return relative != 0;
}

float SoundSource::getMinDistance() const {
    ALfloat distance;
    alCheck(alGetSourcef(m_source, AL_REFERENCE_DISTANCE, &distance));

    return distance;
}

float SoundSource::getAttenuation() const {
    ALfloat attenuation;
    alCheck(alGetSourcef(m_source, AL_ROLLOFF_FACTOR, &attenuation));

    return attenuation;
}

SoundSource::Status SoundSource::getStatus() const {
    ALint status;
    alCheck(alGetSourcei(m_source, AL_SOURCE_STATE, &status));

	switch (status) {
        case AL_INITIAL :
        case AL_STOPPED : return Stopped;
        case AL_PAUSED :  return Paused;
        case AL_PLAYING : return Playing;
    }

    return Stopped;
}
