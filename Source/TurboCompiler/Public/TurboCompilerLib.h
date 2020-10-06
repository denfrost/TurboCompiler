// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TurboCompilerLib.generated.h"

UCLASS()
class TURBOCOMPILER_API UTurboCompiler : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "TurboCompiler", meta = (WorldContext = WorldContextObject))
		static void SetHighPriority(bool &ProcessFound);
};
