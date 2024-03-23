#pragma once

#include <string>

enum FaceType { ATTACK, DEFENSE, EFFECT_ADDER, EFFECT_DOUBLE_THROW, EFFECT_MULTIPLIER };

class Face
{
	public:
		std::string asset_id;
		unsigned int image_id;
		FaceType face_type;
		int value;

		Face(std::string asset_id = "", unsigned int image_id = 0, FaceType face_type = FaceType::ATTACK, int value = 0);

		void UseFace();
};