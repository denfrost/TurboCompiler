// Copyright Epic Games, Inc. All Rights Reserved.

#include "TurboCompiler.h"
#include "TurboCompilerStyle.h"
#include "TurboCompilerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "Blutility/Public/EditorUtilitySubsystem.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"

static const FName TurboCompilerTabName("TurboCompiler");

#define LOCTEXT_NAMESPACE "FTurboCompilerModule"

void FTurboCompilerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTurboCompilerStyle::Initialize();
	FTurboCompilerStyle::ReloadTextures();

	FTurboCompilerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTurboCompilerCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTurboCompilerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTurboCompilerModule::RegisterMenus));
}

void FTurboCompilerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTurboCompilerStyle::Shutdown();

	FTurboCompilerCommands::Unregister();
}

void FTurboCompilerModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	/*FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FTurboCompilerModule::PluginButtonClicked()")),
							FText::FromString(TEXT("TurboCompiler.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);*/

	UObject* WidgetObj = LoadObject<UObject>(nullptr, TEXT("/TurboCompiler/TurboCompiler.TurboCompiler"));
	UEditorUtilityWidgetBlueprint* WidgetBP = (UEditorUtilityWidgetBlueprint*)WidgetObj;
	
	UEditorUtilitySubsystem* EditorUtilitySubsystemG = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	EditorUtilitySubsystemG->SpawnAndRegisterTab(WidgetBP);
}

void FTurboCompilerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTurboCompilerCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTurboCompilerCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTurboCompilerModule, TurboCompiler)