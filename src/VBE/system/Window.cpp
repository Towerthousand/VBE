#include<VBE/system/Window.hpp>
#include<VBE/system/WindowImpl.hpp>
#include<VBE/system/InputImpl.hpp>
#include<VBE/system/Log.hpp>
#include<VBE/system/Keyboard.hpp>
#include<VBE/system/Mouse.hpp>

// static
std::vector<Window::DisplayMode> Window::getFullscreenModes() {
    return WindowImpl::getFullscreenModes();
}

Window::Window(Window::DisplayMode mode, ContextSettings contextSettings) {
    VBE_ASSERT(instance == nullptr, "Only one Window can exist at a time");

    instance = this;
    WindowImpl::create(mode, contextSettings);

    Keyboard::init();
    Mouse::init();
    Gamepad::init();
}

Window::~Window() {
    VBE_ASSERT(instance == this, "wtf");

    instance = nullptr;
    WindowImpl::destroy();
}

void Window::update() {
    // We first save the last frame's input
    Keyboard::update();
    Mouse::update();
    Gamepad::update();
    InputImpl::update();

    // Then we process the events.
    WindowImpl::update();
}

vec2ui Window::getSize() const {
    return WindowImpl::getSize();
}

void Window::setDisplayMode(DisplayMode mode) {
    WindowImpl::setDisplayMode(mode);
}

void Window::setVsync(VsyncMode mode) {
    WindowImpl::setVsync(mode);
}

std::string Window::getTitle() const {
    return title;
}

void Window::setTitle(std::string newTitle) {
    title = newTitle;
    WindowImpl::setTitle(title);
}

bool Window::isFocused() const {
    return WindowImpl::isFocused();
}

bool Window::isClosing() const {
    return WindowImpl::isClosing();
}

void Window::setClosing(bool newClosing) {
    WindowImpl::setClosing(newClosing);
}

void Window::setPosition(unsigned int x, unsigned int y) {
    WindowImpl::setPosition(x, y);
}

void Window::swapBuffers() const {
    WindowImpl::swapBuffers();
}

Window* Window::instance = nullptr;

// static
Window* Window::getInstance() {
    return instance;
}

