#pragma once
#include "Vector.h"

class Ground
{
	private:
		Ground() { };

	public:
		double yCoord = 600.0;
		double change_speed = 15;
		void change_ground_height(int changeValue);
		Vector& impact_point = Vector();
		Ground(const Ground&) = delete;

		static Ground& getGround() //Singleton
		{
			static Ground ground;
			return ground;
		};

};