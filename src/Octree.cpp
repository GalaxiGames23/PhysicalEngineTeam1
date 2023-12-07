#include "Octree.h"
#include "of3dPrimitives.h"
#include <ofGraphics.h>
#include <of3dGraphics.h>

int Octree::countRigidInZone(Node* node)
{
	if (node->nextNodes[0] == nullptr)
	{
		return node->coverSpheres.size();
	}
	std::vector<CoverSphereIntern*> saveSphere;
	
	for (int i = 0; i < 8; i++)
	{
		for (CoverSphereIntern* sphere : node->nextNodes[i]->coverSpheres)
		{
			if (std::find(saveSphere.begin(), saveSphere.end(), sphere) == saveSphere.end())
			{
				saveSphere.push_back(sphere);
			}
		}
	}
	
	return saveSphere.size();
}

std::vector<BoxPair*> Octree::convertToBox(const std::vector<RigidPair*>& allrigid)
{
	vector<BoxPair*> allbox;

	for (RigidPair *rigid : allrigid)
	{
		BoxPair *b = new BoxPair();
		b->box1 = (Box*)rigid->rigid1;
		b->box2 = (Box*)rigid->rigid2;
		allbox.push_back(b);
	}
	return allbox;
}

void Octree::cutNodeTree(Node* cutNode)
{
	if (cutNode->nextNodes[0] != nullptr)
	{
		printf("Error, use function on active node\n");
		return;
	}
	
	double new_size = cutNode->size / 2;

	Vector allSize[8] = { Vector(1,1,1), Vector(1,-1,-1), Vector(1,1,-1), Vector(1,-1,1),
	 Vector(-1,1,1), Vector(-1,-1,-1), Vector(-1,1,-1), Vector(-1,-1,1), };
	auto it = find(activeNode.begin(), activeNode.end(),
		cutNode);

	if (it != activeNode.end()) {
		activeNode.erase(it);
	}
	else
	{
		printf("Error, node not found on activeNode to cut\n");
		return;
	}

	
	for (int i = 0; i < 8; i++)
	{
		Node* newNode = new Node(); 
		newNode->center = cutNode->center + allSize[i] * new_size; // definition du nouveau centre
		newNode->size = new_size;
		newNode->parent = cutNode;
		for (int j = 0; j < 8; j++) newNode->nextNodes[j] = nullptr; 
		
		for (int j = 0; j < cutNode->coverSpheres.size(); j++)
		{
			CoverSphere* analyseSphere = cutNode->coverSpheres[j]->nodeRigids;
			if (isOnZone(newNode,analyseSphere) > 0) //Si la sphere est dans la nouvelle zone
			{
				newNode->result[analyseSphere] = compareLastPosValue(newNode, analyseSphere);
				newNode->coverSpheres.push_back(cutNode->coverSpheres[j]);
				
			}
		}
		cutNode->nextNodes[i] = newNode;
		activeNode.push_back(newNode);
	}
}

void Octree::joinNodeTree(Node* parentJoinedNode)
{
	if (parentJoinedNode->nextNodes[0] == nullptr)
	{
		printf("Error, use function on not active node\n");
		return;
	}
	
	
	for (int i = 0; i < 8; i++)
	{
		joinRec(parentJoinedNode->nextNodes[i]);
		parentJoinedNode->nextNodes[i] = nullptr;
	}

	activeNode.push_back(parentJoinedNode);
	for (CoverSphereIntern* s : parentJoinedNode->coverSpheres)
	{
		parentJoinedNode->result[s->nodeRigids] = compareLastPosValue(parentJoinedNode, s->nodeRigids);
	}
}

void Octree::joinRec(Node* joinedNode)
{
	if (joinedNode->nextNodes[0] == nullptr)
	{
		auto it = find(activeNode.begin(), activeNode.end(),
			joinedNode);

		if (it != activeNode.end()) {
			activeNode.erase(it);
		}
		else
		{
			printf("Error, node not found on activeNode for join\n");
			return;
		}
		delete joinedNode;
		return;
	}

	for (int i = 0; i < 8; i++)
	{
		joinRec(joinedNode->nextNodes[i]);
	}
	delete joinedNode;
}

void Octree::changeZone(CoverSphereIntern* s)
{
	internRemove(s);
	internAdd(s);
}
int Octree::compareLastPosValue(Node* node, CoverSphere* sphere)
{
	Vector direction = sphere->GetRb()->GetCenter()->GetPosition() - node->center;
	double directionx = direction.projection(Vector(1, 0, 0)).get_x();
	double directiony = direction.projection(Vector(0, 1, 0)).get_y();
	double directionz = direction.projection(Vector(0, 0, 1)).get_z();

	double testx = abs(directionx) < node->size + sphere->GetRadius();
	double testy = abs(directiony) < node->size + sphere->GetRadius();
	double testz = abs(directionz) < node->size + sphere->GetRadius();
	return testx * convertSign(directionx) + 4 * testy * convertSign(directiony) + 16 * convertSign(directionz);
}

