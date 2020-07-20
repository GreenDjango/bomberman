/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ImageCreator
*/

#ifndef IMAGECREATOR_HPP_
#define IMAGECREATOR_HPP_

#include <irrlicht/irrlicht.h>
#include <functional>

class ImageCreator
{
public:
    ImageCreator() {};
    ~ImageCreator() {};
    enum Alignment {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER_CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };
    
    static irr::gui::IGUIImage *newImage(irr::gui::IGUIEnvironment *guienv, irr::video::ITexture* texture,
        const irr::core::vector2di &pos, const irr::core::vector2df &size = {1, 1})
    {
        irr::s32 width = texture->getSize().Width * size.X;
        irr::s32 height = texture->getSize().Height * size.Y;
        irr::gui::IGUIImage *image = guienv->addImage(
            irr::core::recti({pos.X, pos.Y},
            irr::core::dimension2di{ std::ref(width), std::ref(height) }));
        image->setImage(texture);
        image->setScaleImage(true);
        return image;
    };
    static irr::gui::IGUIImage *newImage(irr::gui::IGUIEnvironment *guienv, irr::video::ITexture* texture,
        const irr::core::recti &zone, Alignment align = TOP_LEFT, irr::f32 size = 1)
    {
        irr::s32 width = texture->getSize().Width * size;
        irr::s32 height = texture->getSize().Height * size;
        irr::core::vector2di pos = getAlignPos(align, zone, width, height);
 
        irr::gui::IGUIImage *image = guienv->addImage(
            irr::core::recti({pos.X, pos.Y},
            irr::core::dimension2di{ std::ref(width), std::ref(height) }));
        image->setImage(texture);
        image->setScaleImage(true);
        return image;
    };
    static irr::gui::IGUIButton *newButton(irr::gui::IGUIEnvironment *guienv, irr::video::ITexture* texture,
        const irr::core::vector2di &pos, const irr::core::vector2df &size = {1, 1})
    {
        irr::s32 width = texture->getSize().Width * size.X;
        irr::s32 height = texture->getSize().Height * size.Y;
        irr::gui::IGUIButton *button = guienv->addButton(
            irr::core::recti({pos.X, pos.Y},
            irr::core::dimension2di{ std::ref(width), std::ref(height) }));
        button->setImage(texture);
        button->setScaleImage(true);
        button->setUseAlphaChannel(true);
        button->setDrawBorder(false);
        return button;
    };
    static irr::gui::IGUIButton *newButton(irr::gui::IGUIEnvironment *guienv, irr::video::ITexture* texture,
        const irr::core::recti &zone, Alignment align = TOP_LEFT, irr::f32 size = 1)
    {
        irr::s32 width = texture->getSize().Width * size;
        irr::s32 height = texture->getSize().Height * size;
        irr::core::vector2di pos = getAlignPos(align, zone, width, height);
 
        irr::gui::IGUIButton *button = guienv->addButton(
            irr::core::recti({pos.X, pos.Y},
            irr::core::dimension2di{ std::ref(width), std::ref(height) }));
        button->setImage(texture);
        button->setScaleImage(true);
        button->setUseAlphaChannel(true);
        button->setDrawBorder(false);
        return button;
    };
    private:
        static irr::core::vector2di getAlignPos(Alignment align, const irr::core::recti &zone, irr::s32 textureWidth, irr::s32 textureHeight) {
            irr::s32 x = 0;
            irr::s32 y = 0;
            irr::core::vector2di zoneUp = zone.UpperLeftCorner;
            irr::core::vector2di zoneLower = zone.LowerRightCorner;

            if (align == Alignment::TOP_CENTER || align == Alignment::CENTER_CENTER || align == Alignment::BOTTOM_CENTER)
            x = ((zoneLower.X - zoneUp.X) / 2) - (textureWidth / 2);
            else if (align == Alignment::TOP_RIGHT || align == Alignment::CENTER_RIGHT || align == Alignment::BOTTOM_RIGHT)
                x = (zoneLower.X - textureWidth) - zoneUp.X;
            x = x < 0 ? 0 : x;
            x = zoneUp.X + x;
            if (align == Alignment::CENTER_LEFT || align == Alignment::CENTER_CENTER || align == Alignment::CENTER_RIGHT)
                y = ((zoneLower.Y - zoneUp.Y) / 2) - (textureHeight / 2);
            else if (align == Alignment::BOTTOM_LEFT || align == Alignment::BOTTOM_CENTER || align == Alignment::BOTTOM_RIGHT)
                y = (zoneLower.Y - textureHeight) - zoneUp.Y;
            y = y < 0 ? 0 : y;
            y = zoneUp.Y + y;
            return {x, y};
        };
};

#endif /* !IMAGECREATOR_HPP_ */
