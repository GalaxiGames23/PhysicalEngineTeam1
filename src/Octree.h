#pragma once
#include "CoverSphere.h"
#include "BoxPair.h"

class Octree
{

private:
	int nbRigidPerZone = 3; // <<< Nombre de rigid max par zone
	Vector initPosition = Vector(0, 0, 0); // <<< Centre de la zone dans le monde
	double initSize = 1000; // <<< Taille max de la zone
	double minSizeBlock = 20;// <<< taille minimal d'une zone de l'arbre, une zone qui est est plus petite que cette valeur ne se d�coupera pas en sous-zone, m�me s'il y a plein de rigid

	struct CoverSphereIntern
	{
		CoverSphere *nodeRigids;// <<< Sphere de collision associ� � un rigidBody
		std::vector <CoverSphereIntern*> alreadyConsiderCollision;// <<< Si un rigid se trouve dans ce tableau, nous avons d�ja consid�rer la collision
	};

	struct Node
	{
		std::vector <CoverSphereIntern*> coverSpheres; 
		Node* nextNodes[8]; // <<< Noeuds enfants de l'arbre
		Node* parent; // <<< Noeud parent de l'arbre
		Vector center; // <<< Centre de la zone
		double size;// <<< taille de la zone
		std::unordered_map<CoverSphere*, int> result;// <<<sauvegarde du pr�c�dent r�sultat de collision avec l'arbre, calculer par compareLastPosValue a la frame pr�c�dente
	};

	std::vector<CoverSphereIntern*> allSphere; // <<< tous les RigidBody du systeme
	std::vector<struct Node*> activeNode; // <<< Tous les noeuds actifs de l'arbre (les feuilles de l'arbre)

	Node* root;  // <<< Noeud de d�part
	bool enableDrawing = false;
	//Compter le nombre de Sphere qu'il y a � l'�tage suivant de l'arbre (utile pour savoir s'il faut join ou pas)
	int countRigidInZone(Node * node);

	//Couper une zone en 8, et faire placer les spheres dans les nouvelles zones
	void cutNodeTree(Node* cutNode);

	//Fusionner 8 zone en une et placer les spheres dans la nouvelle zone
	void joinNodeTree(Node* parentJoinedNode);

	//Fusionner 8 zone en une et placer les spheres dans la nouvelle zone
	void joinRec(Node* joinedNode);

	//Changement de zone par une sphere, mettre a jour l'arbre
	void changeZone(CoverSphereIntern *s);
	
	//Test si une sphere est dans une zone ou pas, retourne 1 si l'enti�ret� de la sphere est dedans, 2 si elle chevauche la zone, et 0 sinon
	int isOnZone(Node* node, CoverSphere* sphere);

	//Test si une sphere est dans une zone ou pas, retourne 1 si l'enti�ret� de la sphere est dedans, 2 si elle chevauche la zone, et 0 sinon
	int compareLastPosValue(Node* node, CoverSphere* sphere);

	//effacer les donn�es (pour le destructeur)
	void eraseAll(Node* root);

	//enlever une sphere, sans la supprimer au niveau m�moire
	void internRemove(CoverSphereIntern* removeSphere);

	//ConvertSign
	int convertSign(int x) {
		return (x > 0) + 2 * (x < 0);
	}
	//ajouter une sphere, sans la supprimer au niveau m�moire
	void internAdd(CoverSphereIntern* addSphere);

public:
	Octree();
	~Octree();

	//Ajouter une sphere a l'arbre
	void addRigid(Rigid* addSphere);

	//Enlever une sphere de l'arbre avec v�rification du join
	void eraseRigid(Rigid* removeSphere);

	//D�tecter les couples collisions de collision possible
	std::vector<RigidPair*> allPossibleCollision(); 

	std::vector<BoxPair*> convertToBox(const std::vector<RigidPair*> &r);

	/*D�truire la m�moire allou�e pour les tableaux allrigid et allbox*/
	void freePossibleCollision(std::vector<RigidPair*>& allrigid, std::vector<BoxPair*>& allbox);
	/*afficher l'octree*/
	void draw();
	/*rend l'affichage de l'octree visible ou invisible � l'�cran*/
	void changeEnableDrawing();
	

};