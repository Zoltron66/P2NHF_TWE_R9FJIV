// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Fuel_Item.h
*
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly leszarmazottja a P2NHF_Item osztalynak, ami az jelenti,
*   hogy van mar tipus és suly adattagja, ezt kiegesziti meg egy
*   egyedi tulajdonsaggal, ami a liter (mennyi üzemanyagot tartalmaz).
* - Az ososztalyahoz hasonloan ez is alkalmaz settereket es gettereket,
*   tovabba feluirja az ososztaly virtualis fuggvenyeit.
*
* [EN]
* Class description:
* - This class is a derived class from the P2NHF_Item class, which means that
*   it already has type and weight data elements, and it is supplemented by
*	another unique property, which is the liter (how much fuel it contains).
* - Similar to the parent class, this also uses setter methods and getter methods,
*   furthermore it overrides the virtual functions of the parent class.
*/

#pragma once

#include "CoreMinimal.h"
#include "P2NHF_Item.h"

// ======================================================================================================
class TWE_API P2NHF_Fuel_Item : public P2NHF_Item
{
private:
	unsigned Liter;

public:
	P2NHF_Fuel_Item() : Liter(0) {}
	P2NHF_Fuel_Item(const P2NHF_Item* Param);
	virtual ~P2NHF_Fuel_Item() {}

	// Accessor methods for liter
	void SetLiter(const unsigned Param);
	float GetData() const override final { return float(Liter); }

	// Random default value setter function for this item
	void SetupSelf() override final;
};
// ======================================================================================================