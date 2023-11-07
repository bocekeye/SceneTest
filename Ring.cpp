#include "Ring.h"

Ring::Ring(Player& player):
    m_pPlayer(player),
    m_pos(VGet(0.0f, 500.0f, -1000.0f))
{
}

void Ring::init()
{
}

void Ring::update()
{
}

void Ring::draw()
{
    //DrawSphere3D(m_pos,100,10,0xffff00, 0xffff00, true);

    ////ŒŠ‚ð‚ ‚¯‚é‚½‚ß‚Ì‰~
    //DrawSphere3D(m_pos, 80, 10, 0xffffff, 0xffffff, false);
}

void Ring::onDamege()
{
}

bool Ring::isCol(Player& player)
{
    return false;
}
