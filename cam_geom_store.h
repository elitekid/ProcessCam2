#pragma once
#include "gBuffers.h"
#include "shader.h"
#include "SettingManager.h"
#include "texture.h"
#include <opencv2/opencv.hpp>

using namespace cv;

class cam_geom_store
{
public:
	cam_geom_store();
	~cam_geom_store();
	void setCameraGeometry(int cols, int rows);
	void drawCam(const Mat & frame);
	void bind();
	void unBind();
private:
	gBuffers cam_buffers;
	shader cam_shader;
	Texture cam_texture;
	SettingManager settingManager;
};
