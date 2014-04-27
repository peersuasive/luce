/************************************************************

 LDrawable.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LDrawable_inh.h"

const char LDrawable::className[] = "LDrawable";
const Luna<LDrawable>::PropertyType LDrawable::properties[] = {
    {0,0}
};
const Luna<LDrawable>::FunctionType LDrawable::methods[] = {
    //method( LDrawable, createCopy ),
    method( LDrawable, replaceColour ),
    method( LDrawable, createValueTree ),
    method( LDrawable, getParent ),
    method( LDrawable, setTransformToFit ),
    method( LDrawable, draw ),
    method( LDrawable, drawAt ),
    method( LDrawable, drawWithin ),
    method( LDrawable, setOriginWithOriginalSize ),
    method( LDrawable, getDrawableBounds ),
    {0,0}
};

const Luna<LDrawable>::StaticType LDrawable::statics[] = {
    smethod( LDrawable, createFromImageFile ),
    smethod( LDrawable, createFromSVG ),
    smethod( LDrawable, createFromImageDataStream ),
    smethod( LDrawable, createFromImageData ),
    smethod( LDrawable, parseSVGPath ),
    smethod( LDrawable, createFromValueTree ),
    smethod( LDrawable, registerDrawableTypeHandlers ),
    {0,0}
};

LDrawable::LDrawable(lua_State *Ls, Drawable* child_, const String& name_)
    : child(child_),
      LComponent(Ls, child_, name_)
{
    L = Ls;
}

LDrawable::~LDrawable() {
    if(child)
        child.release();
}

int LDrawable::s_parseSVGPath ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LPath>( new LPath(L,
        Drawable::parseSVGPath( LUA::getString(2) )
    ));
}

int LDrawable::s_createFromImageFile ( lua_State *L ) {
    // File file = *LUA::from_luce<LFile>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LDrawable>( new LDrawable(L,
    //     Drawable::createFromImageFile( file )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Drawable s_createFromImageFile( file )" );
}

int LDrawable::s_createFromSVG ( lua_State *L ) {
    // XmlElement svgDocument = *LUA::from_luce<LXmlElement>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LDrawable>( new LDrawable(L,
    //     Drawable::createFromSVG( svgDocument )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Drawable s_createFromSVG( svgDocument )" );
}

int LDrawable::s_createFromImageDataStream ( lua_State *L ) {
    // InputStream dataSource = *LUA::from_luce<LInputStream>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LDrawable>( new LDrawable(L,
    //     Drawable::createFromImageDataStream( dataSource )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Drawable s_createFromImageDataStream( dataSource )" );
}

int LDrawable::s_createFromImageData ( lua_State *L ) {
    // void* data = LUA::from_luce<Lvoid>(2); // TODO;
    // size_t numBytes = *LUA::from_luce<Lsize_t>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LDrawable>( new LDrawable(L,
    //     Drawable::createFromImageData( data, numBytes )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Drawable s_createFromImageData( data, numBytes )" );
}

int LDrawable::s_createFromValueTree ( lua_State *L ) {
    // ValueTree tree = *LUA::from_luce<LValueTree>(2); // TODO;
    // ComponentBuilder::ImageProvider* imageProvider = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LDrawable>( new LDrawable(L,
    //     Drawable::createFromValueTree( tree, imageProvider )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Drawable s_createFromValueTree( tree, imageProvider )" );
}

int LDrawable::s_registerDrawableTypeHandlers ( lua_State* ) {
    // ComponentBuilder componentBuilder = *LUA::from_luce<LComponentBuilder>(2); // TODO;
    // Drawable::registerDrawableTypeHandlers( componentBuilder );
    // return 0;
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "void s_registerDrawableTypeHandlers( componentBuilder )" );
}


// NO: each child its copy method
//int LDrawable::createCopy ( lua_State *L ) {
//    return LUA::storeAndReturnUserdata<LDrawable>( new LDrawable(L,
//        child->createCopy()
//    ));
//}

int LDrawable::replaceColour ( lua_State* ) {
    Colour originalColour = LUCE::luce_tocolour(2);
    Colour replacementColour = LUCE::luce_tocolour(2);
    return LUA::returnBoolean( child->replaceColour( originalColour, replacementColour ) );
}

int LDrawable::createValueTree ( lua_State *L ) {
    // ComponentBuilder::ImageProvider* imageProvider = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LValueTree>( new LValueTree(L,
    //     Drawable::createValueTree( imageProvider )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ValueTree createValueTree( imageProvider )" );
}

int LDrawable::getParent ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LDrawableComposite>( new LDrawableComposite(L,
    //     Drawable::getParent()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "DrawableComposite getParent()" );
}

int LDrawable::getDrawableBounds ( lua_State* ) {
    return LUCE::luce_pushtable( child->getDrawableBounds() );
}

int LDrawable::setTransformToFit ( lua_State* ) {
    Rectangle<float> areaInParent = LUCE::luce_torectangle<float>(2);
    RectanglePlacement placement = LUCE::luce_torectangleplacement(2);
    child->setTransformToFit( areaInParent, placement );
    return 0;
}

int LDrawable::draw ( lua_State* ) {
    Graphics& g = (Graphics&)*LUA::from_luce<LGraphics>(2);
    float opacity = LUA::getNumber<float>(2);
    AffineTransform transform = LUCE::luce_toaffinetransform(2);
    child->draw( g, opacity, transform );
    return 0;
}

int LDrawable::drawAt ( lua_State* ) {
    Graphics& g = (Graphics&)*LUA::from_luce<LGraphics>(2);
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float opacity = LUA::getNumber<float>(2);
    child->drawAt( g, x, y, opacity );
    return 0;
}

int LDrawable::drawWithin ( lua_State* ) {
    Graphics& g = (Graphics&)*LUA::from_luce<LGraphics>(2);
    Rectangle<float> destArea = LUCE::luce_torectangle<float>(2);
    RectanglePlacement placement = LUCE::luce_torectangleplacement(2);
    float opacity = LUA::getNumber<float>(2);
    child->drawWithin( g, destArea, placement, opacity );
    return 0;
}

int LDrawable::setOriginWithOriginalSize ( lua_State* ) {
    child->setOriginWithOriginalSize(LUCE::luce_topoint<float>(2));
    return 0;
}
