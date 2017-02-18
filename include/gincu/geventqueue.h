#ifndef GEVENTQUEUE_H
#define GEVENTQUEUE_H

#include "gincu/gevent.h"

#include "cpgf/gcallback.h"
#include "cpgf/gcallbacklist.h"

#include <deque>
#include <map>
#include <mutex>

namespace gincu {

class GEventQueue
{
public:
	typedef cpgf::GCallback<void (const GEvent &)> EventListener;
	typedef cpgf::GCallbackList<void (const GEvent &)> EventListenerList;

	typedef std::recursive_mutex MutexType;
	typedef std::lock_guard<MutexType> LockType;

private:
	struct TaggedListener
	{
		EventListener listener;
		GEvent::TagType tag;
	};

	struct ListenerItem
	{
		EventListenerList nonTagListenerList;
		std::deque<TaggedListener> taggedListenerList;
	};

public:
	static void dispatchAll();

public:
	GEventQueue();
	~GEventQueue();

	void addListener(const GEventType type, const EventListener & listener, const GEvent::TagType tag = nullptr);
	// add a "catch all" listener
	void addListener(const EventListener & listener, const GEvent::TagType tag = nullptr);

	void removeListener(const GEventType type, const EventListener & listener, const GEvent::TagType tag = nullptr);
	void removeListener(const EventListener & listener, const GEvent::TagType tag = nullptr);

	void send(const GEvent & event);
	void post(const GEvent & event);

	void dispatch();

private:
	void doDispatch();
	void doDispatchEvent(const GEvent & event);
	void doDispatchEventByType(const GEvent & event, const GEventType type);

	void doRemoveFromTaggedList(std::deque<TaggedListener> * taggedList, const EventListener & listener, const GEvent::TagType tag);
	void doRemoveFromTaggedList(std::deque<TaggedListener> * taggedList, const EventListener & listener);

private:
	MutexType eventMutex;
	std::deque<GEvent> eventQueue;
	MutexType listenerMutex;
	std::map<GEventType, ListenerItem> listenerMap;

private:
	static std::deque<GEventQueue *> eventQueueList;
	static MutexType eventQueueListMutex;
};


} //namespace gincu


#endif
