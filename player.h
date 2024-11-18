#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "player_id.h"

#include <graphics.h>

class Player
{
public:
	Player()
	{
		current_animation = &animation_idle_right;
	}
	~Player() = default;

	virtual void on_update(int delta)
	{
		int direction = is_right_key_down - is_left_key_down;

		if (direction != 0)
		{
			is_facing_right = direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
		}
		else
		{
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
		}

		current_animation->on_update(delta);
	}

	virtual void on_draw(const Camera& camera)
	{
		current_animation->on_draw(camera, (int)position.x, (int)position.y);
	}

	virtual void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
					// 'A'
				case 0x41:
					is_left_key_down = true;
					break;
					// 'D'
				case 0x44:
					is_right_key_down = true;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
					// '←'
				case VK_LEFT:
					is_left_key_down = true;
					break;
					// '→'
				case VK_RIGHT:
					is_right_key_down = true;
					break;
				}
				break;
			}
			break;
		case WM_KEYUP:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
					// 'A'
				case 0x41:
					is_left_key_down = false;
					break;
					// 'D'
				case 0x44:
					is_right_key_down = false;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
					// '←'
				case VK_LEFT:
					is_left_key_down = false;
					break;
					// '→'
				case VK_RIGHT:
					is_right_key_down = false;
					break;
				}
				break;
			}
			break;
		}
	}

	void set_id(PlayerID id)
	{
		this->id = id;
	}

	void set_position(float x, float y)
	{
		position.x = x, position.y = y;
	}

protected:
	Vector2 position;                       // 角色位置

	Animation animation_idle_left;          // 朝向左的默认动画
	Animation animation_idle_right;         // 朝向右的默认动画
	Animation animation_run_left;           // 朝向左的奔跑动画
	Animation animation_run_right;          // 朝向右的奔跑动画

	Animation* current_animation = nullptr; // 当前正在播放的动画

	PlayerID id = PlayerID::P1;             // 玩家序号 ID

	bool is_left_key_down = false;          // 向左移动按键是否按下
	bool is_right_key_down = false;         // 向右移动按键是否按下

	bool is_facing_right = true;            // 角色是否朝向右侧
};


#endif // !_PLAYER_H_
