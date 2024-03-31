#pragma once

#include <string>
#include <vector>

#include "Face.h"

class DiceInfo
{
	private:
		std::string dice_name;
		int mana_cost;
		std::vector<Face*> faces;

	public:
		DiceInfo(const std::string& dice_name, int mana_cost);

		const std::string& GetDiceName() const;
		int GetManaCost() const;
		void AddFace(Face* face);
		Face* GetFace(int face) const;
		std::vector<Face*> GetFaces() const;
		const int GetFacesSize() const;
		void PrintFaces();
};