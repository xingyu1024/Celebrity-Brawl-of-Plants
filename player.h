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
					// '��'
				case VK_LEFT:
					is_left_key_down = true;
					break;
					// '��'
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
					// '��'
				case VK_LEFT:
					is_left_key_down = false;
					break;
					// '��'
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
	Vector2 position;                       // ��ɫλ��

	Animation animation_idle_left;          // �������Ĭ�϶���
	Animation animation_idle_right;         // �����ҵ�Ĭ�϶���
	Animation animation_run_left;           // ������ı��ܶ���
	Animation animation_run_right;          // �����ҵı��ܶ���

	Animation* current_animation = nullptr; // ��ǰ���ڲ��ŵĶ���

	PlayerID id = PlayerID::P1;             // ������ ID

	bool is_left_key_down = false;          // �����ƶ������Ƿ���
	bool is_right_key_down = false;         // �����ƶ������Ƿ���

	bool is_facing_right = true;            // ��ɫ�Ƿ����Ҳ�
};


#endif // !_PLAYER_H_
