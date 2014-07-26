#include "Sound.hpp"
#include "SoundBuffer.hpp"
#include "ALCheck.hpp"

Sound::Sound() :
	m_buffer(NULL) {
}

Sound::Sound(const SoundBuffer& buffer) :
	m_buffer(NULL) {
	setBuffer(buffer);
}

Sound::Sound(const Sound& copy) :
	SoundSource(copy),
	m_buffer   (NULL) {
	if (copy.m_buffer)
		setBuffer(*copy.m_buffer);
	setLoop(copy.getLoop());
}

Sound::~Sound() {
	stop();
	if (m_buffer)
		m_buffer->detachSound(this);
}

void Sound::play() {
	alCheck(alSourcePlay(m_source));
}

void Sound::pause() {
	alCheck(alSourcePause(m_source));
}

void Sound::stop() {
	alCheck(alSourceStop(m_source));
}

void Sound::setBuffer(const SoundBuffer& buffer) {
	// First detach from the previous buffer
	if (m_buffer) {
		stop();
		m_buffer->detachSound(this);
	}

	// Assign and use the new buffer
	m_buffer = &buffer;
	m_buffer->attachSound(this);
	alCheck(alSourcei(m_source, AL_BUFFER, m_buffer->m_buffer));
}

void Sound::setLoop(bool loop) {
	alCheck(alSourcei(m_source, AL_LOOPING, loop));
}

void Sound::setPlayingOffset(float timeOffset) {
	alCheck(alSourcef(m_source, AL_SEC_OFFSET, timeOffset));
}

const SoundBuffer* Sound::getBuffer() const {
	return m_buffer;
}

bool Sound::getLoop() const {
	ALint loop;
	alCheck(alGetSourcei(m_source, AL_LOOPING, &loop));

	return loop != 0;
}

float Sound::getPlayingOffset() const {
	ALfloat secs = 0.f;
	alCheck(alGetSourcef(m_source, AL_SEC_OFFSET, &secs));

	return secs;
}

Sound::Status Sound::getStatus() const {
	return SoundSource::getStatus();
}

Sound& Sound::operator =(const Sound& right) {
	// Here we don't use the copy-and-swap idiom, because it would mess up
	// the list of sound instances contained in the buffers

	// Detach the sound instance from the previous buffer (if any)
	if (m_buffer) {
		stop();
		m_buffer->detachSound(this);
		m_buffer = NULL;
	}

	// Copy the sound attributes
	if (right.m_buffer)
		setBuffer(*right.m_buffer);
	setLoop(right.getLoop());
	setPitch(right.getPitch());
	setVolume(right.getVolume());
	setPosition(right.getPosition());
	setRelativeToListener(right.isRelativeToListener());
	setMinDistance(right.getMinDistance());
	setAttenuation(right.getAttenuation());

	return *this;
}

void Sound::resetBuffer() {
	// First stop the sound in case it is playing
	stop();

	// Detach the buffer
	if (m_buffer) {
		alCheck(alSourcei(m_source, AL_BUFFER, 0));
		m_buffer->detachSound(this);
		m_buffer = NULL;
	}
}
