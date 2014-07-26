#ifndef SOUND_HPP
#define SOUND_HPP
#include "SoundSource.hpp"

class SoundBuffer;

class Sound : public SoundSource {
public :
    Sound();
    explicit Sound(const SoundBuffer& buffer);
    Sound(const Sound& copy);
    ~Sound();

    void play();
    void pause();
    void stop();
    void setBuffer(const SoundBuffer& buffer);
    void setLoop(bool loop);
	void setPlayingOffset(float timeOffset);
    const SoundBuffer* getBuffer() const;
    bool getLoop() const;
    float getPlayingOffset() const;
    Status getStatus() const;
    Sound& operator =(const Sound& right);
    void resetBuffer();

private :
    const SoundBuffer* m_buffer; ///< Sound buffer bound to the source
};

#endif // SOUND_HPP
