#ifndef _DATA_GEN_H_
#define _DATA_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Info ---------------
class Info {
  AnsiString crm_id;
  AnsiString name;
  AnsiString surname;
  AnsiString company;
  AnsiString street;
  AnsiString city;
  AnsiString zip;
  AnsiString email;
  AnsiString phone;
  AnsiString mobile;
  AnsiString www;
  AnsiString source;
  AnsiString status;
public:
  Info(const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&);
  virtual const AnsiString& getCrm_id() const;
  virtual const AnsiString& getName() const;
  virtual const AnsiString& getSurname() const;
  virtual const AnsiString& getCompany() const;
  virtual const AnsiString& getStreet() const;
  virtual const AnsiString& getCity() const;
  virtual const AnsiString& getZip() const;
  virtual const AnsiString& getEmail() const;
  virtual const AnsiString& getPhone() const;
  virtual const AnsiString& getMobile() const;
  virtual const AnsiString& getWww() const;
  virtual const AnsiString& getSource() const;
  virtual const AnsiString& getStatus() const;
  virtual AnsiString& getCrm_id();
  virtual AnsiString& getName();
  virtual AnsiString& getSurname();
  virtual AnsiString& getCompany();
  virtual AnsiString& getStreet();
  virtual AnsiString& getCity();
  virtual AnsiString& getZip();
  virtual AnsiString& getEmail();
  virtual AnsiString& getPhone();
  virtual AnsiString& getMobile();
  virtual AnsiString& getWww();
  virtual AnsiString& getSource();
  virtual AnsiString& getStatus();

  virtual AnsiString toJSON() const;
  static Info fromJSON(AnsiString);

  virtual ~Info();

};
//----------------------------------

//------------- Infos ---------------
#include "DynSet.h"


class Infos : public DynSet<Info> {
public:
  Infos();

  virtual AnsiString toJSON() const;
  static Infos fromJSON(AnsiString);

  virtual ~Infos();

};
//----------------------------------

#endif
