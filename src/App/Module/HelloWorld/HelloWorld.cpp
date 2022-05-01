/**
 *  mrh_app_base
 *  Copyright (C) 2021 - 2022 Jens Brörken
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *  3. This notice may not be removed or altered from any source distribution.
 */

// C / C++

// External

// Project
#include "./HelloWorld.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

HelloWorld::HelloWorld() : MRH_Module("HelloWorld") // Module name, for identification
{}

HelloWorld::~HelloWorld() noexcept
{}

//*************************************************************************************
// Update
//*************************************************************************************

void HelloWorld::HandleEvent(const MRH_Event* p_Event) noexcept
{
    /**
     *  This function is where events received by the module are handled.
     *  Modules will only receive events if they are recievable based on
     *  the result of the CanHandleEvent() call.
     *
     *  The HandleEvent function is called from the thread pool background
     *  threads. Multiple threads might call HandleEvent() at the same time
     *  if the libmrhab context was created with multiple threads.
     */
}

MRH_Module::Result HelloWorld::Update()
{
    /**
     *  The Update() function allows the module to update data without
     *  recieving a event. This function will be called once on the thread
     *  which performed the module stack update after the last HandleEvent() 
     *  call has been completed.
     *
     *  Depending on the return result the module stack takes differnt
     *  actions:
     *
     *  - MRH_Module::IN_PROGRESS
     *    The module will not be switched and stay in use as the current
     *    module.
     *
     *  - MRH_Module::FINISHED_APPEND
     *    The module stack will call the NextModule() function of this module
     *    to retrieve a module which will be appended behind this module in the
     *    stack. This module continues to exist and will be returned to if all
     *    modules before it have been popped.
     *
     *  - MRH_Module::FINISHED_REPLACE
     *    The module stack will call the NextModule() function of this module
     *    to retrieve a module which will be used to replace this module.
     *
     *  - MRH_Module::FINISHED_POP
     *    The module stack will remove this module, returning to the one before it.
     *    The module stack will signal that the app can close if this module was the
     *    top module.
     *
     *  Exceptions thrown here are passed down to the module stack update function.
     */
    
    printf("Hello, World!\n");
    return MRH_Module::FINISHED_POP;
}

std::shared_ptr<MRH_Module> HelloWorld::NextModule()
{
    /**
     *  This function will be called if the Update() function returned either
     *  MRH_Module::FINISHED_APPEND or MRH_Module::FINISHED_REPLACE.
     *
     *  The module can be freely created based on information of this module and
     *  other application data since the NextModule() call only happens after
     *  the update call.
     *
     *  Returning a shared_ptr storing NULL will cause the NULL module to be
     *  popped immediatly, returning to either this module if append was choosen
     *  or the one before it if replace was chosen.
     *  The module stack will signal that the app can close if the returned NULL
     *  module was meant to replace the top module.
     *
     *  Exceptions thrown here are passed down to the module stack update function.
     */
    
    throw MRH_ModuleException("HelloWorld",
                              "No module to switch to!");
}

//*************************************************************************************
// Getters
//*************************************************************************************

bool HelloWorld::CanHandleEvent(MRH_Uint32 u32_Type) noexcept
{
    /**
     *  The CanHandleEvent() function is used to determine if a
     *  module can handle a given event. Returning true means that
     *  the module can handle the function, false means it can't.
     *
     *  This function is called at the time of the event job being added, and
     *  returning false stops the event job from being added.
     */
    
    return false;
}
