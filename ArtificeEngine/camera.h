#pragma once
#include "node.h"
#include "node2d.h"


class camera : public node2d
{
public:
	camera();
	~camera();

	void move(int key, int action) override;
};

