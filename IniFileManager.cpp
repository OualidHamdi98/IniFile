//
// Created by OualidHamdi on 06/11/2022.
//

#include "IniFileManager.h"

IniFileManager::IniFileManager(string fileName){
    this->setFileName(fileName);
    if (!create(fileName))
        this->load(fileName,fileContent);
}

IniFileManager::~IniFileManager(void){
    // vector<IniStruct> fileContent = this->getFileContent();
    this->save(fileContent);
}

bool IniFileManager::create(string fileName)
{
    ifstream f(fileName.c_str());
    if (f.good())
    {
        cout << fileName + " file already existed" << endl;
        return false;
    }
    else
    {
        ofstream file;
        file.open (fileName, ios::out);
        cout << fileName << " created!" << endl;
        return true;
    }
}

const vector<IniFileManager::IniStruct> &IniFileManager::getFileContent() const {
    return fileContent;
}

// crea e salva un nuovo file vuoto

bool IniFileManager::save(vector<IniStruct>& fileContent)
{
    //creo un output str
    //if (!outFile.is_open()) return false;
    try{
        //fileName=this->getFileName();
        //  ofstream outFile (this->getFileName().c_str());
        ofstream outFile (fileName.c_str());
        for (int i=0;i<(int)fileContent.size();i++)
        {
            outFile << fileContent[i].commentsStruct;
            if(fileContent[i].keyStruct == "")
                outFile << fileContent[i].charCommentStruct << "["
                        << fileContent[i].sectionStruct << "]" << endl;
            else
                outFile << fileContent[i].charCommentStruct << fileContent[i].keyStruct
                        << "=" << fileContent[i].valueStruct << endl;
        }
        outFile.close();
        return true;
    } catch (std::ofstream::failure &writeErr) {
        std::cerr << "Errore in fase di scrittura del file\n";
        return false;
    }
    catch (std::ifstream::failure &readErr) {
        std::cerr << "Errore in fase di lettura del file\n";
        return false;
    }
}
// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

void trim(std::string& str)
{
    /*
    //regex che individua tutti gli spazi in una stringa
    std::regex r("\\s+");
    str=std::regex_replace(str,r,"");
     */
    const char* t = " \t\n\r\f\v";
    ltrim(rtrim(str, t), t);

}

bool IniFileManager::load(string fileName, vector<IniStruct>& content)
{
    string s;
    string CurrentSection;
    try{
        ifstream inFile (fileName.c_str());
        //content.clear();
        string comments = "";
        //scorro fino alla fine del file;
        while(!std::getline(inFile, s).eof()){
            //pulisco la stringa dagli spazi vuoti;
            trim(s);
            if(!s.empty())
            {
                IniStruct r;
                //controllo se è una linea commentata;
                if((s[0]=='#')||(s[0]==';'))
                {
                    //non ci sono chiavi o valori
                    if ((s.find('[')==string::npos)&&
                        (s.find('=')==string::npos))
                    {
                        comments += s + '\n';
                        //vado a capo;
                    } else {
                        //salvo il caratterre e lo cancello per le iterazioni future;
                        r.charCommentStruct = s[0];
                        s.erase(s.begin());
                        trim(s);
                    }
                }
                    //non ci sono linee commentate
                else r.charCommentStruct = ' ';
                //controllo se è una sezione
                if(s.find('[')!=string::npos)
                {
                    //cancello le quadre, e salvo la sezione;
                    s.erase(s.begin());
                    s.erase(s.find(']'));
                    r.commentsStruct = comments;
                    comments = "";
                    r.sectionStruct = s;
                    r.keyStruct = "";
                    r.valueStruct = "";
                    CurrentSection = s;
                }
                //controllo se ho chiave = valore
                if(s.find('=')!=string::npos)
                {
                    r.commentsStruct = comments;
                    comments = "";
                    r.sectionStruct = CurrentSection;
                    r.keyStruct = s.substr(0, s.find('='));
                    r.valueStruct = s.substr(s.find('=') + 1);
                }
                if(comments == ""){
                    content.push_back(r);
                }
            }
        }
        inFile.close();
        this->setFileContent(content);
        return true;
    }catch(std::exception const& e){
        cout << "Errore di gestione del file: " << e.what() << endl;
        return false;
    }

}