int Octree::isOnZone(Node* node, CoverSphere* sphere)
{
	Vector direction = sphere->GetRb()->GetCenter()->GetPosition() - node->center;
	double projx = direction.projection(Vector(1, 0, 0)).norm();
	double projy = direction.projection(Vector(0, 1, 0)).norm();
	double projz = direction.projection(Vector(0, 0, 1)).norm();
	if (projx < node->size - sphere->GetRadius() && projy < node->size - sphere->GetRadius() && projz < node->size - sphere->GetRadius())
	{
		return 1; // la sphere est entierement a l'intérieur du 
	}
	else if (projx < node->size + sphere->GetRadius() && projy < node->size + sphere->GetRadius() && projz < node->size + sphere->GetRadius())
	{
		return 2;  // la sphere est partiellement dans la zone, mais elle en chevauche une autre
	}

	return 0;
}

void Octree::eraseAll(Node* root)
{
	std::vector<Node*> saveParent;
	while (true)
	{
		Node* currentNode = activeNode.back();
		activeNode.pop_back();

		if (currentNode->parent != nullptr && std::find(saveParent.begin(), saveParent.end(), currentNode) != saveParent.end())
		{
			saveParent.push_back(currentNode);
		}
		
		delete currentNode;

		if (activeNode.empty() && saveParent.empty())
		{
			break;
		}
		else if (activeNode.empty() && !saveParent.empty())
		{
			while (!saveParent.empty())
			{
				activeNode.push_back(saveParent.back());
				saveParent.pop_back();
			}
		}
	}
}

Octree::Octree()
{
	root = new Node();
	root->center = initPosition;
	root->size = initSize;
	root->parent = nullptr;
	for (int i = 0; i < 8; i++) root->nextNodes[i] = nullptr;
	activeNode.push_back(root);
}

Octree::~Octree()
{
	eraseAll(root);
}
void Octree::internAdd(CoverSphereIntern* newSphere)
{
	for (Node* n : activeNode)
	{
		if (isOnZone(n, newSphere->nodeRigids) > 0) //associer la sphère au noeud ou elle se trouve
		{
			n->coverSpheres.push_back(newSphere);
			Node* temp = n->parent;
			while (temp != nullptr) //mettre a jour les noeuds supérieurs
			{
				if (std::find(temp->coverSpheres.begin(), temp->coverSpheres.end(), newSphere) == temp->coverSpheres.end())
				{
					temp->coverSpheres.push_back(newSphere);
				}
				else
				{
					break;
				}
				temp = temp->parent;
			}
		}
	}

	bool change = false;
	int max_change = 5;
	do
	{
		change = false;
		for (Node* n : activeNode)
		{
			if (n->size > minSizeBlock && n->coverSpheres.size() > nbRigidPerZone) // Si trop de rigid dans la même zone, couper la zone en 8
			{
				cutNodeTree(n);
				change = true;
				max_change--;
				break;
			}
		}
	} while (change && max_change > 0);
}

void Octree::addRigid(Rigid* addSphere)
{
	CoverSphereIntern* newSphere = new CoverSphereIntern();
	CoverSphere* sphere = new CoverSphere(addSphere);
	newSphere->nodeRigids = sphere;
	allSphere.push_back(newSphere);
	for (Node* n : activeNode)
	{
		if (isOnZone(n, sphere) > 0)//associer la sphère au noeud ou elle se trouve
		{
			n->coverSpheres.push_back(newSphere);
			Node* temp = n->parent;
			while (temp != nullptr) //mettre a jour les noeuds supérieurs
			{
				if (std::find(temp->coverSpheres.begin(), temp->coverSpheres.end(), newSphere) == temp->coverSpheres.end())
				{
					temp->coverSpheres.push_back(newSphere);
				}
				else
				{
					break;
				}
				temp = temp->parent;
			}
		}
	}
	bool change = false;
	int max_change = 5;
	do
	{
		change = false;
		for (Node* n : activeNode)
		{
			if ( n->size > minSizeBlock && n->coverSpheres.size() > nbRigidPerZone) // Si trop de rigid dans la même zone
			{
				cutNodeTree(n);
				change = true;
				max_change--;
				break;
			}
		}
	} while (change && max_change > 0);
}

void Octree::eraseRigid(Rigid* removeSphere)
{
	for (std::vector<CoverSphereIntern*>::iterator it = allSphere.begin(); it < allSphere.end(); it++)//gestion de la fusion (si y'a trop peu de rigid dans une zone)
	{
		CoverSphereIntern* sphereToRemove = (*it);
		if (sphereToRemove->nodeRigids->GetRb() == removeSphere)
		{
			internRemove(sphereToRemove);
			for (Node* n : activeNode)
			{
				Node* temp = n;
				int i = 0;
				 while (temp != nullptr) //mettre a jour les noeuds supérieurs
				 {
					 auto it = std::find(temp->coverSpheres.begin(), temp->coverSpheres.end(), sphereToRemove);
					 if (it != temp->coverSpheres.end())
					 {
						 temp->coverSpheres.erase(it);
					 }
					 i++;
					 temp = temp->parent;
				 }
			}

			allSphere.erase(it);
			delete sphereToRemove->nodeRigids;
			delete sphereToRemove;
			return;
		}
	}
	
}

