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

    void setFileName(const string &fileName);

    const string &getFileName() const;

    enum enumCharComment
    {
        hashtag = '#',
        semicolon = ';'
    };

    IniFileManager(string fileName);
    virtual ~IniFileManager(void);

    bool addSection(string sectionName);
    bool addKeyValue(string KeyName, string Value, string SectionName);
    bool renameSection(string oldName, string newName);

    bool commentSection(char commentChar, string section);
    bool setSectionComments(string comments, string sectionName);
    bool commentRecord(enumCharComment cc, string key, string section);
    bool setRecordComments(string comments, string key, string section);

    bool checkKeyValue(string section,string key);
    bool checkSection(string section);

    bool deleteSection(string section);
    bool deleteRecord(string KeyName, string SectionName);

    void printFile();
    void printAllSection();
    void printValue(string key, string section);

    const vector<IniStruct> &getFileContent() const;
    void setFileContent(const vector<IniStruct> &fileContent);

private:
    string fileName;
    vector<IniStruct> fileContent;
    bool save(vector<IniStruct>& content);
    bool load(string fileName, vector<IniStruct>& content);
    bool create(string fileName);

};



#endif //INIFILE_INIFILEMANAGER_H
