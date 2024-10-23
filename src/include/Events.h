#pragma once
#include "Utility.h"

namespace Events
{
    class WaitStopEventHandler : public RE::BSTEventSink<RE::TESWaitStopEvent>
    {
    public:
        static WaitStopEventHandler* GetSingleton()
        {
            static WaitStopEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESWaitStopEvent* a_event, RE::BSTEventSource<RE::TESWaitStopEvent>*) override
        {
            if(a_event->interrupted){
                logger::info("[MENU] :: interrupted");
            } else {
                logger::info("[MENU] :: finish");
            }

            return RE::BSEventNotifyControl::kContinue;
        }
        

        static void Register()
        {
            RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
            eventHolder->AddEventSink(WaitStopEventHandler::GetSingleton());
        }
    };

    inline static void Register()
    {
        WaitStopEventHandler::Register();
    }
}
