#include <cstdio>
#include "Data.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- string ---------------
//----------------------------------

//------------- Info ---------------
Info::Info(const AnsiString& _crm_id, const AnsiString& _name, const AnsiString& _surname, const AnsiString& _company, const AnsiString& _street, const AnsiString& _city, const AnsiString& _zip, const AnsiString& _email, const AnsiString& _phone, const AnsiString& _mobile, const AnsiString& _www, const AnsiString& _source, const AnsiString& _status) : crm_id(_crm_id), name(_name), surname(_surname), company(_company), street(_street), city(_city), zip(_zip), email(_email), phone(_phone), mobile(_mobile), www(_www), source(_source), status(_status) {
}
const AnsiString& Info::getCrm_id() const {
  return crm_id;
}
AnsiString& Info::getCrm_id() {
  return crm_id;
}
const AnsiString& Info::getName() const {
  return name;
}
AnsiString& Info::getName() {
  return name;
}
const AnsiString& Info::getSurname() const {
  return surname;
}
AnsiString& Info::getSurname() {
  return surname;
}
const AnsiString& Info::getCompany() const {
  return company;
}
AnsiString& Info::getCompany() {
  return company;
}
const AnsiString& Info::getStreet() const {
  return street;
}
AnsiString& Info::getStreet() {
  return street;
}
const AnsiString& Info::getCity() const {
  return city;
}
AnsiString& Info::getCity() {
  return city;
}
const AnsiString& Info::getZip() const {
  return zip;
}
AnsiString& Info::getZip() {
  return zip;
}
const AnsiString& Info::getEmail() const {
  return email;
}
AnsiString& Info::getEmail() {
  return email;
}
const AnsiString& Info::getPhone() const {
  return phone;
}
AnsiString& Info::getPhone() {
  return phone;
}
const AnsiString& Info::getMobile() const {
  return mobile;
}
AnsiString& Info::getMobile() {
  return mobile;
}
const AnsiString& Info::getWww() const {
  return www;
}
AnsiString& Info::getWww() {
  return www;
}
const AnsiString& Info::getSource() const {
  return source;
}
AnsiString& Info::getSource() {
  return source;
}
const AnsiString& Info::getStatus() const {
  return status;
}
AnsiString& Info::getStatus() {
  return status;
}
AnsiString Info::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"crm_id\":";
    _json += "\"" + JSONEscape::encode(crm_id) + "\"";
    _json += ",";
    _json += "\"name\":";
    _json += "\"" + JSONEscape::encode(name) + "\"";
    _json += ",";
    _json += "\"surname\":";
    _json += "\"" + JSONEscape::encode(surname) + "\"";
    _json += ",";
    _json += "\"company\":";
    _json += "\"" + JSONEscape::encode(company) + "\"";
    _json += ",";
    _json += "\"street\":";
    _json += "\"" + JSONEscape::encode(street) + "\"";
    _json += ",";
    _json += "\"city\":";
    _json += "\"" + JSONEscape::encode(city) + "\"";
    _json += ",";
    _json += "\"zip\":";
    _json += "\"" + JSONEscape::encode(zip) + "\"";
    _json += ",";
    _json += "\"email\":";
    _json += "\"" + JSONEscape::encode(email) + "\"";
    _json += ",";
    _json += "\"phone\":";
    _json += "\"" + JSONEscape::encode(phone) + "\"";
    _json += ",";
    _json += "\"mobile\":";
    _json += "\"" + JSONEscape::encode(mobile) + "\"";
    _json += ",";
    _json += "\"www\":";
    _json += "\"" + JSONEscape::encode(www) + "\"";
    _json += ",";
    _json += "\"source\":";
    _json += "\"" + JSONEscape::encode(source) + "\"";
    _json += ",";
    _json += "\"status\":";
    _json += "\"" + JSONEscape::encode(status) + "\"";
  _json += "}";
  return _json.get();
}
Info Info::fromJSON(AnsiString s) {
  //printf("FromJson: %s\n", s.c_str());
  AnsiString arr[13];
  int ix=1;
  for (int i=0;i<13;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("Info::fromJSON 0x2 " + AnsiString(i));
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\') {
        ix+=2;
        continue;
      } else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<13) {
          if (ix-start-1<=0)
            throw Exception("Info::fromJSON ox3");
          arr[i] = s.SubString(start+1, ix-start-1);
          //printf("added %s\n", arr[i].c_str());
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return Info((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), (arr[2].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))), (arr[3].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[3].SubString(2, arr[3].Length()-2))), (arr[4].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[4].SubString(2, arr[4].Length()-2))), (arr[5].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[5].SubString(2, arr[5].Length()-2))), (arr[6].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[6].SubString(2, arr[6].Length()-2))), (arr[7].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[7].SubString(2, arr[7].Length()-2))), (arr[8].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[8].SubString(2, arr[8].Length()-2))), (arr[9].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[9].SubString(2, arr[9].Length()-2))), (arr[10].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[10].SubString(2, arr[10].Length()-2))), (arr[11].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[11].SubString(2, arr[11].Length()-2))), (arr[12].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[12].SubString(2, arr[12].Length()-2))));
}
Info::~Info() {
}
//----------------------------------

//------------- Infos ---------------
Infos::Infos() {
}
AnsiString Infos::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
Infos Infos::fromJSON(AnsiString s) {
  Infos arr = Infos();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("Infos::fromJSON 0x2");
  while (ix<=s.Length()) {
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\') {
        ix+=2;
        continue;
      } else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && (s[ix]==',' || ix==s.Length())) {
        if (start==ix)
          return arr;
        if (ix-start<=0)
          throw Exception("Infos::fromJSON 0x3");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(Info::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
Infos::~Infos() {
}
//----------------------------------

