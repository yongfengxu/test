#ifndef Esc_H
#define Esc_H


#include <vector>
#include <iostream>
#include <inttypes.h>


namespace esc {


class Event;


class IEventReceiver {
public:
    virtual ~IEventReceiver() {}
    virtual void processEvent(Event& event) = 0;
};


class EventId {
public:
    EventId(uint64_t higher, uint64_t lower) : higher_(higher), lower_(lower) {}
    EventId(const EventId& other) : higher_(other.higher_), lower_(other.lower_) {}
    EventId& operator=(const EventId& other) { higher_ = other.higher_; lower_ = other.lower_; return *this; }
    bool operator==(const EventId& other) const { return higher_ == other.higher_ && lower_ == other.lower_; }
    bool operator<(const EventId& other) const
        { return higher_ < other.higher_ || (higher_ == other.higher_ && lower_ < other.lower_); }
    friend std::ostream& operator<<(std::ostream& os, const EventId& id);
private:
    uint64_t higher_, lower_;
};

inline std::ostream& operator<<(std::ostream& os, const EventId& id)
{
    os << id.higher_ << "," << id.lower_;
    return os;
}


class Event {
public:
    Event(EventId eventId, const std::string& name) : eventId_(eventId), enabled_(true), destination_(0), name_(name) {
    }
    virtual ~Event() {}

    const EventId& getId() const {
        return eventId_;
    }

    IEventReceiver* getDestination() const {
        return destination_;
    }

    void setDestination(IEventReceiver* destination) { 
        destination_ = destination;
    }

    bool isEnabled() const {
        return enabled_;
    }

    void setEnabled(bool enabled) {
        enabled_ = enabled;
    }

    const std::string& getName() const {
        return name_;
    }

private:
    EventId eventId_;
    bool enabled_;
    IEventReceiver* destination_;
    std::string name_;
};


enum Priority {
    LowPrio,
    MediumPrio,
    HighPrio
};


class ITimer {
public:
    virtual ~ITimer() {}
    virtual void cancel(bool doLog) = 0;
    virtual EventId getEventId() = 0;
};


class Sm : public IEventReceiver {
public:
    virtual void sendEvent(Event* event, Priority prio = MediumPrio) = 0;
    void asyncDestroy();

protected:
    Sm();
    virtual ~Sm();
    void startBehavior(); // Implementation in generated code
    void processEvent(Event& event);
    virtual bool handleEvent(Event& event) = 0; // Implementation in generated code
    virtual void handleNotConsumed(const Event& event);
    virtual const char* getSmName() const = 0;
    virtual const char* getTimerEventName(const EventId& eventId) const;
    std::string getEventName(const Event& event) const;
    virtual ITimer* createTimer(EventId timerEventId, int timeoutMs) = 0;
    void scheduleTimer(EventId timerEventId, int timeoutMs);
    void cancelTimer(EventId timerEventId, bool doLog=true);
    void cancelTimers();
    void pushNullTransition();
    void popNullTransition();
    void runToCompletion();
    void completeStartBehavior();
    void onTimer(EventId timerEventId);
    void setLoggingEnabled(bool loggingEnabled);
    virtual void log(const std::string& message) = 0;

private:
    void cancelTimer(int index, bool doLog);

    int nullTransitionCount_;
    bool toBeDeleted_;
    Event* eventBeingProcessed_;
    bool loggingEnabled_;
    std::vector<ITimer*> activeTimers_;

    static EventId nullEventId;
    static EventId completeStartBehaviorEventId;
    static EventId destroyEventId;
};


/* Used as a way of aborting ongoing event processing without touching
 * the state machine object anymore, after it has been destroyed */
class SmDestroyedException
{
};

}

#endif
