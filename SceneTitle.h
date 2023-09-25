#pragma once

#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle(){}

	virtual ~SceneTitle() {}

	virtual void init();
	virtual void end() {}

	virtual SceneBase* update() override;
	virtual void draw();

private:


};
