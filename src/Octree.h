#pragma once
#include "CoverSphere.h"
#include "BoxPair.h"

class Octree
{

private:
	int nbRigidPerZone = 4; // <<< Nombre de rigid max par zone
	Vector initPosition = Vector(500, 500, 0); // <<< Centre de la zone dans le monde
	double initSize = 2000; // <<< Taille max de la zone

	struct CoverSphereIntern
	{
		CoverSphere *nodeRigids;
		std::vector <CoverSphereIntern*> alreadyConsiderCollision;// <<< Si un rigid se trouve dans ce tableau, nous avons déja considérer la collision
	};

	struct Node
	{
		std::vector <CoverSphereIntern*> coverSpheres; 
		Node* nextNodes[8]; // <<< Noeuds enfants de l'arbre
		Node* parent; // <<< Noeud parent de l'arbre
		Vector center; // <<< Centre de la zone
		double size;// <<< taille de la zone
	};

	std::vector<CoverSphereIntern*> allSphere; // <<< tous les RigidBody du systeme
	std::vector<struct Node*> activeNode; // <<< Tous les noeuds actifs de l'arbre (les feuilles de l'arbre)

	Node* root;  // <<< Noeud de départ

	//Compter le nombre de Sphere qu'il y a à l'étage suivant de l'arbre (utile pour savoir s'il faut join ou pas)
	int countRigidInZone(Node * node);

	//Couper une zone en 8, et faire placer les spheres dans les nouvelles zones
	void cutNodeTree(Node* cutNode);

	//Fusionner 8 zone en une et placer les spheres dans la nouvelle zone
	void joinNodeTree(Node* parentJoinedNode);

	//Changement de zone par une sphere, mettre a jour l'arbre
	void changeZone(CoverSphere *s);
	
	//Test si une sphere est dans une zone ou pas, retourne 1 si l'entièreté de la sphere est dedans, 2 si elle chevauche la zone, et 0 sinon
	int isOnZone(Node* node, CoverSphere* sphere);

	//effacer les données (pour le destructeur)
	void eraseAll(Node* root);

	//enlever une sphere sans vérifier s'il faut join
	void removeRigid(CoverSphere* removeSphere);

public:
	Octree();
	~Octree();

	//Ajouter une sphere a l'arbre
	void addRigid(CoverSphere* addSphere);

	//Enlever une sphere de l'arbre avec vérification du join
	void eraseRigid(CoverSphere* removeSphere);

	//Détecter les couples collisions de collision possible
	std::vector<RigidPair*> allPossibleCollision(); 
	

};