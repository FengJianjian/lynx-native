// Copyright 2017 The Lynx Authors. All rights reserved.

#include <runtime/js_vm.h>
#include <JavaScriptCore/JavaScript.h>

namespace jscore {
    void JSVM::Initialize() {
        JSContextGroupRef context_group = JSContextGroupCreate();
        vm_ = static_cast<void*>(const_cast<OpaqueJSContextGroup*>(context_group));
    }
    
    JSVM::~JSVM() {
        if(vm_) {
            JSContextGroupRef context_group = static_cast<JSContextGroupRef>(vm_);
            JSContextGroupRelease(context_group);
        }
    }
}