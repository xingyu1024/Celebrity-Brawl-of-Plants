#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "scene.h"
#include "atlas.h"
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
		animation_peashooter_run_right.set_loop(false);
		animation_peashooter_run_right.set_callback(
			[]()
			{
				scene_manager.switch_to(SceneManager::SceneType::Game);
			}
		);
	}

	void on_update(int delta) 
	{
		animation_peashooter_run_right.on_update(delta);
	}

	void on_draw() 
	{
		animation_peashooter_run_right.on_draw(100, 100);
	}

	void on_input(const ExMessage& msg) 
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.switch_to(SceneManager::SceneType::Game);
		}
	}

	void on_exit() 
	{
		std::cout << "Ö÷²Ëµ¥ÍË³ö" << std::endl;
	}

private:
	Animation animation_peashooter_run_right;
};


#endif // !_MENU_SCENE_H_
