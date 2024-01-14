#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h> 
#include "ResourceManager.h"
// Welcome to the default class
// everything displayed in the game tree comes from here
// node is essentially a meta wrapper object
// it doesn't have a purpose except encompassing all nodewide methods (including some abstract ones like render).
// 


// Class Tree : Node
//				 ^^






class node
{
	//Non-Abstract
public:
	typedef std::map<std::string, void (node::*)()> FunctionMap;


	void call(std::string referrable, bool forChildren=true);
	
	//Adds a node* to the tree
	void add_child(node* nRef);
	//Returns reference to children
	std::vector<node*>* get_children();
	node* get_parent();
	void set_parent(node* pRef);
	virtual void update();

protected:
	FunctionMap callMap{ {"render",&node::render},{"update",&node::update} };
private:
	//Private Information
	std::vector<node*> children;
	node* parent;

	//Abstract
public:
	virtual void render() = 0;
	
};

