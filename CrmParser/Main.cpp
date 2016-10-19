#include <iostream>

#include "DynSet.h"
#include "AnsiString.h"

#include "DataUtil.h"

#include "Data.h"

DynSet<AnsiString> readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return ret;
}

Info empyInfo() {
  return Info("","","","","","","","","","","","","");
}

DynSet<AnsiString> getWords(AnsiString line) {
  DynSet<AnsiString> ret;
  AnsiString act = "";
  for(int i=1;i<=line.Length();i++) {
    if(line[i]=='#') {
        ret.Insert(act);
        act = "";
    } else
      act += line[i];
  }
  ret.Insert(act);
  return ret;
}

const int crmIdPos = 0;
const int namePos = 1;
const int surnamePos = 2;
const int companyPos = 3;
const int cityPos = 4;
const int streetPos = 5;
const int zipPos = 6;
const int emailPos = 7;
const int phonePos = 8;
const int mobilePos = 9;

void process(DynSet<Info>& infos, DynSet<AnsiString>& lines) {
  for(int i=0;i<lines.Size();i++) {
    Info info = empyInfo();
    DynSet<AnsiString> words = getWords(lines[i]);
    if(words.Size()>mobilePos) {
      info.getCrm_id() = words[crmIdPos];
      info.getName() = words[namePos];
      info.getSurname() = words[surnamePos];
      info.getCompany() = words[companyPos];
      info.getCity() = words[cityPos];
      info.getStreet() = words[streetPos];
      info.getZip() = words[zipPos];
      info.getEmail() = words[emailPos];
      info.getPhone() = words[phonePos];
      info.getMobile() = words[mobilePos];
      info.getSource()= "crm";
      infos.Insert(info);
    } else
      std::cerr<<"[WARNING] Skip line: "<<lines[i].c_str()<<std::endl;
  }
}

static bool checkArg(int argc, const char* argv[], const AnsiString& v) {
  for (int i=1;i<argc;i++)
    if (v==argv[i])
      return true;
  return false;
}

int main(int argc, const char* argv[]) {
  DynSet<AnsiString> lines = readData();
  Infos infos;
  process(infos, lines);
  AnsiString jsonArg = "-json";
  bool json = checkArg(argc, argv, jsonArg);
  if(!json)
    DataUtil::printInfosCSV(infos); 
  else
    std::cout<<(infos.toJSON()).c_str()<<std::endl;
}
