#pragma once
#include "Vector.h"
#include "Ground.h"
#include "InputForce.h"
#define _USE_MATH_DEFINES

#include <cmath>


struct InputRegistre {
	Particule* particule;
	InputForce* fg;
};

class Input
{
	private:
		double max_norm = 1000; //<<<max de la norme possible
		double speed_norm = 400.0; //<<<vitesse de progression de la norme
		double speed_angle = 1; //<<<vitesse de progression des angles

		double current_angle1 = 0; //<<<angle théta
		double current_angle2 = 0;//<<<angle phi
		double current_norm = 100;//<<< norme
		bool DessinerTrace = false; //<<< détermine si l'on affiche la trace
		bool AfficherPositions = false; //<<< détermine si l'on affiche les positions
		Input() { };
	
	public:
		bool angle_key = false; //<<< Si l'utilisateur est en train de changer l'angle
		bool ground_key = false;
		//Si l'utilisateurse déplace d'un coté
		InputRegistre * forward_key = NULL;
		InputRegistre* backward_key = NULL;
		InputRegistre* right_key = NULL;
		InputRegistre* left_key = NULL;

		int last_pos_x = 0; //<<< dernière position de la souris en x
		int last_pos_y = 0;//<<< dernière position de la souris en y
		Vector& max_point = Vector();
	
		Input(const Input&) = delete;

		static Input& getInput()  //Singleton
		{
			static Input myInput;
			return myInput;
		};

		void set_Input(Vector &v) const;

		void change_norm(bool positive);

		void change_angle1(int positive);

		void change_angle2(int positive);

		void remove_input(InputRegistre* registre, std::vector<InputRegistre*>& allInput);

		void reset();
	
		void SetDessinerTrace(bool b) { this->DessinerTrace = b; }
		bool GetDessinerTrace() { return this->DessinerTrace; }
		void SetAfficherPositions(bool b) { this->AfficherPositions = b; }
		bool GetAfficherPositions() { return this->AfficherPositions; }

		void calculSomePoints(Vector& velocity, Vector& position, Vector & gravity, Ground & groundHeight);


};