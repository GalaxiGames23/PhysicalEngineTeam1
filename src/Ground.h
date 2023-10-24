#pragma once
#include "Vector.h"

class Ground
{
	private:
		////// Constructeur //////
		Ground() { };

	public:
		////// Attributs //////
		double yCoord = 600.0; // Hauteur du sol
		double change_speed = 15;
		Vector& impact_point = Vector();
		
		////// Getter //////
		static Ground& getGround() //Singleton
		{
			static Ground ground;
			return ground;
		};

		////// Setter //////
		void change_ground_height(int changeValue);

		////// Destructeur //////
		Ground(const Ground&) = delete;
};