#include "Log.h"
#include "Player.h"

Log::Log(Player player):
    m_pPlayer(player),
    m_pos(VGet(4000,0,-500)),
    m_isExist(true)
{
}

void Log::init()
{
    //‰Šú‰»Žž‚Í‘¶Ý‚·‚é
    m_isExist = true;
}

void Log::update()
{
    if (!m_isExist) return;

}

void Log::draw()
{
    if (!m_isExist) return;
    DrawCapsule3D(VGet(-kWidth, kHeight, 0.0f), VGet(kWidth, kHeight, 0.0f), kRadius, 30, 0x734e30, 0x734e30, true);
}

void Log::onDamege()
{
    m_isExist = false;
}

bool Log::isCol(Player& player)
{
    if (!m_isExist) return false;

    if (player.getLeft() > getRight()) return false;
    if (player.getRight() < getLeft()) return false;
    if (player.getTop() < getBottom()) return false;
    if (player.getBottom() > getTop()) return false;
    if (player.getNear() > getFar()) return false;
    if (player.getFar() < getNear()) return false;

    return true;
}
