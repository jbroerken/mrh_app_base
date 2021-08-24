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
#include <stdio.h>

// External
#include <libmrhs.h>

// Project


// Prevent name wrangling for library header functions
#ifdef __cplusplus
extern "C"
{
#endif
    
    //*************************************************************************************
    // Init
    //*************************************************************************************

    int MRH_Init(void)
    {
        /**
         *  This function will be called once on service startup.
         *  Initial events and service setup should be handled here.
         */
    
        return 0;
    }

    //*************************************************************************************
    // Update
    //*************************************************************************************

    int MRH_Update(void)
    {
        /**
         *  This function will be called in a set timeframe (defined by configuration values).
         *  Updating the service and preparing events to sent should be performed here.
         */
    
        return 0;
    }

    //*************************************************************************************
    // Event
    //*************************************************************************************

    MRH_Event* MRH_SendEvent(void)
    {
        /**
         *  This function is called after the MRH_Update function. It will be called until
         *  NULL is returned (meaning no more events to send).
         */
    
        return NULL;
    }

    //*************************************************************************************
    // Exit
    //*************************************************************************************

    void MRH_Exit(void)
    {
        /**
         *  This function is called once on normal service exit. A crash will not call
         *  this function.
         */
    }

#ifdef __cplusplus
}
#endif
