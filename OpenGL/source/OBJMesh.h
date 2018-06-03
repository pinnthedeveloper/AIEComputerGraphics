#pragma once
#include "Component.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <vector>


#include "Shader.h"
#include "Texture.h"

namespace aie {

// a simple triangle mesh wrapper
class OBJMesh : public Component
{
public:

	//pointer to the GPU bound code to render the mesh
	ShaderProgram * shaderPipe;

	int useTexture = false;

	// a vertex structure for obj files
	struct Vertex 
	{
		glm::vec4 position; // added to attrib location 0
		glm::vec4 normal;	// added to attrib location 1
		glm::vec2 texcoord;	// added to attrib location 2

							// normal-mapping data
		glm::vec4 tangent;	// added to attrib location 3
	};

	// a basic material
	class Material 
	{
	public:

		Material() : ambient(1), diffuse(1), specular(0), emissive(0), specularPower(1), opacity(1) {}
		~Material() {}

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 emissive;

		float specularPower;
		float opacity;

		Texture diffuseTexture;				// bound slot 0
		Texture alphaTexture;				// bound slot 1
		Texture ambientTexture;				// bound slot 2
		Texture specularTexture;			// bound slot 3
		Texture specularHighlightTexture;	// bound slot 4
		Texture normalTexture;				// bound slot 5
		Texture displacementTexture;		// bound slot 6
	};

	OBJMesh(ShaderProgram* inShaderPipe);
	~OBJMesh();

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
	* update
	* overrides Component's update(float deltaTime)
	*
	* called once per frame
	*
	* @param float deltaTime - amount of time passed since the last frame
	* @returns void
	*/
	void update(float deltaTime) override {}

	// will fail if a mesh has already been loaded in to this instance
	bool load(const char* filename, bool loadTextures = true, bool flipTextureV = false);

	// allow option to draw as patches for tessellation
	void draw(mat4 viewProjection) override;

	// access to the filename that was loaded
	const std::string& getFilename() const { return m_filename; }

	// material access
	size_t getMaterialCount() const { return m_materials.size();  }
	Material& getMaterial(size_t index) { return m_materials[index];  }

private:

	void calculateTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	struct MeshChunk {
		unsigned int	vao, vbo, ibo;
		unsigned int	indexCount;
		int				materialID;
	};

	std::string				m_filename;
	std::vector<MeshChunk>	m_meshChunks;
	std::vector<Material>	m_materials;
};

} // namespace aie