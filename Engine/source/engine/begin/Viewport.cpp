#include <glad/glad.h>
#include "Viewport.h"

Viewport::~Viewport() {
	if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
	if (m_texture) glDeleteTextures(1, &m_texture);
	if (m_rbo) glDeleteRenderbuffers(1, &m_rbo);
}