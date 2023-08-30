// Copyright Epic Games, Inc. All Rights Reserved.

#include "XCurlWrapper.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "XCurlWrapperLibrary/ExampleLibrary.h"

#define LOCTEXT_NAMESPACE "FXCurlWrapperModule"

void FXCurlWrapperModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("XCurlWrapper")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/XCurlWrapperLibrary/XSX/XCurlWrapper.dll"));

	//#if PLATFORM_WINDOWS
//	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/XCurlWrapperLibrary/Win64/ExampleLibrary.dll"));
//#elif PLATFORM_MAC
//    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/XCurlWrapperLibrary/Mac/Release/libExampleLibrary.dylib"));
//#elif PLATFORM_LINUX
//	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/XCurlWrapperLibrary/Linux/x86_64-unknown-linux-gnu/libExampleLibrary.so"));
//#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		const auto Func = (void(*)())FPlatformProcess::GetDllExport(ExampleLibraryHandle, TEXT("ExampleLibraryFunction"));
		Func();
		
		// Call the test function in the third party library that opens a message box
		//ExampleLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FXCurlWrapperModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXCurlWrapperModule, XCurlWrapper)
