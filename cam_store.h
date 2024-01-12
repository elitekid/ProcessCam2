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

class cam_store
{
public:
	cam_store();
	~cam_store();
	void set_camera_geometry();
	void drawCam();
private:
	gBuffers cam_buffers;
	shader cam_shader;
	SettingManager settingManager;
};
