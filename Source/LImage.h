/************************************************************

 LImage.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LIMAGE_H
#define __LUCE_LIMAGE_H

class LImage
    : public LBase,
      public Image
{
public:
    LImage(lua_State*);
    LImage(lua_State*, const Image&);
    LImage(lua_State*, juce::Image::PixelFormat, int w, int h, bool clear);
    LImage(lua_State*, juce::Image::PixelFormat, int w, int h, bool clear, juce::ImageType&);
    static int lnew(lua_State*);
    ~LImage();

    //==============================================================================
    static int s_null(lua_State*);

    //==============================================================================
    int getProperties(lua_State*);

    //==============================================================================
    int setPixelAt(lua_State*);
    int getPixelAt(lua_State*);
    int getWidth(lua_State*);
    int getHeight(lua_State*);
    int getBounds(lua_State*);

    //==============================================================================
    int createSolidAreaMask(lua_State*);
    int multiplyAllAlphas(lua_State*);
    int moveImageSection(lua_State*);
    int desaturate(lua_State*);
    int multiplyAlphaAt(lua_State*);
    int clear(lua_State*);
    int duplicateIfShared(lua_State*);

    //==============================================================================
    int getFormat(lua_State*);
    int isRGB(lua_State*);
    int createLowLevelContext(lua_State*);
    int convertedToFormat(lua_State*);
    int getReferenceCount(lua_State*);
    int getClippedImage(lua_State*);
    int isNull(lua_State*);
    int getPixelData(lua_State*);
    int createCopy(lua_State*);
    int isARGB(lua_State*);
    int isSingleChannel(lua_State*);
    int hasAlphaChannel(lua_State*);
    int isValid(lua_State*);
    int rescaled(lua_State*);
    
    //==============================================================================
    // ImageCache
    static int s_getFromFile(lua_State*);
    static int s_getFromMemory(lua_State*);
    static int s_getFromHashCode(lua_State*);
    static int s_addImageToCache(lua_State*);
    static int s_setCacheTimeout(lua_State*);
    static int s_releaseUnusedImages(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LImage>::Inheritence inherits[];
    static const Luna<LImage>::InheritenceF inheritsF[];
    static const Luna<LImage>::PropertyType properties[];
    static const Luna<LImage>::FunctionType methods[];
    static const Luna<LImage>::StaticType statics[];
    static const Luna<LImage>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LImage)
};

#endif // __LUCE_LIMAGE_H
