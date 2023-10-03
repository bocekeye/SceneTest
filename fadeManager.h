#pragma once
class fadeManager
{
public:
	fadeManager();
	virtual ~fadeManager();

	void init();
	void update();
	void draw();

private:

	int m_radius;	//”¼Œa

};

