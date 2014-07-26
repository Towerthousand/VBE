#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "tools.hpp"

class SoundSource {
	public :
		enum Status
		{
			Stopped,
			Paused,
			Playing
		};

		SoundSource(const SoundSource& copy);
		virtual ~SoundSource();

		void setPitch(float pitch);
		void setVolume(float volume);
		void setPosition(float x, float y, float z);
		void setPosition(const vec3f& position);
		void setRelativeToListener(bool relative);
		void setMinDistance(float distance);
		void setAttenuation(float attenuation);
		float getPitch() const;
		float getVolume() const;
		vec3f getPosition() const;
		bool isRelativeToListener() const;
		float getMinDistance() const;
		float getAttenuation() const;

	protected :
		SoundSource();
		Status getStatus() const;

		unsigned int m_source; // OpenAL source identifier
};

#endif // SOUNDSOURCE_HPP
