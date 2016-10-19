#include <iostream>

#include "DynSet.h"
#include "AnsiString.h"

#include "DataUtil.h"

#include "Data.h"

DynSet<AnsiString> readData() {
  char buf[1000000];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1000000))
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

AnsiString extractCompanyName(AnsiString div) {
  const AnsiString companyPrefix = "<h2 class=\"company-name\" itemprop=\"name\">";
  int beg = div.Pos(companyPrefix);
  if(beg<=0)
    return "";
  div = div.SubString(beg+companyPrefix.Length(), div.Length()-beg-companyPrefix.Length()+1);
  beg = div.Pos(">");
  if(beg<=0)
    return "";
  div = div.SubString(beg+1, div.Length()-beg);
  beg = div.Pos("<");
  if(beg<=0)
    return "";
  return div.SubString(1, beg-1);
}

AnsiString extractCity(AnsiString div) {
  const AnsiString cityPrefix = "<span itemprop=\"addressRegion\">";
  int beg = div.Pos(cityPrefix);
  if(beg<=0)
    return "";
  div = div.SubString(beg+cityPrefix.Length(), div.Length()-beg-cityPrefix.Length()+1);
  beg = div.Pos("<");
  if(beg<=0)
    return "";
  return div.SubString(1, beg-1);
}

AnsiString extractStreet(AnsiString div) {
  const AnsiString streetPrefix = "<span class=\"street-address\" itemprop=\"streetAddress\">";
  int beg = div.Pos(streetPrefix);
  if(beg<=0)
    return "";
  div = div.SubString(beg+streetPrefix.Length(), div.Length()-beg-streetPrefix.Length()+1);
  beg = div.Pos("<");
  if(beg<=0)
    return "";
  return div.SubString(1, beg-1);
}

AnsiString extractPhone(AnsiString div) {
  const AnsiString phonePrefix = "data-phone=\"";
  int beg = div.Pos(phonePrefix);
  if(beg<=0)
    return "";
  div = div.SubString(beg+phonePrefix.Length(), div.Length()-beg-phonePrefix.Length()+1);
  beg = div.Pos("\"");
  if(beg<=0)
    return "";
  return div.SubString(1, beg-1);
}

AnsiString extractWWW(AnsiString div) {
  const AnsiString wwwPrefix = "<span class=\"www--full\">";
  int beg = div.Pos(wwwPrefix);
  if(beg<=0)
    return "";
  div = div.SubString(beg+wwwPrefix.Length(), div.Length()-beg-wwwPrefix.Length()+1);
  beg = div.Pos("\"");
  if(beg<=0)
    return "";
  return div.SubString(1, beg-1);
}

AnsiString extractEmail(AnsiString div) {
  const AnsiString emailPrefix = "<span data-tooltip=\"tooltip\" title=\"";
  const AnsiString emailWord = "e-mail";
  
  int beg = div.Pos(emailPrefix);
  while(beg>0) {
    div = div.SubString(beg+emailPrefix.Length(), div.Length()-beg-emailPrefix.Length()+1);
    beg = div.Pos("\"");
    if(beg<=0)
      return "";
    AnsiString ret = div.SubString(1, beg-1);
    if(div.Pos(emailWord)==ret.Length()+3) {
      return ret;
    }
    beg = div.Pos(emailPrefix);
  }
  return "";
}

void processDiv(DynSet<Info>& infos, AnsiString div) {
  Info info = empyInfo();
  info.getCompany() = extractCompanyName(div);
  info.getCity() = extractCity(div);
  info.getStreet() = extractStreet(div);
  info.getPhone() = extractPhone(div);
  info.getWww() = extractWWW(div);
  info.getEmail() = extractEmail(div);
  infos.Insert(info);
}

const AnsiString divPrefix = "<div id=\"id";

void processLine(DynSet<Info>& infos, AnsiString line) {
  while(line.Pos(divPrefix)>0) {
    int beg = line.Pos(divPrefix);
    AnsiString div = line.SubString(beg+divPrefix.Length(), line.Length()-beg-divPrefix.Length()+1);
    beg = div.Pos(">");
    div = div.SubString(beg+1, div.Length()-beg);
    int end = div.Pos(divPrefix);
    if(end > 0) {
      line = div.SubString(end, div.Length()-end+1);
      div = div.SubString(1, end-1);
      processDiv(infos, div);
    } else {
      processDiv(infos, div);
      break;
    }
  }
}

void process(DynSet<Info>& infos, DynSet<AnsiString>& lines) {
  for(int i=0;i<lines.Size();i++) {
    processLine(infos, lines[i]);
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
