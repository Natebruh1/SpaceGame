#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <glad/glad.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h> 
#include "globals.h"
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
	typedef std::map<int, void (node::*)(int key, int Action)> InputMap;


	void call(std::string referrable, bool forChildren=true);
	void callInput(int key, int action, bool forChildren = true);
	
	//Adds a node* to the tree
	void add_child(node* nRef);
	//Returns reference to children
	std::vector<node*>* get_children();
	node* get_parent();
	void set_parent(node* pRef);
	virtual void update();



	node() {}
	~node() {};
protected:
	FunctionMap callMap{ {"render",&node::render},{"update",&node::update} };
	InputMap ActionMap;
private:
	//Private Information
	std::vector<node*> children;
	node* parent;

	//Abstract
public:
	virtual void render();
	

public:
	//Calls / InputCalls
	virtual void move(int key, int action);
	
};

