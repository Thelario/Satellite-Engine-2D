#pragma once

#include <map>
#include <string>

#include "../Objects/Dices/Face.h"

class FacesManager
{
	private:
		std::map<std::string, Face*> faces;

	public:
		FacesManager();
		~FacesManager();

		bool LoadFaces();
		void ClearFaces();

		Face* GetFace(const std::string& face_name) const;
};