#include "CaerusPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "CaerusEngine.h"

int main(int, char*[])
{
	CaerusEngine engine;
	engine.Run();
    return 0;
}