#pragma once
#include <DxLib.h>
#include <memory>

class Player;

class Ring
{
public:
	Ring(Player& player);
	virtual ~Ring(){}

	void init();
	void update();
	void draw();

	//�ւ����̈ʒu���擾����
	VECTOR getPos() const { return m_pos; }

	//�_���[�W���󂯂�
	void onDamege();

	//�����蔻��
	bool isCol(Player& player);

	//���f���̑傫���̎擾�p
	float getRight() { return m_pos.x + 23.0f; }
	float getLeft() { return m_pos.x - 23.0f; }
	float getTop() { return m_pos.y + 66.0f; }
	float getBottom() { return m_pos.y - 39.0f; }
	float getFar() { return m_pos.z + 200.0f; }
	float getNear() { return m_pos.z - 120.0f; }

private:

	//���W
	VECTOR m_pos;
	//�Q�Ɠn��
	Player& m_pPlayer;
	//���݂��邩
	bool m_isExist;
};

