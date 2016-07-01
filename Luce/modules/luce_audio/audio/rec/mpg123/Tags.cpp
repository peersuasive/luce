namespace rec {
namespace mpg123 {

#include <mpg123.h>

static void set(mpg123_text* text, int size, StringPairArray* data) {
    for (mpg123_text* t = text; t != text + size; ++t) {
        String name(t->id, 4);
        for (; (*data)[name] != ""; name += "+");
        data->set(name, String(t->text.p, t->text.fill));
    }
}

Error getMp3Tags(mpg123_handle* mh, StringPairArray* data) {
    if (!mpg123_meta_check(mh))
        return MPG123_ERR;

    mpg123_id3v1 *v1;
    mpg123_id3v2 *v2;

    if (Error e = mpg123_id3(mh, &v1, &v2))
        return e;

    if (v2) {
        data->set("idversion", "id3v2");
        set(v2->text, v2->texts, data);
        set(v2->comment_list, v2->comments, data);
        set(v2->extra, v2->extras, data);

        return MPG123_OK;
    }

    if (v1) {
        data->set("idversion", "id3v1");
        data->set("title", String(v1->title, 30));
        data->set("artist", String(v1->artist, 30));
        data->set("album", String(v1->album, 30));
        data->set("year", String(v1->year, 4));
        data->set("comment", String(v1->comment, 30));
        data->set("genre", String((const char*) &v1->genre, 1));

        return MPG123_OK;
    }

    return MPG123_ERR;
}

}  // namespace mpg123
}  // namespace rec
