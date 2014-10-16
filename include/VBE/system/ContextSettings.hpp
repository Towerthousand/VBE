#ifndef STARTINGCONFIG_HPP
#define STARTINGCONFIG_HPP

class ContextSettings {
	public:
		enum ContextFlag {
			DebugContext = 0x01,
			ForwardCompatibleContext = 0x02,
			RobustAccessContext = 0x04,
			RobustIsolationContext = 0x08,
		};

		enum ProfileMask {
			CoreProfile = 0x01,
			CompatibilityProfile = 0x02,
			ESProfile = 0x04,
		};

		unsigned int major;
		unsigned int minor;
		unsigned int redBits;
		unsigned int greenBits;
		unsigned int blueBits;
		unsigned int alphaBits;
		unsigned int bufferBits;
		unsigned int depthBits;
		unsigned int stencilBits;
		unsigned int accumRedBits;
		unsigned int accumGreenBits;
		unsigned int accumBlueBits;
		unsigned int accumAlphaBits;
		unsigned int multisampleBuffers;
		unsigned int multisampleSamples;
		unsigned int contextFlags;
		ProfileMask profile;
		bool doubleBuffer;
		bool acceleratedGraphics;
		bool stereo;
		bool shareContext;
		bool requestSRGB;

		ContextSettings() :
#ifndef VBE_ES2
			major(4),
			minor(2),
#else
			major(2),
			minor(0),
#endif
			redBits(8),
			greenBits(8),
			blueBits(8),
			alphaBits(0),
			bufferBits(0),
			depthBits(16),
			stencilBits(0),
			accumRedBits(0),
			accumGreenBits(0),
			accumBlueBits(0),
			accumAlphaBits(0),
			multisampleBuffers(0),
			multisampleSamples(0),
			contextFlags(0),
#ifndef VBE_ES2
			profile(CoreProfile),
#else
			profile(ESProfile),
#endif
			doubleBuffer(true),
			acceleratedGraphics(true),
			stereo(false),
			shareContext(false),
			requestSRGB(false) {}
};

#endif // STARTINGCONFIG_HPP
