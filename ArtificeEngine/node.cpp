#include "node.h"

void node::call(std::string referrable, bool forChildren)
{
	//Run call on children
	if (forChildren)
	{
		for (auto& i : *get_children())
		{
			i->call(referrable);
		}
	}
	

	auto it = callMap.find(referrable);
	if (it != callMap.end())
	{
		//Key Found
		//Call it
		(this->*callMap[referrable])();
		 
	}
}

void node::callInput(int key, int action, bool forChildren)
{
	//Run call on children
	if (forChildren)
	{
		for (auto& i : *get_children())
		{
			i->callInput(key,action);
		}
	}


	auto it = ActionMap.find(key);
	if (it != ActionMap.end())
	{
		//Key Found
		//Call it
		(this->*ActionMap[key])(key,action);

	}
}

void node::add_child(node* nRef)
{
	std::vector<node*>::iterator it;
	it = std::find(children.begin(), children.end(),nRef);
	if (it == children.end()) //WIP NEED TO CHECK CHILD HAS NO PARENT ALREADY
	{
		//Child not in children
		children.push_back(nRef);
		nRef->set_parent(this);
	}
}

std::vector<node*>* node::get_children()
{
	//Returns reference to children
	return &children;
}

node* node::get_parent()
{
	return parent;
}

void node::set_parent(node* pRef)
{
	parent = pRef;
}

void node::update()
{
}

void node::render()
{
}

void node::move(int key, int action)
{
}

