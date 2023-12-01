#include "Octree.h"

int Octree::countRigidInZone(Node* node)
{
	if (node->nextNodes[0] = nullptr)
	{
		return node->coverSpheres.size();
	}

	std::vector<CoverSphereIntern*> saveSphere;

	for (int i = 0; i < 8; i++)
	{
		for (CoverSphereIntern* sphere : node->nextNodes[i]->coverSpheres)
		{
			if (std::find(saveSphere.begin(), saveSphere.end(), sphere) != saveSphere.end())
			{
				saveSphere.push_back(sphere);
			}
		}
	}
	return saveSphere.size();
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
		printf("Error, node not found on activeNode for cut\n");
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
				newNode->coverSpheres.push_back(cutNode->coverSpheres[j]);
			}
		}
		cutNode->nextNodes[i] = newNode;
		activeNode.push_back(newNode);
	}

	cutNode->coverSpheres.clear(); //clear le parent

}

void Octree::joinNodeTree(Node* parentJoinedNode)
{
	if (parentJoinedNode->nextNodes[0] == nullptr)
	{
		printf("Error, use function on not active node\n");
		return;
	}
	else if (parentJoinedNode->nextNodes[0]->nextNodes[0] != nullptr)
	{
		printf("Too high in the tree\n");
		return;
	}

	parentJoinedNode->coverSpheres.clear();

	for (int i = 0; i < 8; i++)
	{
		for (CoverSphereIntern* sphere : parentJoinedNode->nextNodes[i]->coverSpheres)
		{
			if (std::find(parentJoinedNode->coverSpheres.begin(), parentJoinedNode->coverSpheres.end(), sphere) != parentJoinedNode->coverSpheres.end())
			{
				parentJoinedNode->coverSpheres.push_back(sphere);
			}
		}
		parentJoinedNode->nextNodes[i]->coverSpheres.clear();

		auto it = find(activeNode.begin(), activeNode.end(),
			parentJoinedNode->nextNodes[i]);

		if (it != activeNode.end()) {
			activeNode.erase(it);
		}
		else
		{
			printf("Error, node not found on activeNode for join\n");
			return;
		}
		delete parentJoinedNode->nextNodes[i];
		parentJoinedNode->nextNodes[i] = nullptr;
	}
}

void Octree::changeZone(CoverSphere* s)
{
	removeRigid(s);
	addRigid(s);
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
	else if (projx < node->size + sphere->GetRadius() || projy < node->size + sphere->GetRadius() || projz < node->size + sphere->GetRadius())
	{
		return 2;  // sphere between two or more zone
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

void Octree::addRigid(CoverSphere* addSphere)
{
	CoverSphereIntern* newSphere = new CoverSphereIntern();
	allSphere.push_back(newSphere);
	for (Node* n : activeNode)
	{
		if (isOnZone(n, addSphere) > 0)
		{
			newSphere->nodeRigids = addSphere;
			n->coverSpheres.push_back(newSphere);
		}
	}

	std::vector<Node*> copy(activeNode);
	for (Node* n : copy)
	{
		if (n->coverSpheres.size() > nbRigidPerZone) // Si trop de rigid dans la même zone
		{
			cutNodeTree(n);
		}
		else if (countRigidInZone(n->parent) <= nbRigidPerZone)  // Si trop peu de rigid dans le parent
		{
			joinNodeTree(n);
		}
	}
}

void Octree::eraseRigid(CoverSphere* removeSphere)
{
	removeRigid(removeSphere);
	std::vector<Node*> copy(activeNode);
	for (Node* n : copy)
	{
		if (countRigidInZone(n->parent) <= 4)
		{
			joinNodeTree(n);
		}
	}
}

void Octree::removeRigid(CoverSphere* removeSphere){
	
	for (Node* n : activeNode)
	{
		for (std::vector<CoverSphereIntern*>::iterator it = n->coverSpheres.begin(); it < n->coverSpheres.begin();)
		{
			if ((*it)->nodeRigids == removeSphere)
			{
				n->coverSpheres.erase(it);
			}
			else
			{
				it++;
			}
		}
		
	}

	for (std::vector<CoverSphereIntern*>::iterator it = allSphere.begin(); it < allSphere.begin();)
	{
		if ((*it)->nodeRigids == removeSphere)
		{
			allSphere.erase(it);
			delete* it;
			return;
		}

	}
	printf("There is a problem sphere don't find in allSphere");
}



std::vector<RigidPair*> Octree::allPossibleCollision()
{
	std::vector<RigidPair*> allCollision;

	std::vector<RigidPair*> boxBetweenTwoSameZone;

	std::unordered_map<CoverSphereIntern*, int> countZone;

	for (Node* currentNode : activeNode) // si un rigidBody est sortie de la zone, mettre a jour l'arbre
	{
		for (int i = 0; i < currentNode->coverSpheres.size(); i++)
		{
			CoverSphere* s1 = currentNode->coverSpheres[i]->nodeRigids;
			int testZone = isOnZone(currentNode, s1);
			if (testZone == 0 || testZone == 2)
			{
				changeZone(s1);
			}
		}
	}

	for (Node* currentNode : activeNode) //Recolter les collisions sur la même zone
	{
		for (int i = 0; i < currentNode->coverSpheres.size(); i++)
		{
			CoverSphereIntern *s1 = currentNode->coverSpheres[i];

			for (int j = i + 1; currentNode->coverSpheres.size(); j++)
			{
				CoverSphereIntern* s2 = currentNode->coverSpheres[j];
				if (std::find(s1->alreadyConsiderCollision.begin(), s1->alreadyConsiderCollision.end(), s2) != s1->alreadyConsiderCollision.end()) //enlever les doublons
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
