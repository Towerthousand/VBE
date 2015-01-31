#ifndef TOUCH_HPP
#define TOUCH_HPP

#include <VBE/math.hpp>
#include <vector>

class InputImpl;

class Touch {
	public:
		class Finger {
			public:
				int getId() const;
				bool justPressed() const;
				vec2f position() const;
				vec2f movement() const;

			private:
				int id;
				vec2f pos;
				vec2f oldPos;
				bool isNew;

				friend class Touch;
				friend class InputImpl;
		};

		static const std::vector<Finger>& getFingers();
};

#endif
