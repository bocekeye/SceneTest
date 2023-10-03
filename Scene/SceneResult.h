#pragma once

#include "SceneBase.h"

class SceneManager;

class SceneResult  : public SceneBase
{
public:
	SceneResult(SceneManager& manager);
	virtual ~SceneResult(){}

	 void init();

	 void update() ;
	 void draw();

private:




};

