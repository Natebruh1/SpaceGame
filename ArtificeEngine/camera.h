#pragma once
#include "node.h"
#include "node2d.h"


class camera : public node2d
{
public:
	camera();
	~camera();

	void input(int key, int scancode, int action, int mods) override;
};

