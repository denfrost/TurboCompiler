// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TurboCompilerLib.h"
#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Windows/MinWindows.h"
#include <tlhelp32.h>



void UTurboCompiler::SetHighPriority(bool &ProcessFound)
{
	FString nameP1 = "ShaderCompileWorker.exe";
	FString nameP2 = "UnrealLightmass.exe";

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	int NumberProcess = 0;

	std::wstring widecharP1;
	for (int i = 0; i < nameP1.Len(); ++i) widecharP1 += wchar_t(nameP1[i]);
	const wchar_t* resultP1 = widecharP1.c_str();

	std::wstring widecharP2;
	for (int i = 0; i < nameP2.Len(); ++i) widecharP2 += wchar_t(nameP2[i]);
	const wchar_t* resultP2 = widecharP2.c_str();

	if (Process32First(hProcessSnap, &pe32) == TRUE)
	{
		while (Process32Next(hProcessSnap, &pe32) == TRUE)
		{
			if (_tcsicmp(pe32.szExeFile, (resultP1)) == 0)
			{
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
				NumberProcess = NumberProcess + 1;

				CloseHandle(hProcess);
			}
			if (_tcsicmp(pe32.szExeFile, (resultP2)) == 0)
			{
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
				NumberProcess = NumberProcess + 1;

				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(hProcessSnap);
	if (NumberProcess > 0) {
		ProcessFound = true;
	}
	else {
		ProcessFound = false;
	}
}

