/**
 *  mrh_app_base
 *  Copyright (C) 2021 Jens Brörken
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
#include <cstdio>
#include <string>

// External
#include <libmrh/MRH_AppLoop.h>
#include <libmrhab.h>

// Project
#include "./Module/HelloWorld/HelloWorld.h"
#include "./Revision.h"

// Pre-defined
namespace
{
    libmrhab* p_Context = NULL;
    bool b_CloseApp = false;

    // The callback thread count to hand events to the current module
    // 1 thread is the minimum, 0 will cause an exception
    constexpr int i_CallbackThreadCount = 1;
}


// Prevent name wrangling for library header functions
#ifdef __cplusplus
extern "C"
{
#endif
    
    //*************************************************************************************
    // Init
    //*************************************************************************************

    int MRH_Init(const char* p_LaunchInput, int i_LaunchCommandID)
    {
        /**
         *  This function will be called once on application startup.
         *  The library context should be created here to catch early issues.
         */
    
        try
        {
            // Create the library context, setting up the module stack
            // and thread pool for event jobs
            p_Context = new libmrhab(std::make_unique<HelloWorld>(),
                                     i_CallbackThreadCount);
            return 0;
        }
        catch (MRH_ABException& e)
        {
            printf("Failed to initialize app base library: %s\n", e.what());
            return -1;
        }
        catch (std::exception& e) // alloc and other stuff
        {
            printf("General exception: %s\n", e.what());
            return -1;
        }
    }

    //*************************************************************************************
    // Recieve Event
    //*************************************************************************************

    void MRH_RecieveEvent(const MRH_Event* p_Event)
    {
        /**
         *  This function is called until all events recieved by application services
         *  have been handed to the application.
         *  Events recieved here are never NULL and don't have to be deallocated after
         *  use.
         *
         *  The recieved event should here be handed to the context to give the event
         *  as a job to the current module.
         */
    
        try
        {
            // Add recieved event as library thread pool job
            // for the current module
            p_Context->AddJob(p_Event);
        }
        catch (MRH_ABException& e)
        {
            printf("Failed to add event job: %s\n", e.what());
        }
    }

    //*************************************************************************************
    // Send Event
    //*************************************************************************************

    MRH_Event* MRH_SendEvent(void)
    {
        /**
         *  This function is called after the last MRH_RecieveEvent function call.
         *  It will be called until NULL is returned (meaning no more events to send).
         *
         *  The current module should be updated here (for main thread guarantee), once.
         */
    
        // We update the module first, but this is actually
        // not a requirement. It just makes events sendable
        // faster.
        // We flag with a boolean to prevent calling module
        // updates for every SendEvent call
        static bool b_UpdateModules = true;
    
        if (b_UpdateModules == true)
        {
            try
            {
                // Perform the update first, generating module events
                LIBMRHAB_UPDATE_RESULT b_Result = p_Context->Update();
            
                // App closing requested?
                if (b_Result == LIBMRHAB_UPDATE_CLOSE_APP)
                {
                    // Set app closure, and then send remaining events
                    // generated this module update
                    b_CloseApp = true;
                }
            }
            catch (MRH_ABException& e)
            {
                printf("Module update failed: %s\n", e.what());
            
                // Stop sending immediatly to get to MRH_CanExit()
                b_CloseApp = true;
                return NULL;
            }
        
            // Reset, next calls don't update
            b_UpdateModules = false;
        }
    
        // Send the oldest available event and remove it from storage
        MRH_Event* p_Event = MRH_EventStorage::Singleton().GetEvent(true);
    
        // Is the container empty now with nothing left to send?
        if (p_Event == NULL)
        {
            // All generated events are sent, next call should update again
            b_UpdateModules = true;
        }
    
        return p_Event;
    }

    //*************************************************************************************
    // Exit
    //*************************************************************************************

    int MRH_CanExit(void)
    {
        /**
         *  This function is called at the start of each update loop. Returning 0
         *  then breaks out of the update loop and continues to MRH_Exit().
         */
    
        return b_CloseApp == true ? 0 : -1;
    }

    void MRH_Exit(void)
    {
        /**
         *  This function is called once on normal service exit. A crash will not call
         *  this function.
         */
    
        // Check NULL for the rare case where SIGTERM hits before MRH_Init (or during)
        if (p_Context != NULL)
        {
            delete p_Context;
        }
    }
    
#ifdef __cplusplus
}
#endif
