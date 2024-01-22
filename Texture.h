// Copyright 2024 elitekid

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();
	void Load(int width, int height);
	void Update(unsigned char* camera_data);
	void Bind(unsigned int slot = 0) const;
	void UnBind();

	inline int GetWidth() const { return texture_width_; }
	inline int GetHeight() const { return texture_height_; }
private:
	unsigned int texture_id_;
	unsigned char* local_buffer_;
	int texture_width_, texture_height_;
};

#endif  // TEXTURE_H_