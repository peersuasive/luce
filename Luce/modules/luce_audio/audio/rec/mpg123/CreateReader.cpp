namespace rec {
namespace mpg123 {
namespace {

Error setFormat(mpg123_handle* mh,
                OutputFormat* begin,
                OutputFormat* end) {
  if (begin != end) {
    if (Error e = mpg123_format_none(mh))
      return e;

    for (OutputFormat* i = begin; i != end; ++i) {
      if (Error e = mpg123_format(mh, i->rate_, i->channels_, i->encoding_))
        return e;
    }
  }
  return MPG123_OK;
}

}  // namespace

Error createReader(InputStream* in,
        AudioFormatReader** reader,
        OutputFormat* begin,
        OutputFormat* end) {
    mpg123_handle *mh = NULL;

    bool isInfinite = in->getTotalLength()<0;
    long sampleRate;
    int numChannels, encoding;
    int bitsPerSample;
    Copier copier;

    Error e;
    if ((e = newHandle(in, &mh)) ||
            (e = setFormat(mh, begin, end)) ||
            (e = isInfinite ? 0 : mpg123_scan(mh)) ||
            (e = mpg123_getformat(mh, &sampleRate, &numChannels, &encoding)) ||
            !(bitsPerSample = getBitsPerSample(encoding)) ||
            !(copier = getCopier(encoding)) ||
            numChannels > MPG123_STEREO) {  // Failure.
        mpg123_delete(mh);

    } else {
        std::cout << "creating reader" << std::endl;
        *reader = new Reader(in, getTranslatedName(), mh, copier);
        AudioFormatReader &r = **reader;
        r.bitsPerSample = bitsPerSample;
        r.sampleRate = int(sampleRate);
        r.lengthInSamples = mpg123_length(mh);
        r.usesFloatingPointData = (encoding & MPG123_ENC_FLOAT);
        r.numChannels = numChannels;

        if(!isInfinite)getMp3Tags(mh, &r.metadataValues);
    }

    return e;

#if 0
    long sampleRate;
    int numChannels, encoding;
    int bitsPerSample;
    Copier copier;

    bool isInfinite = in->getTotalLength()<0;

    Error e;
    if (e = newHandle(in, &mh)) {
        std::cout << "failed to create handle" << std::endl;
        mpg123_delete(mh);
    } else if ((e = setFormat(mh, begin, end))) {
        std::cout << "failed to set format" << std::endl;
        mpg123_delete(mh);
    //} else if ((e = mpg123_scan(mh))) {
    //    std::cout << "failed to scan" << std::endl;
    //    mpg123_delete(mh);
    } else if ((e = mpg123_getformat(mh, &sampleRate, &numChannels, &encoding))) {
        std::cout << "failed to get format" << std::endl;
        mpg123_delete(mh);
    } else if (!(bitsPerSample = getBitsPerSample(encoding))) {
        std::cout << "failed to get bits per sample" << std::endl;
        mpg123_delete(mh);
    } else if (!(copier = getCopier(encoding))) {
        std::cout << "failed to get copier" << std::endl;
        mpg123_delete(mh);
    } else if (numChannels > MPG123_STEREO) {
        std::cout << "wrong number of channels" << std::endl;
        mpg123_delete(mh);
    /*
    if ((e = newHandle(in, &mh)) ||
            (e = setFormat(mh, begin, end)) ||
            (e = mpg123_scan(mh)) ||
            (e = mpg123_getformat(mh, &sampleRate, &numChannels, &encoding)) ||
            !(bitsPerSample = getBitsPerSample(encoding)) ||
            !(copier = getCopier(encoding)) ||
            numChannels > MPG123_STEREO) {  // Failure.
        mpg123_delete(mh);
    */
    } else {
        std::cout << "ok, create reader !" << std::endl;
        *reader = new Reader(in, getTranslatedName(), mh, copier);
        AudioFormatReader &r = **reader;
        r.bitsPerSample = bitsPerSample;
        r.sampleRate = int(sampleRate);
        r.lengthInSamples = mpg123_length(mh);
        r.usesFloatingPointData = (encoding & MPG123_ENC_FLOAT);
        r.numChannels = numChannels;

        std::cout << "bitsPerSample: " << r.bitsPerSample
            << ", sampleRate: "  << r.sampleRate
            << ", lengthInSamples: " << r.lengthInSamples
            << ", usesFloatingPointData: " << r.usesFloatingPointData
            << ", numChannels: " << r.numChannels
            << std::endl;

        if(isInfinite) {
            mpg123_seek(mh, 0, SEEK_SET);
        } else
            getMp3Tags(mh, &r.metadataValues);
    }

    return e;
#endif

}

}  // namespace mpg123
}  // namespace rec
