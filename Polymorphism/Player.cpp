#include "Player.h"
#include <iostream>

Player::Player()
{
	std::cout << __FUNCTION__ << std::endl;
}

Player::~Player()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Player::Attack()
{
	// ������ ������ �θ��� Attack() �Լ��� ȣ���ϰ� �ʹٸ�
	__super::Attack();
	std::cout << __FUNCTION__ << std::endl;
}
