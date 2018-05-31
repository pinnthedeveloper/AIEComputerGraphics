#pragma once
#include <vector>

using namespace std;

//forward declaration
class GameObject;

/*
* class Scene
*
* holds a collection of GameObjects that are
* updated every frame, each GameObject's life
* depends on the scene's lifetime
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class Scene
{
public:

	//list of gameObjects in the scene
	vector<GameObject*> gameObjects;

	/*
	* Scene()
	* default constructor
	*/
	Scene() {}

	/*
	* ~Scene()
	* destructor, removes all gameObjects
	*/
	~Scene();

	/*
	* update
	*
	* called once per frame
	* updates all gameObjects
	*
	* @param float deltaTime - the amount of passed since the last frame
	* @returns void
	*/
	void update(float deltaTime);

	/*
	* draw
	*
	* called once per frame afte the update loop
	* draws all gameObjects
	*
	* @returns void
	*/
	void draw();
};