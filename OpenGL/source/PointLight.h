#pragma once
#include "Component.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace glm;
using namespace aie;

/*
* class PointLight
* child class of Component
*
* a component that takes various G-Pass buffers and creates
* colour for a light with a specific location and falloff in the L-Pass
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class PointLight : public Component
{
public:

	ShaderProgram * lightShader = nullptr;

	Texture * positionBuffer = nullptr;
	Texture * normalBuffer = nullptr;
	Texture * specularBuffer = nullptr;
	Texture * specularPowerBuffer = nullptr;

	vec3 position;
	float radius;
	vec3 diffuse;
	vec3 specular;

	//amount of triangles in the mesh
	unsigned int triCount = 0;

	//handles for the gpu
	unsigned int vao = 0; //vertex array object, temporary array to copy into the vbo
	unsigned int vbo = 0; //vertex buffer objects, where vertex data is read into shaders
	unsigned int ibo = 0; //index buffer object

	/*
	* PointLight()
	* constructor, assigns normal buffer
	*
	* @param ShaderProgram* lightShader - shader that renders the light
	* @param Texture* positionBuffer - positional information
	* @param Texture* normalBuffer - normal information
	* @param Texture* specularBuffer - specular colour information
	* @param Texture* specularPowerBuffer - the specular power
	*/
	PointLight(ShaderProgram* lightShader, Texture* positionBuffer, Texture* normalBuffer, Texture* specularBuffer, Texture* specularPowerBuffer);

	/*
	* ~DirectionalLight()
	* destructor, deinitialises all vertex arrays and other buffers
	*/
	~PointLight();

	/*
	* start
	* overrides Component's start()
	*
	* called when the object is created
	*
	* @returns void
	*/
	void start() override;

	/*
	* initialiseCube
	*
	* sets up the vertex buffer and normal buffers to render a cube
	* that encloses the radius the light effects
	*
	* @returns void
	*/
	void initialiseCube();

	/*
	* draw
	* overrides Component's draw()
	*
	* called once per frame after the update loop
	*
	* @param Camera* camera - the pov to render the component
	* @param ERenderType renderType - the type of pass to perform on the fragment shader
	* @returns void
	*/
	void draw(Camera* camera, ERenderType renderType) override;
};