void Octree::internRemove(CoverSphereIntern* removeSphere){
	
	for (Node* n : activeNode)
	{
		
		Node* temp = n;
		while (temp != nullptr) //mettre a jour les noeuds supérieurs
		{
			auto tempIt = std::find(temp->coverSpheres.begin(), temp->coverSpheres.end(), removeSphere);
			if (tempIt != temp->coverSpheres.end())
			{
				temp->coverSpheres.erase(tempIt);

			}
			else
			{
				break;
			}
			temp = temp->parent;
		}
			

	}
	bool change = false;
	int max_change = 5;
	do
	{
		change = false;
		for (Node* n : activeNode) //gestion de la fusion (si y'a trop peu de rigid dans une zone)
		{
			if (n != nullptr && n->parent != nullptr && countRigidInZone(n->parent) < nbRigidPerZone)
			{
				joinNodeTree(n->parent);
				change = true;
				max_change--;
				break;
			}
		}
	} while (change && max_change > 0);
}



std::vector<RigidPair*> Octree::allPossibleCollision()
{
	std::vector<RigidPair*> allCollision;

	std::vector<RigidPair*> boxBetweenTwoSameZone;

	std::unordered_map<CoverSphereIntern*, int> countZone;
	bool change = false;
	int max_change = 5;
	do {
		change = false;
		for (Node* currentNode : activeNode) // si un rigidBody change de zone, mettre a jour l'arbre
		{
			for (int i = 0; i < currentNode->coverSpheres.size(); i++)
			{
				CoverSphere* s1 = currentNode->coverSpheres[i]->nodeRigids;
				int testZone = isOnZone(currentNode, s1);
				if (testZone == 0)
				{

					changeZone(currentNode->coverSpheres[i]);
					change = true;
					max_change--;
					break;

				}
				else if (testZone == 2)
				{
					int num = compareLastPosValue(currentNode, s1);
					if (currentNode->result[s1] != num)
					{
						currentNode->result[s1] = num;
						changeZone(currentNode->coverSpheres[i]);
						change = true;
						max_change--;
						break;
					}
					
				}
				else
				{
					currentNode->result[s1] = 0;
				}
			}
			if (change)
			{
				break;
			}
		}
	} while (change && max_change > 0);
	for (Node* currentNode : activeNode) //Recolter les collisions sur la même zone
	{
		for (int i = 0; i < currentNode->coverSpheres.size(); i++)
		{
			CoverSphereIntern *s1 = currentNode->coverSpheres[i];
			for (int j = i + 1; j < currentNode->coverSpheres.size(); j++)
			{
				CoverSphereIntern* s2 = currentNode->coverSpheres[j];
				if (std::find(s1->alreadyConsiderCollision.begin(), s1->alreadyConsiderCollision.end(), s2) == s1->alreadyConsiderCollision.end()) //enlever les doublons
				{
					RigidPair* r = new RigidPair();
					r->rigid1 = s1->nodeRigids->GetRb();
					r->rigid2 = s2->nodeRigids->GetRb();
					allCollision.push_back(r);
					
					s1->alreadyConsiderCollision.push_back(s2);
					s2->alreadyConsiderCollision.push_back(s1);
				}
			}
		}
	}
	for (int i = 0; i < allSphere.size(); i++) //clear les collisions déjà prit en compte, pour la prochaine frame
	{
		allSphere[i]->alreadyConsiderCollision.clear();
	}
	return allCollision;
}

void Octree::draw()
{
	if (enableDrawing)
	{
		int size = activeNode.size();
		ofEnableAlphaBlending();
		for (int i = 0; i < size; i++)
		{
			int numR = 255 - (i * 200) % 256;
			int numG = 255 - (i * 200 * (i * 200 / 256)) % 256;
			int numB = 255 - (i * 200 * (i * 200 / (256 * 256))) % 256;

			ofSetColor(numR, numG, numB, 20);
			ofDrawBox(activeNode[i]->center.toVec3(), activeNode[i]->size * 2);

		}
		ofDisableAlphaBlending();
		ofSetColor(ofColor::white);
	}
	

}

void Octree::changeEnableDrawing()
{
	enableDrawing = !enableDrawing;
}

void Octree::freePossibleCollision(std::vector<RigidPair*> &allrigid, std::vector<BoxPair*>& allbox)
{
	auto it = allrigid.begin();
	while (!allrigid.empty())
	{
		RigidPair* value = allrigid.back();
		allrigid.pop_back();
		delete value;
	}

	while (!allbox.empty())
	{
		BoxPair* value = allbox.back();
		allbox.pop_back();
		delete value;
	}
	
}
