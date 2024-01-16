#pragma once
#include "gBuffers.h"
#include "shader.h"
#include "label_text_store.h"
#include "frame_info.h"
#include "util.h"

class text_geom_store
{
public:

	text_geom_store();
	~text_geom_store();
	void setTextGeometry();
	void deleteBuffers();
	void drawText(frame_info& frameInfo);
private:
	void addLabel();
	void setSimpleTriangle(float* vertices, unsigned int& vertices_count,
		unsigned int* indices, unsigned int& indices_count);
	gBuffers tri_buffers;
	label_text_store all_labels;

	shader tri_shader;
	shader text_shader;

	SettingManager settingManager;
	frame_info frameInfo;
};
