#ifndef __REC_AUDIO_FORMAT_MPG123_REPLACE_READER__
#define __REC_AUDIO_FORMAT_MPG123_REPLACE_READER__

#include <stdlib.h>
#include <sys/types.h>

namespace rec {
namespace mpg123 {

#include <mpg123.h>

namespace {

    ssize_t read(void *inputStream, void *buf, size_t nbytes) {
        return reinterpret_cast<InputStream*>(inputStream)->read(buf, nbytes);
    }

    off_t seek(void *inputStream, off_t offset, int whence) {
        InputStream* in = reinterpret_cast<InputStream*>(inputStream);

        if (whence == SEEK_CUR)
            offset += in->getPosition();

        else if (whence == SEEK_END)
            offset += in->getTotalLength();

        else if (whence != SEEK_SET)
            offset = -1;

        return (offset >= 0) && in->setPosition(offset) ? offset : -1;
    }

}  // namespace

Error newHandle(InputStream* in, mpg123_handle** result) {
    Error e;
    mpg123_handle* mh = NULL;

    if ((e = initializeOnce()) || !(mh = mpg123_new(NULL, &e))) {
        mpg123_delete(mh);
    } else {
        mpg123_param(mh, MPG123_VERBOSE, 2, 0);
        mpg123_param(mh, MPG123_FLAGS, MPG123_FUZZY | MPG123_SEEKBUFFER | MPG123_GAPLESS, 0);
        if ( !(e = mpg123_replace_reader_handle(mh, read, seek, NULL)) &&
                !(e = mpg123_open_handle(mh, in)))
            *result = mh;
        else
            mpg123_delete(mh);
    }
    return e;

#if 0
    Error e;
    mpg123_handle* mh = NULL;
    bool isInfinite = in->getTotalLength()<0;
    std::cout << "is infinite ? " << isInfinite << std::endl;
    if (!(e = initializeOnce()) &&
            (mh = mpg123_new(NULL, &e)) &&
            ( (isInfinite && true) || (
               !(e = mpg123_replace_reader_handle(mh, read, seek, NULL)) &&
               !(e = mpg123_open_handle(mh, in))
              )
            )
       )
    {
        if(isInfinite) {
            if (e = mpg123_replace_reader_handle(mh, read, seek, NULL)) {
                mpg123_delete(mh);
                return e;
            }
            mpg123_param(mh, MPG123_VERBOSE, 2, 0);
            e = mpg123_param(mh, MPG123_FLAGS, MPG123_FUZZY | MPG123_SEEKBUFFER | MPG123_GAPLESS, 0);
            if(e != MPG123_OK)
            {
                mpg123_delete(mh);
                std::cout << "Unable to set library options: " << mpg123_plain_strerror(e) << std::endl;
                return e;
            }
            // Let the seek index auto-grow and contain an entry for every frame
            e = mpg123_param(mh, MPG123_INDEX_SIZE, -1, 0);
            if(e != MPG123_OK)
            {
                std::cout << "Unable to set index size: " << mpg123_plain_strerror(e) << std::endl;
                return e;
            }

            e = mpg123_open_feed(mh);
            if(e != MPG123_OK)
            {
                std::cout << "Unable to open feed: " << mpg123_plain_strerror(e) << std::endl;
                return e;
            }

            unsigned char buffer[512];
            int len = in->read(buffer, 512);
            in->setPosition(0);
            mpg123_feed(mh, buffer, len);
        }
        *result = mh;
    }
    else
        mpg123_delete(mh);

    return e;
#endif
}

}  // namespace mpg123
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_MPG123_REPLACE_READER__
