#pragma once
#include "SceneBase.h"


#include <vector>
#include <memory>

class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:

};
