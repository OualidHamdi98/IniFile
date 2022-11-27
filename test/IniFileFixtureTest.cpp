#include "gtest/gtest.h"
#include "../IniFileManager.h"

class IniFileFixtureTest: public ::testing::Test{


protected:
    virtual void SetUp() {
        iniFile->addKeyValue("identifier", "Oualid Hamdi", "Owner");
        iniFile->addSection("Database");
        iniFile->addKeyValue("SchemaDb", "test_db", "Database");
        iniFile->addKeyValue("SchemaDb", "prod_db", "Database");
        iniFile->addKeyValue("SchemaDb", "svil_db", "Database");
        iniFile->addSection("Connection");
        iniFile->addKeyValue("ServerIp", "123.1.2.3", "Connection");
        iniFile->addKeyValue("ServerPort", "8080", "Connection");
        iniFile->renameSection("Database","DataBaseProperty");
        iniFile->addKeyValue("file1.lib", "libName", "Lib");
        iniFile->addKeyValue("file2.lib", "libName", "Lib");
        iniFile->commentRecord(IniFileManager::enumCharComment::semicolon, "ServerPort", "Connection"); //commenta il record della chiave indicata
        iniFile->commentSection(IniFileManager::enumCharComment::semicolon, "Owner");
        iniFile->setSectionComments("#File di test creato il 18/11", "Owner");
        iniFile->setRecordComments("#versione deprecata","file2.lib", "Lib");
    }

    IniFileManager* iniFile = new IniFileManager("test.ini");

};

TEST_F(IniFileFixtureTest,Delete){
    ASSERT_TRUE(iniFile->deleteComment("ServerPort", "Connection"));
    ASSERT_TRUE(iniFile->deleteRecord("ServerIp","Connection"));
    ASSERT_FALSE(iniFile->deleteRecord("ServerIp2","Connection"));
    ASSERT_TRUE(iniFile->deleteSection("Connection"));
}



