#pragma once
class Screen
{

public:
	void makeActive();
	void endActive();
	bool getActive();
private:
	bool active = false;
};

