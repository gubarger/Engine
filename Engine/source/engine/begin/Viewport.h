#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include "Scene.h"

class Viewport {
public:
    Viewport() : m_width(0), m_height(0) {}
    ~Viewport();

    void RenderScene(const Scene& scene, Shader& shader3D, Shader& shader2D);
    void Initialize(int width, int height);
    
    void Resize(int width, int height);

    void BeginFrame();
    void EndFrame();

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

public:
	unsigned int GetTextureID() const { return m_texture; }
	ImVec2 GetSize() const { return m_size; }

private:
	unsigned int m_fbo = 0;       // Framebuffer Object
	unsigned int m_texture = 0;    // Target rendering texture
	unsigned int m_rbo = 0;        // Renderbuffer Object (for depth)

	ImVec2 m_size = { 0, 0 };        // Current viewport size

	int m_width = 0;
	int m_height = 0;

};