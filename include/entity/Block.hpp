/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Block
*/

#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "interface/IEntityComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "class/ICollision.hpp"

class Block : public virtual IEntityComponent
, public GraphicsComponent
, public TransformComponent
, public ICollision
{
private:
    char _type;
    irr::core::vector2d<irr::u32> _pos;
    int _corner;
    int _border;
public:
    Block(char type, irr::core::vector2d<irr::u32> pos, irr::scene::ISceneManager *smgr, int corner = -1, int border = -1);
    ~Block() { };
    char getBlockType() const { return _type; };
    const irr::core::vector2d<irr::u32> get2DPos() const { return _pos; };
    int getCorner() const { return _corner; };
    int getBorder() const { return _border; };
    void explose();
    void setType(char type) { _type = type; };
    void update(char type);
};

#endif /* !BLOCK_HPP_ */
