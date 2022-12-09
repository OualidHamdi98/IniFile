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

    IniFileManager(const string &fileName);
    virtual ~IniFileManager(void);

    bool addSection(const string &sectionName);
    bool addKeyValue(const string &KeyName,const string &Value,const string &SectionName);
    bool renameSection(const string &oldName,const string &newName);

    bool commentSection(char commentChar,const string &section);
    bool setSectionComments(const string &comments,const string &sectionName);
    bool commentRecord(enumCharComment cc,const string &key,const string &section);
    bool setRecordComments(const string &comments,const string &key,const string &section);


    bool deleteSection(const string &section);
    bool deleteRecord(const string &KeyName,const string &SectionName);
    bool deleteComment(const string &key,const string &section);

    void printFile() const;
    void printAllSection() const;
    void printValue(const string &key,const string &section) const;

    const vector<IniStruct> &getFileContent() const;
    void setFileContent(const vector<IniStruct> &fileContent);

private:
    string fileName;
    vector<IniStruct> fileContent;
    bool save(vector<IniStruct>& content) const;
    bool load(const string &fileName, vector<IniStruct>& content);
    bool create(const string &fileName);
    bool checkKeyValue(const string &section,const string &key) const;
    bool checkSection(const string &section) const;

};



#endif //INIFILE_INIFILEMANAGER_H
