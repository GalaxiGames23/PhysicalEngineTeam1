#pragma once
#include "Vector.h"
#include "Ground.h"
#define _USE_MATH_DEFINES

#include <cmath>
class Input
{
	private:
		double max_norm = 1000;
		double speed_norm = 400.0;
		double speed_angle = 1;

		double current_angle1 = 0;
		double current_angle2 = 0;
		double current_norm = 100;
		bool DessinerTrace = false; //<<< détermine si l'on affiche la trace
		bool AfficherPositions = false; //<<< détermine si l'on affiche les positions
		Input() { };
	
	public:
		bool angle_key = false;
		bool ground_key = false;
		int last_pos_x = 0;
		int last_pos_y = 0;
		Vector& max_point = Vector();
	
		Input(const Input&) = delete;

		static Input& getInput() 
		{
			static Input myInput;
			return myInput;
		};

		void set_Input(Vector &v) const;

		void change_norm(bool positive);

		void change_angle1(int positive);

		void change_angle2(int positive);

		void reset();
	
		void SetDessinerTrace(bool b) { this->DessinerTrace = b; }
		bool GetDessinerTrace() { return this->DessinerTrace; }
		void SetAfficherPositions(bool b) { this->AfficherPositions = b; }
		bool GetAfficherPositions() { return this->AfficherPositions; }

		void calculSomePoints(Vector& velocity, Vector& position, Vector & gravity, Ground & groundHeight);


};