// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Item.h
*
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly felelos a jatekban fellelheto targyak alapveto,
*   kozos tulajdonsagainak megahtarozasaert, mint tipus es suly.
* - Tovabba ez az osztaly alkotja az altalanos targy listaelemet,
*   ezt lista alapu heterogen kollekciora hasznalja a program.
* - Tartlamaz Gettereket es Settereket, tovabba tisztan virtualsi
*   fuggvenyeket.
*
* [EN]
* Class description:
* - This class is responsible for defining the common properties of
*   objects found in the game, such as type and weight.
* - Furthermore, this class forms the general object list element, which
*   is used by the program for list-based heterogeneous collection.
* - Contains Getter methods, Setter methods and purely virtual
*   functions.
*/

#pragma once

#include "CoreMinimal.h"

// ======================================================================================================
enum class EItemType : uint8
{
	I_invalid,
	I_battery,
	I_fuse,
	I_wire,
	I_fuel
};

class TWE_API P2NHF_Item
{
private:
	EItemType Type;
	float Weight;
	P2NHF_Item* Next;

public:
	P2NHF_Item() : Type(EItemType::I_invalid), Weight(0.0f), Next(nullptr) {}
	P2NHF_Item(const EItemType Type, const float Weight, P2NHF_Item* Next = nullptr) : Type(Type), Weight(Weight), Next(Next) {}
	virtual ~P2NHF_Item() {}

	// Accessor methods for Type, with default value in the Setter method
	EItemType GetType() const { return Type; }
	void SetType(const EItemType Param = EItemType::I_invalid) { Type = Param; }
	
	// Accessor methods for Weight
	float GetWeight() const { return Weight; }
	void SetWeight(const float Param);

	// Accessor methods for Next pointer
	bool SetNext(P2NHF_Item* Param);
	P2NHF_Item* GetNext() const { return Next; }
	
	// Pure virtual functions, for future derived classes
	virtual float GetData() const = 0;
	virtual void SetupSelf() = 0;
};
// ======================================================================================================