void IniFileManager::printFile()
{
    string s="";
    //vector<IniStruct> content = this->getFileContent();
    for (int i=0;i<(int)fileContent.size();i++)
    {
        if(fileContent[i].commentsStruct != "") s += fileContent[i].commentsStruct;
        if(fileContent[i].charCommentStruct != ' ') s += fileContent[i].charCommentStruct;
        if((fileContent[i].keyStruct == "")) s += '[' + fileContent[i].sectionStruct + ']';
        else s += fileContent[i].keyStruct + '=' + fileContent[i].valueStruct;
        //vai a capo
        if (i != fileContent.size()) s += '\n';
    }
    cout << s;
}

void IniFileManager::printAllSection()
{
    vector<string> allSection;
    //vector<IniStruct> content = this->getFileContent();

    for (int i=0;i<(int)fileContent.size();i++)
    {
        //se non esiste una chiave allora è una sezione;
        if(fileContent[i].keyStruct == "")
            allSection.push_back(fileContent[i].sectionStruct);
    }
    //lambda function per stampare il vettore
    std::for_each(  allSection.begin(),
                    allSection.end(),
                    [](const auto & elem ) {
                        std::cout<<elem<<"\n";
                    });
}

bool IniFileManager::addSection(string sectionName)
{
    // vector<IniStruct> content = this->getFileContent();;

    if (!checkSection(sectionName))
    {
        //definisco una nuova iniStruct
        IniStruct s = {"",' ',sectionName,"",""};
        fileContent.push_back(s);
        //this->setFileContent(fileContent);
        return true;
    }
    return false;
}

bool IniFileManager::commentSection(char commentChar, string section)
{
    // vector<IniStruct> content = this->getFileContent();

    for(vector<IniStruct>::iterator iter = fileContent.begin(); iter < fileContent.end(); iter++)
    {
        if(iter->sectionStruct == section){
            //Cambia il commento e salva
            iter->charCommentStruct = commentChar;
            //this->setFileContent(content);
            return true;
        }
    }
    return false;
}

bool IniFileManager::checkKeyValue(string section,string key)
{
    //vector<IniStruct> content = this->getFileContent();
    vector<IniStruct>::iterator iter = fileContent.begin();
    while(iter != fileContent.end() ){
        if((iter->sectionStruct == section) && (iter->keyStruct == key)) return true;
        else iter++;
    }
    return false;
}

bool IniFileManager::renameSection(string oldName, string newName)
{
    //vector<IniStruct> content = this->getFileContent();
    for(vector<IniStruct>::iterator iter = fileContent.begin();
        iter < fileContent.end(); iter++)
    {
        if(iter->sectionStruct == oldName){
            iter->sectionStruct = newName;
            //this->setFileContent(content);
            return true;
        }
    }
    return false;
}

bool IniFileManager::setSectionComments(string comments, string sectionName)
{
    // vector<IniStruct> content = this->getFileContent();
    for(vector<IniStruct>::iterator iter = fileContent.begin(); iter < fileContent.end(); iter++)
    {
        // cerco la sezione corretta con record vuoto;
        if((iter->sectionStruct == sectionName) && (iter->keyStruct == ""))
        {
            // aggiungo a capo se non presente
            if (comments.size() >= 2 && comments.substr(comments.size()-2) != "\n")
                comments += "\n";
            //salvo il commento
            iter->commentsStruct = comments;
            // this->setFileContent(content);
            return true;
        }
    }
    return false;
}

