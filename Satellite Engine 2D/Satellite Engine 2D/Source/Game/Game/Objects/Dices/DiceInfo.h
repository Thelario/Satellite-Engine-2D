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
		DiceInfo(std::string dice_name, int mana_cost);

		std::string GetDiceName();
		int GetManaCost();
		void AddFace(Face* face);
		Face* GetFace(int face);
		std::vector<Face*> GetFaces();
		int GetFacesSize();
		void PrintFaces();
};