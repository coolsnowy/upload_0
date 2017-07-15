
#include "readfile.h"


void readfile(string &s1,string &s2,string &s3,const char *filepath)
{
    Json::Reader reader;
    Json::Value root;
    ifstream in;
    in.open(filepath, ios::binary);
    if( !in.is_open() )
    {
        Debug( "Error opening file\n");
        exit(0);
    }
    if(reader.parse(in,root))
    {
        s1 = root["RecvPort"].asString();
        s2 = root["ServIP"].asString();
        s3 = root["ServPort"].asString();
    }
    else
    {
        Debug("parse error\n");
        exit(0);
    }
    Debug("read paramter success!\n");
    in.close();
}
