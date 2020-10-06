// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TurboCompilerStyle.h"

class FTurboCompilerCommands : public TCommands<FTurboCompilerCommands>
{
public:

	FTurboCompilerCommands()
		: TCommands<FTurboCompilerCommands>(TEXT("TurboCompiler"), NSLOCTEXT("Contexts", "TurboCompiler", "TurboCompiler Plugin"), NAME_None, FTurboCompilerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
