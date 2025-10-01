#pragma once
#include "base/Layout.h"
class Vertical_Layout : public Layout
{
private:
	void layout_members() override;
public:
	Vertical_Layout();
	~Vertical_Layout();
};

