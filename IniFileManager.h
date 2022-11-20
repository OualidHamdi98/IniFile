//
// Created by OualidHamdi on 06/11/2022.
//

#ifndef INIFILE_INIFILEMANAGER_H
#define INIFILE_INIFILEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <regex>

using namespace std;

class IniFileManager
{
public:
    struct IniStruct
    {
        string commentsStruct;
        char charCommentStruct;
        string sectionStruct;
        string keyStruct;
        string valueStruct;
    };

    enum enumCharComment
    {
        hashtag = '#',
        semicolon = ';'
    };

    IniFileManager(void);
    virtual ~IniFileManager(void);

    static bool create(string fileName);

    static bool addSection(string sectionName, string fileName);
    static bool addKeyValue(string KeyName, string Value, string SectionName, string FileName);
    static bool renameSection(string oldName, string newName, string fileName);

    static bool commentSection(char commentChar, string section, string fileName);
    static bool setSectionComments(string comments, string sectionName, string fileName);
    static bool commentRecord(enumCharComment cc, string key, string section, string fileName);
    static bool setRecordComments(string comments, string key, string section, string fileName);

    static bool checkKeyValue(string section,string key, string fileName);
    static bool checkSection(string section, string fileName);

    static bool deleteSection(string section, string fileName);
    static bool deleteRecord(string KeyName, string SectionName, string FileName);

    static void printFile(string fileName);
    static void printAllSection(string fileName);
    static void printValue(string key, string section, string fileName);

private:
    static bool save(string fileName, vector<IniStruct>& content);
    static bool load(string fileName, vector<IniStruct>& content);

};



#endif //INIFILE_INIFILEMANAGER_H
