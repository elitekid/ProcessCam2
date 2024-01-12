#pragma once
#include "gBuffers.h"
#include "shader.h"
#include "textarea.h"
#include "SettingManager.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <concurrent_vector.h>

class box_geom_store
{
public:
	box_geom_store();
	~box_geom_store();
	void set_box_geometry();
	void drawBox(unsigned char* cameraData, int numberOfBox, std::vector<float> updatedVertices);
	void bind();
	void unBind();
private:
	std::vector<float> vertices;
	gBuffers box_buffers;
	shader box_shader;
	SettingManager settingManager;
};
