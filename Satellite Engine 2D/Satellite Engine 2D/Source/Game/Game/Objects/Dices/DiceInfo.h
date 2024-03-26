#pragma once

#include <string>
#include <vector>

#include "Face.h"

class DiceInfo
{
	private:
		std::string dice_name;
		std::vector<Face*> faces;

	public:
		DiceInfo(std::string dice_name);

		std::string GetDiceName();
		void AddFace(Face* face);
		Face* GetFace(int face);
		std::vector<Face*> GetFaces();
		int GetFacesSize();
		void PrintFaces();
};