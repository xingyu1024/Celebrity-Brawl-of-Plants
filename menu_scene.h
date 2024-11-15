#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"

#include <iostream>

extern Atlas atlas_peashooter_run_right;

extern SceneManager scene_manager;

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void on_enter()
	{
		animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_peashooter_run_right.set_interval(75);
		animation_peashooter_run_right.set_loop(true);

		timer.set_wait_time(1000);
		timer.set_one_shot(false);
		timer.set_callback(
			[]()
			{
				std::cout << "Shot!" << std::endl;
			}
		);
	}

	void on_update(int delta) 
	{
		timer.on_update(delta);
		camera.on_update(delta);
		animation_peashooter_run_right.on_update(delta);
	}

	void on_draw() 
	{
		const Vector2& pos_camera = camera.get_position();
		animation_peashooter_run_right.on_draw((int)(100-pos_camera.x), (int)(100 - pos_camera.y));
	}

	void on_input(const ExMessage& msg) 
	{
		if (msg.message == WM_KEYDOWN)
		{
			camera.shake(10, 350);
		}
	}

	void on_exit() 
	{
		std::cout << "Ö÷²Ëµ¥ÍË³ö" << std::endl;
	}

private:
	Timer timer;
	Camera camera;
	Animation animation_peashooter_run_right;
};


#endif // !_MENU_SCENE_H_
