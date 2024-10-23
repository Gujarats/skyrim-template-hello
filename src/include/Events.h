#pragma once
using EventResult = RE::BSEventNotifyControl;

class WaitStopEventHandler : public RE::BSTEventSink<RE::TESWaitStopEvent>
{
    public:
        static WaitStopEventHandler* GetSingleton()
        {
            static WaitStopEventHandler singleton;
            return &singleton;
        }

        EventResult ProcessEvent(const RE::TESWaitStopEvent* a_event, RE::BSTEventSource<RE::TESWaitStopEvent>*) override
        {
            if(a_event->interrupted){
                logger::info("[MENU] :: interrupted");
            } else {
                logger::info("[MENU] :: finish");
            }

            return EventResult::kContinue;
        }
        

        static void Register()
        {
            RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
            eventHolder->AddEventSink(WaitStopEventHandler::GetSingleton());
        }
};

class events
{
public:
	static void registerAllEventHandlers() {
        WaitStopEventHandler::Register();
	}
};
