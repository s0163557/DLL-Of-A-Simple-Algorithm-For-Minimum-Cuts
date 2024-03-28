// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the EXAMPLE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// EXAMPLE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef EXAMPLE_EXPORTS
#define EXAMPLE_API __declspec(dllexport)
#else
#define EXAMPLE_API __declspec(dllimport)
#endif

// This class is exported from the dll
class EXAMPLE_API CExample {
public:
	CExample(void);
	// TODO: add your methods here.
};

extern EXAMPLE_API int nExample;

EXAMPLE_API int fnExample(void);
