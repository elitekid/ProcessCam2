#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();
	void load(int width, int height);
	void update(unsigned char* cameraData);
	void bind(unsigned int slot = 0) const;
	void unBind();

	inline int GetWidth() const { return texture_width; }
	inline int GetHeight() const { return texture_height; }
private:
	unsigned int texture_id;
	unsigned char* local_buffer;
	int texture_width, texture_height;
};

