#pragma once
#include "Vector.h"
#include "Ground.h"
#include "InputForce.h"

#include "Rigid.h"
#define _USE_MATH_DEFINES

#include <cmath>

class RigidBodyForceRegistry;
class RigidBodyForce;
class Camera;

struct InputRegistre {
	Particule* particule;
	InputForce* fg;
};

struct InputRigidRegistre {
	Rigid* rb;
	std::vector<RigidBodyForce*> forces;
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
		Vector printForcePosition = Vector();
		InputRigidRegistre inputRigid;//<<< Créer et Stocker les forces d'un rigidBody avant de le spawn
		Input() { };

	public:
		bool angle_key = false; //<<< Si l'utilisateur est en train de changer l'angle
		bool ground_key = false;
		//Si l'utilisateurse déplace d'un coté
		InputRegistre * forward_key = NULL;
		InputRegistre* backward_key = NULL;
		InputRegistre* right_key = NULL;
		InputRegistre* left_key = NULL;

		bool move_cam = false;

		int last_pos_x = 0; //<<< dernière position de la souris en x
		int last_pos_y = 0;//<<< dernière position de la souris en y
		Vector& max_point = Vector();
	
		Input(const Input&) = delete;

		static Input& getInput()  //Singleton
		{
			static Input myInput;
			return myInput;
		};

		void setInput(Vector &v) const;

		void changeNorm(bool positive);

		void changeAngle1(int positive);

		void changeAngle2(int positive);

		void removeInput(InputRegistre* registre, std::vector<InputRegistre*>& allInput);

		void changePosition(const Vector &deltaPosition);
		Vector getPosition() const { return printForcePosition; };

		void reset();

	
		void SetDessinerTrace(bool b) { this->DessinerTrace = b; }
		bool GetDessinerTrace() { return this->DessinerTrace; }
		void SetAfficherPositions(bool b) { this->AfficherPositions = b; }
		bool GetAfficherPositions() { return this->AfficherPositions; }

		void calculSomePoints(Vector& velocity, Vector& position, Vector & gravity, Ground & groundHeight);

		void updateFromGui(double x, double y, double z, double radius, double theta, double phi);

		void preSpawnRigid(Camera* myCam, Particule* moonParticle);

		void addForceToSpawningRegistry();

		void spawnRigid(std::vector<Rigid*>& rigidBodies, RigidBodyForceRegistry &registreRigids);

		void draw();
};