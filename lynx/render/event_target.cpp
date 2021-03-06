// Copyright 2017 The Lynx Authors. All rights reserved.

#include "render/event_target.h"

#include "runtime/base/lynx_array.h"
#include "base/debug/memory_debug.h"

#include "base/trace_event/trace_event_common.h"

namespace lynx {

void EventTarget::DispatchEvent(const std::string& event, base::ScopedPtr<jscore::LynxArray> args) {
    TRACE_EVENT0("renderer", "EventTarget::DispatchEvent");
    EventListenerMap::iterator iter = event_listener_map_.find(event);
    if (iter == event_listener_map_.end()) return;
    for (int i = 0; i < iter->second->size(); i++) {
        if (target_data_ != NULL) {
            (*iter->second)[i]->function_->Run(target_data_, args.Get());
        }
    }
}

void EventTarget::AddEventListener(const std::string& event,
                                    jscore::LynxFunction* function,
                                    bool capture) {
    EventListenerMap::iterator iter = event_listener_map_.find(event);

    if (iter == event_listener_map_.end()) {
        iter = event_listener_map_.add(event,
                        lynx_new base::ScopedVector<EventListener>()).first;
    }
    iter->second->push_back(lynx_new EventListener(function, capture));

    RegisterEvent(event, EVENT_ADD);
}

void EventTarget::RemoveEventListener(const std::string& event,
                                      jscore::LynxFunction* function) {
    EventListenerMap::iterator iter = event_listener_map_.find(event);
    if (iter == event_listener_map_.end()) {
        return;
    }

    base::ScopedVector<EventListener>::iterator vec_iter =
                                                    iter->second->begin();

    for (vec_iter; vec_iter != iter->second->end(); vec_iter++) {
        if ((*vec_iter)->function_->GetKey().compare(function->GetKey()) == 0) {
            iter->second->erase(vec_iter);
            break;
        }
    }

    RegisterEvent(event, EVENT_REMOVE);
}
}  // namespace lynx
