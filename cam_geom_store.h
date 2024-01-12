#pragma once
#include "gBuffers.h"
#include "shader.h"
#include "SettingManager.h"
#include "texture.h"
#include <vector>

class cam_geom_store
{
public:
	cam_geom_store();
	~cam_geom_store();
	void set_camera_geometry(int cols, int rows);
	void drawCam(unsigned char* cameraData);
	void bind();
	void unBind();
private:
	gBuffers cam_buffers;
	shader cam_shader;
	Texture cam_texture;
	SettingManager settingManager;
};
