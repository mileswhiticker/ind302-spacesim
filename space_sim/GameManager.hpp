#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

class Planet;

class GameManager
{
public:
	static Planet* GetHomePlanet();
	static void SetHomePlanet(Planet* a_pNewHomePlanet);
	//
private:
	GameManager();
	//
};

#endif	//GAME_MANAGER_HPP