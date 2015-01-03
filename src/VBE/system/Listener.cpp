#include <VBE/system/Listener.hpp>

Listener::~Listener() {
	while(!parents.empty())
		(*parents.begin())->unlisten(this);
}

bool Listener::connect(EmitterBase *instance) {
	return parents.insert(instance).second;
}

bool Listener::disconnect(EmitterBase *instance) {
	return parents.erase(instance) > 0;
}

EmitterBase::~EmitterBase() {
	disconnectAll();
}

bool EmitterBase::listen(Listener *instance) {
	auto ins = listeners.insert(instance);
	bool lis = instance->connect(this);
	return ins.second && lis;
}

bool EmitterBase::unlisten(Listener *instance) {
	std::size_t val = listeners.erase(instance);
	if (val > 0)
		return instance->disconnect(this);

	return false;
}

void EmitterBase::disconnectAll() {
	while(!listeners.empty()) {
		(*listeners.begin())->disconnect(this);
		listeners.erase(listeners.begin());
	}
}
