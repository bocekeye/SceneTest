#include "Ring.h"
#include "Model.h"
#include "Player.h"

#include <random>

namespace
{
    //�t�@�C����
    const char* const kFileName = "data/ring.mv1";
}

Ring::Ring(Player& player):
    m_pPlayer(player),
    m_pos(VGet(0.0f, 1000.0f, -1500.0f)),
    m_isExist(false),
    m_radius(0),
    m_angle(0)
{
    //3D���f���̐���
    m_pModel = std::make_shared<Model>(kFileName);

}

void Ring::init()
{
    m_isExist = true;
}

void Ring::update()
{
    //�O�p�֐����g�p���A�~�̈ʒu������o��
    //m_angle += 10.0f;
    m_radius = 100.0f;
    float rad = DX_PI_F * m_angle / 180.0f;

   // m_pos.x = cos(rad) * m_radius + m_pos.x;
  //  m_pos.y = sin(rad) * m_radius + m_pos.y;

    if (m_pPlayer.getNear() < m_pos.z)
    {
        m_isExist = false;
    }
    
    //MATRIX angle = MGetRotY(m_angle);

    m_pModel->setPos(m_pos);
    m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));
}

void Ring::draw()
{
    if (!m_isExist) return;


    m_pModel->draw();
   
    DrawString(850,20,"�����O",0xffffff);
    DrawFormatString(850, 40, 0xffffff, "%f", m_angle);
}

void Ring::onDamege()
{
}

void Ring::create()
{
    //�����_���v�Z
    std::random_device rd;
    std::mt19937 mt(rd());
    //-50.0f�`50.0f
    std::uniform_real_distribution <float> rdtX(-2000.0f, 2000.0f); //X��
    std::uniform_real_distribution <float> rdtY(-400.0f, 300.0f);   //Y��
    
    m_pos.x = rdtX(mt);
    m_pos.y += rdtY(mt);
    m_pos.z = m_pPlayer.getPos().z - 3500.0f;

    //�v���C���[�������Ă�������ɐ�������(��)
    m_angle = m_pPlayer.getAngle();

    m_isExist = true;   
}

bool Ring::isCol(Player& player)
{


    return false;
}
