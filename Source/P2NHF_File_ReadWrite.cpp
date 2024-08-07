// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_File_ReadWrite.cpp
*/

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "P2NHF_File_ReadWrite.h"

// ======================================================================================================

P2NHF_File_ReadWrite::P2NHF_File_ReadWrite(const unsigned Param)
{
	Data = FString::Printf(TEXT("%d"), Param);
}

P2NHF_File_ReadWrite::operator unsigned int() const
{
	TCHAR* EndPtr;
	unsigned OutputUnsigned = unsigned(FCString::Strtoui64(*Data, &EndPtr, 10));
	if (*EndPtr != '\0')
	{
		UE_LOG(LogTemp, Error, TEXT("FString to unsigned conversion failed in P2NHF_File_ReadWrite.cpp[22]"));
		return 0;
	}
	return OutputUnsigned;
}

P2NHF_File_ReadWrite::operator float() const
{
	return FCString::Atof(*Data);
}

void P2NHF_File_ReadWrite::operator=(const unsigned Param)
{
	Data = FString::Printf(TEXT("%d"), Param);
}

void P2NHF_File_ReadWrite::operator=(const FString& Param)
{
	Data = Param;
}

bool P2NHF_File_ReadWrite::ReadFromFile(const FString& SourceFilePath)
{
	FString FilePath = FPaths::ProjectDir() / SourceFilePath;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		Data = FString::Printf(TEXT("Read from %s file failed! - Can't found!"), *FilePath);
		UE_LOG(LogTemp, Error, TEXT("Read from %s file failed! - Can't found!"), *FilePath);
		return false;
	}

	FString TempString = "";

	if (!FFileHelper::LoadFileToString(TempString, *FilePath))
	{
		Data = FString::Printf(TEXT("Read from %s file failed! - Was not able to read!"), *SourceFilePath);
		UE_LOG(LogTemp, Error, TEXT("Read from %s file failed! - Was not able to read!"), *SourceFilePath);
		return false;
	}

	Data = TempString;
	return true;
}

bool P2NHF_File_ReadWrite::WriteToFile(const FString& DestinationFilePath) const
{
	FString FilePath = FPaths::ProjectDir() / DestinationFilePath;
	if (!FFileHelper::SaveStringToFile(Data, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Write to %s file failed!"), *DestinationFilePath);
		return false;
	}

	return true;
}
// ======================================================================================================