#include <VBE/system/Touch.hpp>
#include <VBE/system/InputImpl.hpp>

int Touch::Finger::getId() const {
    return id;
}

bool Touch::Finger::justPressed() const {
    return isNew;
}

vec2f Touch::Finger::position() const {
    return pos;
}

vec2f Touch::Finger::movement() const {
    return pos - oldPos;
}

// static
const std::vector<Touch::Finger>& Touch::getFingers() {
    return InputImpl::getFingers();
}
