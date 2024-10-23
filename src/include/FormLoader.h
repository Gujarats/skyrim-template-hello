#pragma once
#include "Utility.h"

class FormLoader
{
public:
  
    static FormLoader* GetSingleton()
    {
        static FormLoader formLoader;
        return &formLoader;
    }

    void LoadAllForms() { 
        logger::info("Begin load all forms");
    }

    // Cache commonly called addresses to avoid address lib overhead
    void CacheGameAddresses()
    {
        auto utility = Utility::GetSingleton();
        // Cache player singleton address
        utility->PlayerSingletonAddress       = RELOCATION_ID(517014, 403521).address(); // what in the world ?? where does the number coming from ??
    }

};
