#ifndef STARTINGCONFIG_HPP
#define STARTINGCONFIG_HPP

///
/// \brief The ContextSettings class contains all the settings for the OpenGL context creation used when creating a Window.
///
class ContextSettings {
    public:
        ///
        /// \brief The ContextFlag enum
        ///
        enum ContextFlag {
            DebugContext = 0x01, ///< Allows GPU debugging
            ForwardCompatibleContext = 0x02, ///< Disables all extensions marked as legacy (only relevant for OpenGL 3.0)
            RobustAccessContext = 0x04, ///< RobustAccess
            RobustIsolationContext = 0x08, ///< RobustIsolation
        };

        ///
        /// \brief The ProfileMask enum
        ///
        enum ProfileMask {
            CoreProfile = 0x01, ///< Only core functions for the specified version.
            CompatibilityProfile = 0x02, ///< Core + compatibility context (supports older API)
            ESProfile = 0x04, ///< For embedded systems
        };
        ///
        /// \brief The major version number of the desired OpenGL version. Defaults to 4 (2 on Android).
        ///
        unsigned int versionMajor;

        ///
        /// \brief The minor version number of the desired OpenGL version. Defaults to 2 (0 on Android).
        ///
        unsigned int versionMinor;

        ///
        /// \brief Number of bits on the red channel. Defaults to 8.
        ///
        unsigned int redBits;

        ///
        /// \brief Number of bits on the green channel. Defaults to 8.
        ///
        unsigned int greenBits;

        ///
        /// \brief Number of bits on the blue channel. Defaults to 8.
        ///
        unsigned int blueBits;

        ///
        /// \brief Number of bits on the alpha channel. Defaults to 8.
        ///
        unsigned int alphaBits;

        ///
        /// \brief Number of bits for the buffer. Defaults to 0.
        ///
        unsigned int bufferBits;

        ///
        /// \brief Number of bits for the depth texture. Defaults to 16.
        ///
        unsigned int depthBits;

        ///
        /// \brief Number of bits for the stencil texture. Defaults to 0.
        ///
        unsigned int stencilBits;

        ///
        /// \brief accumRedBits
        ///
        unsigned int accumRedBits;

        ///
        /// \brief accumGreenBits
        ///
        unsigned int accumGreenBits;

        ///
        /// \brief accumBlueBits
        ///
        unsigned int accumBlueBits;

        ///
        /// \brief accumAlphaBits
        ///
        unsigned int accumAlphaBits;

        ///
        /// \brief multisampleBuffers
        ///
        unsigned int multisampleBuffers;

        ///
        /// \brief multisampleSamples
        ///
        unsigned int multisampleSamples;

        ///
        /// \brief A combination of values from the ContextFlag enum. Defaults to 0. \see ContextFlag
        ///
        unsigned int contextFlags;
        ///
        /// \brief The the desired profile. Defaults to Core (ES on Android). \see ProfileMask.
        ///
        ProfileMask profile;

        ///
        /// \brief Wether to use double buffering. Defaults to true.
        ///
        bool doubleBuffer;

        ///
        /// \brief Wether to use hardware acceleration. Defaults to true.
        ///
        bool acceleratedGraphics;

        ///
        /// \brief Request support for stereo render. Defaults to false.
        ///
        bool stereo;

        ///
        /// \brief Request context sharing. Defaults to false.
        ///
        bool shareContext;

        ///
        /// \brief Request SRGB texture availability. Defaults to false.
        ///
        bool requestSRGB;

        ///
        /// \brief Default constructor.
        ///
        ContextSettings() :
    #ifndef VBE_ES2
            versionMajor(4),
            versionMinor(2),
    #else
            versionMajor(2),
            versionMinor(0),
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
///
/// \class ContextSettings ContextSettings.hpp <VBE/system/ContextSettings.hpp>
///	\ingroup System
///
/// Remember that, as a rule of thumb, you cannot expect everything you request in this settings
/// to be available everywhere. If the graphics card doesn't support the OpenGL version you request
/// (for example) it will quietly provide you an older version instead of directly crashing.
///
/// \see Window
///

#endif // STARTINGCONFIG_HPP
