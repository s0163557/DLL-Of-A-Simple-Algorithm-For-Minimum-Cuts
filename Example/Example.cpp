// Example.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Example.h"


// This is an example of an exported variable
EXAMPLE_API int nExample=0;

// This is an example of an exported function.
EXAMPLE_API int fnExample(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CExample::CExample()
{
    return;
}
