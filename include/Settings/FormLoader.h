#pragma once
#include "Utility.h"
#include "Buffs/Awake.h"

class FormLoader
{
public:
  
    static FormLoader* GetSingleton()
    {
        static FormLoader formLoader;
        return &formLoader;
    }

    void LoadAllForms() { 
      /*Load all assets start here*/
    }

    // Cache commonly called addresses to avoid address lib overhead
    void CacheGameAddresses()
    {
        auto utility = Utility::GetSingleton();
        // Cache player singleton address
        utility->PlayerSingletonAddress       = RELOCATION_ID(517014, 403521).address(); // what in the world ?? where does the number coming from ??
    }

};
