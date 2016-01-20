/************************************************************

 LInputStream.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LINPUTSTREAM_H
#define __LUCE_LINPUTSTREAM_H

class LInputStream
    : public LBase,
      public InputStream//, private InputStream::Listener
{
public:
    LInputStream(lua_State*);
    LInputStream(lua_State *L, InputStream*);
    ~LInputStream();

    //==============================================================================
    int getNumBytesRemaining(lua_State*);
    int readShort(lua_State*);
    int readInt64BigEndian(lua_State*);
    int readInt(lua_State*);
    int readCompressedInt(lua_State*);
    int readShortBigEndian(lua_State*);
    int readDoubleBigEndian(lua_State*);
    int readFloat(lua_State*);
    int readByte(lua_State*);
    int readEntireStreamAsString(lua_State*);
    int readString(lua_State*);
    int readDouble(lua_State*);
    int readNextLine(lua_State*);
    int readIntBigEndian(lua_State*);
    int readBool(lua_State*);
    int readInt64(lua_State*);
    int readFloatBigEndian(lua_State*);

    //int readIntoMemoryBlock(lua_State*);
    int skipNextBytes(lua_State*);

    //== virtuals ==================================================================
    virtual int64 getTotalLength() override;
    int getTotalLength(lua_State*);
    virtual bool isExhausted() override;
    int isExhausted(lua_State*);
    virtual int64 getPosition() override;
    int getPosition(lua_State*);
    virtual bool setPosition (int64 newPosition) override;
    int setPosition(lua_State*);
    virtual int read (void* destBuffer, int maxBytesToRead) override;
    int read(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LInputStream>::Inheritence inherits[];
    static const Luna<LInputStream>::InheritenceF inheritsF[];
    static const Luna<LInputStream>::PropertyType properties[];
    static const Luna<LInputStream>::FunctionType methods[];
    static const Luna<LInputStream>::StaticType statics[];
    static const Luna<LInputStream>::Enum enums[];

private:
    //==============================================================================
    ScopedPointer<InputStream> child;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LInputStream)
};

#endif // __LUCE_LINPUTSTREAM_H
