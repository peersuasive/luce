/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== json_sample.json ==================
static const unsigned char temp_binary_data_0[] =
"[\n"
"    {\n"
"        \"address\" : \"\",\n"
"        \"phone\"    : \"\",\n"
"        \"city\"     : \"Toulouse\",\n"
"        \"mobile\"   : \"\",\n"
"        \"userid\"   : \"cberbizier@peersuasive.com\",\n"
"        \"contact\":\"cberbizier@peersuasive.com\"\n"
"    },\n"
"    {\n"
"        \"address\":\"\",\n"
"        \"phone\":\"\",\n"
"        \"city\":\"London\",\n"
"        \"mobile\":\"\",\n"
"        \"userid\":\"testuser@peersuasive.net\",\n"
"        \"contact\":\"testuser@peersuasive.net\"\n"
"    },\n"
"    {\n"
"        \"address\":\"\",\n"
"        \"phone\":\"\",\n"
"        \"city\":\"\",\n"
"        \"mobile\":\"\",\n"
"        \"userid\":\"cberbizier@peersuasive.org\",\n"
"        \"contact\":\"cberbizier@peersuasive.org\"\n"
"    }\n"
"]\n";

const char* json_sample_json = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x13785986:  numBytes = 601; return json_sample_json;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "json_sample_json"
};

}
