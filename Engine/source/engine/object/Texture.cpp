#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& filePath) {
	stbi_set_flip_vertically_on_load(true);

	int channels;

	unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &channels, 4);

	if (!data)
	{
		//** I haven't built a built-in console in the engine yet,
		//** so for now we'll output to the regular console.
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		return;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture::~Texture() {
	if (m_textureID) 
	{
		glDeleteTextures(1, &m_textureID);
	}
}

void Texture::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::UnBind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}