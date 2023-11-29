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

		double current_angle1 = 0; //<<<angle th�ta
		double current_angle2 = 0;//<<<angle phi
		double current_norm = 100;//<<< norme
		bool DessinerTrace = false; //<<< d�termine si l'on affiche la trace
		bool AfficherPositions = false; //<<< d�termine si l'on affiche les positions
		Vector printForcePosition = Vector();//<<< Vecteur repr�sentant la position de la force en entr�e
		InputRigidRegistre inputRigid;//<<< Cr�er et Stocker les forces d'un rigidBody avant de le spawn
		Input() { };

	public:
		bool angle_key = false; //<<< Si l'utilisateur est en train de changer l'angle
		bool ground_key = false;
		//Si l'utilisateurse d�place d'un cot�
		InputRegistre * forward_key = NULL;
		InputRegistre* backward_key = NULL;
		InputRegistre* right_key = NULL;
		InputRegistre* left_key = NULL;

		bool move_cam = false;

		int last_pos_x = 0; //<<< derni�re position de la souris en x
		int last_pos_y = 0;//<<< derni�re position de la souris en y
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

		/*Enlever le registre d'input contenu dans allInput */
		void removeInput(InputRegistre* registre, std::vector<InputRegistre*>& allInput);

		void changePosition(const Vector &deltaPosition);
		Vector getPosition() const { return printForcePosition; };

		void reset();

	
		void SetDessinerTrace(bool b) { this->DessinerTrace = b; }
		bool GetDessinerTrace() { return this->DessinerTrace; }
		void SetAfficherPositions(bool b) { this->AfficherPositions = b; }
		bool GetAfficherPositions() { return this->AfficherPositions; }

		/*Fonction de la phase 1, permettant de connaitre le point d'impact d'une particule avec le sol, en partant avec une velocit� initiale et une position initiale donn�e */
		void calculSomePoints(Vector& velocity, Vector& position, Vector & gravity, Ground & groundHeight);

		/*Lien entre l'interface graphique des sliders et les inputs en entr�e */
		void updateFromGui(double x, double y, double z, double radius, double theta, double phi);

		/*Lien entre l'interface graphique des sliders et les inputs en entr�e */
		void preSpawnRigid(Camera* myCam, Particule* moonParticle);

		/*Fonction permettant d'ajouter une force sur un solide, en fonction de l'entr�e contenu dans la classe*/
		void addForceToSpawningRegistry();

		/*Cr�er un solide, et le mettre dans la liste des solides du monde, avec les forces qui lui sont associ�es*/
		void spawnRigid(std::vector<Rigid*>& rigidBodies, RigidBodyForceRegistry &registreRigids);

		/*Dessiner les inputs en entr�e a l'aide d'une fl�che, ainsi que visualiser le solide qui va �tre cr�er*/
		void draw();
};