bool IniFileManager::deleteSection(string section)
{
    // vector<IniStruct> content = this->getFileContent();
    for(int i=(int)fileContent.size()-1;i>=0;i--) {
        if (fileContent[i].sectionStruct == section) {
            fileContent.erase(fileContent.begin() + i);
            // this->setFileContent(fileContent);
            return true;
        }
    }
    return false;
}

bool IniFileManager::addKeyValue(string KeyName, string Value, string SectionName)
{
    //vector<IniStruct> content = this->getFileContent();
    if(!checkSection(SectionName))
    {
        IniStruct s = {"", ' ', SectionName, "", ""};
        IniStruct r = {"", ' ', SectionName, KeyName, Value};
        fileContent.push_back(s);
        fileContent.push_back(r);
        // this->setFileContent(fileContent);
        return true;
    }
    if(!checkKeyValue(SectionName, KeyName))
    {
        vector<IniStruct>::iterator iter = fileContent.begin();
        //non faccio altri controlli tanto so che esiste una sezione = section;
        while(iter->sectionStruct != SectionName)
            iter++;
        IniStruct r = {"", ' ', SectionName, KeyName, Value};
        fileContent.insert(iter+1,r);
        //iter.push_back(r);
        //content.insert(iter,r);
        // this->setFileContent(content);
        return true;
    }
    return false;
}

bool IniFileManager::commentRecord(enumCharComment cc, string key, string section)
{
    //vector<IniStruct> content = this->getFileContent();

    vector<IniStruct>::iterator iter = fileContent.begin();
    while((iter != fileContent.end()) && (iter->sectionStruct != section) || (iter->keyStruct!=key))
        iter++;
    if (iter == fileContent.end()) return false;
    iter->charCommentStruct = cc;
    //this->setFileContent(content);
    return true;
}

bool IniFileManager::checkSection(string sectionName)
{
    //vector<IniStruct> content = this->getFileContent();
    vector<IniStruct>::iterator iter = fileContent.begin();
    while(iter != fileContent.end() ){
        if(iter->sectionStruct == sectionName) return true;
        else iter++;
    }
    return false;
}

void IniFileManager::printValue(string key, string section)
{
    IniStruct data;
    // vector<IniStruct> content = this->getFileContent();
    vector<IniStruct>::iterator iter = fileContent.begin();
    while(iter !=  fileContent.end() && (iter->sectionStruct != section || iter->keyStruct != key))
        iter++;
    if (iter != fileContent.end())
        cout <<"\n value of key : "<<key <<" in section : "<<section<< " is : " << iter->valueStruct ;
    else cout << "\n there is no value for for this section or this key in this file; " ;

}

bool IniFileManager::deleteRecord(string key, string section)
{
    // vector<IniStruct> content = this->getFileContent();
    vector<IniStruct>::iterator iter = fileContent.begin();
    while (iter != fileContent.end() && (iter->sectionStruct != section || iter->keyStruct != key))
        iter++;
    if (iter != fileContent.end()) {
        fileContent.erase(iter);
        //this->setFileContent(content);
        return true;
    }
    cout <<"\n no key has been deleted ";
    return false;
}

bool IniFileManager::setRecordComments(string comments, string key, string section)
{
    // vector<IniStruct> content = this->getFileContent();

    vector<IniStruct>::iterator iter = fileContent.begin();
    while(iter !=  fileContent.end() && (iter->sectionStruct != section || iter->keyStruct != key))
        iter++;
    if (iter == fileContent.end()) return false;
    if ((comments.size() >= 2) && (comments.substr(comments.size()-2) != "\n"))
        comments += "\n";
    iter->commentsStruct = comments;
    //this->setFileContent(content);
    return true;
}

void IniFileManager::setFileContent(const vector<IniStruct> &fileContent) {
    IniFileManager::fileContent = fileContent;
}

const string &IniFileManager::getFileName() const {
    return fileName;
}

void IniFileManager::setFileName(const string &fileName) {
    IniFileManager::fileName = fileName;
}












