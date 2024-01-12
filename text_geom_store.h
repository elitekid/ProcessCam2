#pragma once
#include "gBuffers.h"
#include "shader.h"
#include "label_text_store.h"
#include "textarea.h"
#include "SettingManager.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <concurrent_vector.h>

class text_geom_store
{
public:

	text_geom_store();
	~text_geom_store();
	void set_text_geometry();
	void add_label(std::vector<TextArea>& textAreas, float w, float h, float square);
	void delete_buffers();
	void paint_geometry();
private:
	void set_simple_triangle(float* vertices, unsigned int& vertices_count,
		unsigned int* indices, unsigned int& indices_count);
	gBuffers tri_buffers;
	label_text_store all_labels;

	shader tri_shader;
	shader text_shader;

	SettingManager settingManager;
};
