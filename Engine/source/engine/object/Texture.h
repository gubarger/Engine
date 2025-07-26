#pragma once

/**
		--------------------------------------
		@the implementation is not working yet
		--------------------------------------
*/

#include <glad/glad.h>
#include <string>

class Texture {
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	GLuint GetID() const { return m_textureID; }

private:
	GLuint m_textureID = 0;

	int m_width = 0;
	int m_height = 0;

};