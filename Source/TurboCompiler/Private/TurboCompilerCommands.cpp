// Copyright Epic Games, Inc. All Rights Reserved.

#include "TurboCompilerCommands.h"

#define LOCTEXT_NAMESPACE "FTurboCompilerModule"

void FTurboCompilerCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TurboCompiler", "Execute TurboCompiler action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
