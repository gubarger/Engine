#include <glad/glad.h>
#include "../engineErrors/EngineDebug.h"
#include "Viewport.h"

Viewport::~Viewport() {
	if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
	if (m_texture) glDeleteTextures(1, &m_texture);
	if (m_rbo) glDeleteRenderbuffers(1, &m_rbo);
}

void Viewport::Initialize(int width, int height) {
	// Create textures for rendering
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// Create FBO (Framebuffer Object)
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	{
		// Attaching texture to FBO
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

		// Creating a depth buffer
		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw Debuging::Error("Framebuffer complete failed!");
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_size = ImVec2(width, height);
}

void Viewport::Resize(int width, int height) {
	if (width <= 0 || height <= 0) return;

	// Updating textures and buffers
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	m_size = ImVec2(width, height);
}

void Viewport::BeginFrame() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	
	glViewport(0, 0, m_size.x, m_size.y);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // The 3D area
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::EndFrame() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}