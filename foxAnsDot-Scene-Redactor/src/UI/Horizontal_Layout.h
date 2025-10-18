#pragma once
#include "base/Layout.h"
class Horizontal_Layout : public Layout
{
private:
	void layout_members() override;
	float horizontal_free_space; 
public:
	Horizontal_Layout();
	~Horizontal_Layout();
};

