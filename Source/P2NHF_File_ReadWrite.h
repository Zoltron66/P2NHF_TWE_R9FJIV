// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_File_ReadWrite.h
* 
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly felelos a fokent "txt" fájlok irasaert es
*   olvasasaert.
* - Kepes a kiolvasott erteket szovegkent es szamkent is visszaadni.
*
* [EN]
* Class description:
* - This class is responsible for writing and reading mainly "txt" files.
* - It can return the read values ​​as text and numbers.
*/

#pragma once

#include "CoreMinimal.h"

// ======================================================================================================
class TWE_API P2NHF_File_ReadWrite
{
private:
    FString Data;

    auto operator=(const P2NHF_File_ReadWrite& Param) = delete;

public:
	P2NHF_File_ReadWrite() : Data("") {}
    explicit P2NHF_File_ReadWrite(const unsigned Param);

    // Conversion operators
    operator unsigned int() const;
    operator float() const;
    operator FString() const { return Data; }
    
    // Assignment operators
    void operator=(const unsigned Param);
    void operator=(const FString& Param);

    // Read - Write
    bool ReadFromFile(const FString& SourceFilePath);
    bool WriteToFile(const FString& DestinationFilePath) const;
};
// ======================================================================================================