// Example of class for combined parameters

#ifndef ROOT_MyParameters
#define ROOT_MyParameters

#include <map>
#include <string>

#include "TNamed.h"

class MyParameters : public TNamed {
private:
   Int_t                         fInt;       // An Int_t parameter
   Double_t                      fDouble;    // A Double_t parameter
   Bool_t                        fBool;      // A Bool_t parameter
   std::map<std::string,int>    fMapInt;    // A map of named ints
   std::map<std::string,double> fMapDouble; // A map of named doubles
   std::map<std::string,bool>   fMapBool;   // A map of named booleans

public:
   MyParameters(const char *s = "mypar") : TNamed(s,""), fInt(0), fDouble(0.), fBool(kFALSE) { }
   virtual ~MyParameters() { }

   // Getters
   Int_t TheInt() const { return fInt; }
   Double_t TheDouble() const { return fDouble; }
   Bool_t TheBool() const { return fBool; }
   Int_t TheNamedInt(std::string n, Int_t &i) {
      std::map<std::string,int>::iterator iter = fMapInt.find(n);
      if (iter != fMapInt.end()) { i = iter->second; return 0; }
      return -1;
   }
   Int_t TheNamedBool(std::string n, Bool_t &b) {
      std::map<std::string,bool>::iterator iter = fMapBool.find(n);
      if (iter != fMapBool.end()) { b = iter->second; return 0; }
      return -1;
   }
   Int_t TheNamedDouble(std::string n, Double_t &d) {
      std::map<std::string,double>::iterator iter = fMapDouble.find(n);
      if (iter != fMapDouble.end()) { d = iter->second; return 0; }
      return -1;
   }

   // Setters
   void SetInt(int i) { fInt = i; };
   void SetBool(bool b) { fBool = b; };
   void SetDouble(double d) { fDouble = d; };
   void SetNamedInt(std::string n, int i) { fMapInt[n] = i; }
   void SetNamedBool(std::string n, bool b) { fMapBool[n] = b; }
   void SetNamedDouble(std::string n, double d) { fMapDouble[n] = d; }

   // Dump content
   void DumpParms() {
      Printf(" +++++++++++++++ MyParameters ++++++++++++++++++++ ");
      Printf(" + Name: %s", GetName());
      Printf(" + Int: %d, Bool: %d, Double: %f", TheInt(), TheBool(), TheDouble());
      Printf(" + Named Int(s): %d", fMapInt.size());
      std::map<std::string,int>::iterator iti = fMapInt.begin();
      while (iti != fMapInt.end()) { Printf(" +   '%s' -> %d", iti->first.c_str(), iti->second); iti++; }
      Printf(" + Named Bool(s): %d", fMapBool.size());
      std::map<std::string,bool>::iterator itb = fMapBool.begin();
      while (itb != fMapBool.end()) { Printf(" +   '%s' -> %d", itb->first.c_str(), itb->second); itb++; }
      Printf(" + Named Double(s): %d", fMapDouble.size());
      std::map<std::string,double>::iterator itd = fMapDouble.begin();
      while (itd != fMapDouble.end()) { Printf(" +   '%s' -> %f", itd->first.c_str(), itd->second); itd++; }
      Printf(" +++++++++++++++++++++++++++++++++++++++++++++++++ ");
   }

   // We need to stream this class
   ClassDef(MyParameters, 1)  // Structure to define many parameters in one go
};

#endif
