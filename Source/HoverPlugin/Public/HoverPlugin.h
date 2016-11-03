// Some copyright should be here...

#pragma once

#include "ModuleManager.h"


class FHoverPluginModule
	: public IModuleInterface
{
public:

	//~ IModuleInterface interface

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};