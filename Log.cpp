#include "Log.h"
#include "Player.h"

#include <random>

Log::Log(Player player):
    m_pPlayer(player),
    m_pos(VGet(0,0,-1000)),
    m_isExist(false),
    m_randomNum(0)
{
}

void Log::init()
{
    //初期化時は存在する
    m_isExist = true;
}

void Log::update()
{


}

void Log::draw()
{
    //(仮)ステージが生成されたときにランダムな位置に複数個生成する
    if (!m_isExist) return;

    int leftX = m_pos.x - kWidth + m_randomNum;
    int rightX = m_pos.x + kWidth + m_randomNum;
    DrawCapsule3D(VGet(leftX, kHeight, m_pos.z), VGet(rightX, kHeight, m_pos.z), kRadius, 30, 0x734e30, 0x734e30, true);
    
}

void Log::onDamege()
{
    m_isExist = false;
}

void Log::create()
{
    //ランダム計算
    std::random_device rd;
    std::mt19937 mt(rd());
    //-50.0f～50.0f
    std::uniform_real_distribution <float> rdt(-1000.0f, 1000.0f);

    m_randomNum = rdt(mt);

    m_isExist = true;
}

bool Log::isCol(Player& player)
{
    if (!m_isExist) return false;

    if (player.getLeft() > getRight()) return false;
    if (player.getRight() < getLeft()) return false;
    if (player.getTop() < getBottom()) return false;
    if (player.getBottom() > getTop()) return false;
    if (player.getFar() > getNear()) return false;
    if (player.getNear() < getFar()) return false;

    return true;
}
