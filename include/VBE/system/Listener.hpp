#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <unordered_set>
#include <functional>
#include <algorithm>

class EmitterBase;
class Listener {
	public:
		virtual ~Listener();

	private:
		bool connect(EmitterBase* instance);
		bool disconnect(EmitterBase* instance);

		std::unordered_set<EmitterBase*> parents;
		friend class EmitterBase;
};

class EmitterBase {
	public:
		virtual ~EmitterBase();

		bool listen(Listener* instance);
		bool unlisten(Listener* instance);
		void disconnectAll();

	protected:
		std::unordered_set<Listener*> listeners;
};

template<typename T> class Emitter : public EmitterBase {
	public:
		void all(std::function<void(T&)> f) {
			for(auto it = listeners.begin(); it != listeners.end(); it++)
				f(*(T*)(*it));
		}
};

#endif // LISTENER_HPP
