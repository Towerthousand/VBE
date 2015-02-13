#ifndef TOUCH_HPP
#define TOUCH_HPP

#include <VBE/math.hpp>
#include <vector>

class InputImpl;

///
/// \brief The Touch class provides support to read multi-touch gestures
///
class Touch {
	public:
		///
		/// \brief The Finger class represents one of the user's fingers
		///
		class Finger {
			public:
				///
				/// \brief Returns the ID of this fingers
				///
				int getId() const;
				///
				/// \brief Returns whether this finger just made contact with the display
				///
				bool justPressed() const;
				///
				/// \brief Returns the current position of the finger in normalized (0..1) coordinates
				///
				vec2f position() const;
				///
				/// \brief Returns the current movement relative to the last frame
				///
				vec2f movement() const;

			private:
				int id;
				vec2f pos;
				vec2f oldPos;
				bool isNew;

				friend class Touch;
				friend class InputImpl;
		};
		///
		/// \class Finger Window.hpp <VBE/system/Touch.hpp>
		/// \ingroup System
		///
		/// Each user finger is kept track of since the moment of contact untill release, and it will
		/// maintain the same ID throughout the whole gesture.
		///
		/// \see Touch
		///

		///
		/// \brief Returns a vector reference that contains all the currently tracked fingers
		///
		static const std::vector<Finger>& getFingers();
};
/// \class Touch Touch.hpp <VBE/system/Touch.hpp>
/// \ingroup System
///
///  The total number of fingers is only limited by the actual device.
///

#endif
