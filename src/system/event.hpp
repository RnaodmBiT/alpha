#pragma once
#include <functional>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>


typedef int EventID;


class IEvent {
public:
    virtual ~IEvent() { }
};


class EventQueue {
public:
    typedef std::function<void(IEvent*)> DelegateFunctor;

    template <typename Event, typename C>
    void Register(C* context, void (C::*method)(Event*)) {
        Delegate d;
        d.obj = context;
        d.fn = [context, method] (IEvent* e) { (*context.*method)((Event*)e); };
        callbacks[Event::GetID()].push_back(d);
    }

    template <typename Event, typename C>
    void Register(C* context, std::function<void(Event*)> callback) {
        Delegate d;
        d.obj = context;
        d.fn = [callback] (IEvent* e) { callback((Event*)e); };
        callbacks[Event::GetID()].push_back(d);
    }

    template <typename Event, typename C>
    void Unregister(C* context) {
        std::vector<Delegate>& delegates = callbacks[Event::GetID()];
        auto it = std::remove_if(delegates.begin(), delegates.end(), [&] (const Delegate& d) { return d.obj == context; });
        delegates.erase(it, delegates.end());
    }

    template <typename Event>
    void QueueEvent(Event* event) {
        events[Event::GetID()].emplace_back(event);
        delete event;
    }

    template <typename Event>
    void TriggerEvent(Event* event) {
        DispatchEvent(Event::GetID(), event);
    }

    void UpdateQueue() {
        for (auto& idQueue : events) {
            std::vector<std::unique_ptr<IEvent>> queue;
            std::swap(queue, idQueue.second);

            for (auto& e : queue) {
                DispatchEvent(idQueue.first, e.get());
            }
        }
    }


private:

    void DispatchEvent(EventID id, IEvent* event) {
        std::vector<Delegate>& delegates = callbacks[id];
        for (auto& delegate : delegates) {
            delegate.fn(event);
        }
    }

    struct Delegate {
        void* obj;
        DelegateFunctor fn;
    };

    std::map<EventID, std::vector<Delegate>> callbacks;
    std::map<EventID, std::vector<std::unique_ptr<IEvent>>> events;

};

