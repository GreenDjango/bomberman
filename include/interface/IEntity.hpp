/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

class IEntity
{
public:
    enum class EType {
        UNKNOWN,
        PLAYER,
        ROOM,
        ITEM,
        MOB,
        BLOCK,
        BOMB
    };
protected:
    EType _type;
    bool _alive;
    bool _needFree;
    void *_objAddr;
public:
    IEntity(EType type, void *objAddr);
    virtual ~IEntity() { };
    // Getter
    bool isAlive() const { return _alive; };
    bool needFree() const { return _needFree; };
    EType getType() const { return _type; };
    void *getObj() { return _objAddr; };
    // --
    void setAlive(bool v) { _alive = v; };
};

#endif /* !IENTITY_HPP_ */
