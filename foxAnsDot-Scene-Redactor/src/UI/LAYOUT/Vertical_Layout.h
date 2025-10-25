#pragma once
#include "base/Layout.h"
class Vertical_Layout : public Layout
{
private:
	void layout_members() override;
	float vertical_free_space;
public:
	Vertical_Layout();
	~Vertical_Layout();
};

