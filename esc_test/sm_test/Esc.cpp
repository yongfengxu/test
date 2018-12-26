#include "Esc.h"
#include <sstream>


namespace esc
{


EventId  Sm::nullEventId                  = EventId(0, 0);
EventId  Sm::completeStartBehaviorEventId = EventId(0, 1);
EventId  Sm::destroyEventId               = EventId(0, 2);


#define LOG(msg) \
    do { \
        if (__builtin_expect(loggingEnabled_, 0)) { \
            std::stringstream ss; \
            ss << __FUNCTION__ << ": " << msg; \
            log(ss.str()); \
        } \
    } while (0)


Sm::Sm()
    : nullTransitionCount_(0), toBeDeleted_(false), eventBeingProcessed_(0), loggingEnabled_(false)
{
}

Sm::~Sm()
{
    cancelTimers();
    if (eventBeingProcessed_)
    {
        eventBeingProcessed_->setEnabled(false);
    }
}

void Sm::processEvent(Event& event)
{
    void* thisPtr = this;
    LOG("[" << getSmName() << "(" << thisPtr << ")] Processing event: " << getEventName(event));

    try
    {
        EventId eventId = event.getId();
        if (eventId == completeStartBehaviorEventId)
        {
            LOG("[" << getSmName() << "(" << thisPtr << ")] Completing startBehavior");
            runToCompletion();
        }
        else if (eventId == destroyEventId)
        {
            LOG("[" << getSmName() << "(" << thisPtr << ")] Deleting this");
            delete this;
            return;
        }
        else if (!toBeDeleted_)
        {
            LOG("[" << getSmName() << "(" << thisPtr << ")] Handling event");
            eventBeingProcessed_ = &event;
            handleEvent(event);
            eventBeingProcessed_ = 0;
            runToCompletion();
        }
    }
    catch (SmDestroyedException e)
    {
        // This object has been deallocated, must not use it in any way (e.g. call LOG)
        return;
    }

    LOG("[" << getSmName() << "(" << thisPtr << ")] Processing event done: " << getEventName(event));
}

const char* Sm::getTimerEventName(const EventId& eventId) const
{
    // default implementation for SMs without timers
    static_cast<void>(eventId);
    return "";
}

std::string Sm::getEventName(const Event& event) const
{
    std::string name = event.getName();
    if (name == "<timer>")
    {
        return getTimerEventName(event.getId());
    }
    else
    {
        return name;
    }
}

void Sm::scheduleTimer(EventId timerEventId, int timeoutMs)
{
    activeTimers_.push_back(createTimer(timerEventId, timeoutMs));
}

void Sm::cancelTimer(EventId timerEventId, bool doLog)
{
    for (size_t i = 0; i < activeTimers_.size(); i++)
    {
        if (activeTimers_[i]->getEventId() == timerEventId)
        {
            cancelTimer(i, doLog);
            break;
        }
    }
}

void Sm::cancelTimer(int index, bool doLog)
{
    activeTimers_[index]->cancel(doLog);
    delete activeTimers_[index];
    activeTimers_.erase(activeTimers_.begin() + index);
}

void Sm::cancelTimers()
{
    while (!activeTimers_.empty())
    {
        cancelTimer(0, false);
    }
}

void Sm::onTimer(EventId timerEventId)
{
    LOG("[" << getSmName() << "(" << this << ")] On timer: " << getTimerEventName(timerEventId) << std::endl);
    Event timerEvent(timerEventId, "<timer>");
    cancelTimer(timerEventId);
    processEvent(timerEvent);
}

void Sm::pushNullTransition()
{
    ++nullTransitionCount_;
}

void Sm::popNullTransition()
{
    --nullTransitionCount_;
}

void Sm::runToCompletion()
{
    while (nullTransitionCount_ > 0)
    {
        Event nullEvent(nullEventId, "<null>");
        eventBeingProcessed_ = &nullEvent;
        bool  consumed = handleEvent(nullEvent);
        eventBeingProcessed_ = 0;
        if (!consumed)
        {
            break;
        }
    }
}

void Sm::completeStartBehavior()
{
    if (nullTransitionCount_ > 0)
    {
        sendEvent(new Event(completeStartBehaviorEventId, "<completeStartBehavior>"));
    }
}

void Sm::handleNotConsumed(const Event& event)
{
    static_cast<void>(event); // not yet implemented
}

void Sm::asyncDestroy()
{
    toBeDeleted_ = true;
    sendEvent(new Event(destroyEventId, "<destroy>"));
}

void Sm::setLoggingEnabled(bool loggingEnabled)
{
    loggingEnabled_ = loggingEnabled;
}

}
