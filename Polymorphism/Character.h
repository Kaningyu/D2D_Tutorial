#pragma once
class Character
{
public:
	Character();
	virtual ~Character(); // �ı��ڿ��� ��? virtual�� ���ϱ�??

	int m_HP=100;	

	void Jump();
	virtual void Damage(int _Damage);
	virtual void Attack();
};

