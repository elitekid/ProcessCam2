#pragma once
#include "gBuffers.h"
#include "shader.h"
#include "frame_info.h"

class box_geom_store
{
public:
	box_geom_store();
	~box_geom_store();
	void setBoxGeometry();
	void drawBox(frame_info & frameInfo);
	void bind();
	void unBind();
private:
	std::vector<float> vertices;
	gBuffers box_buffers;
	shader box_shader;
	SettingManager settingManager;
};
