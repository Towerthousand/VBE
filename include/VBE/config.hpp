
#if defined(ANDROID)
	#define VBE_GLES2
	#define VBE_SYSTEM_ANDROID
#else
	#define VBE_SYSTEM_SDL2
#endif

#if defined(WINDOWS)
	#define VBE_SYSTEM_WINDOWS
#else
	#define VBE_SYSTEM_UNIX
#endif


#define VBE_DEBUG

#if defined(NDEBUG)
	#undef VBE_DEBUG
#endif
#if defined(QT_NO_DEBUG)
	#undef VBE_DEBUG
#endif
