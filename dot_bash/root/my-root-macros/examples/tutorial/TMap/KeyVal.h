#ifndef KEYVAL
#define KEYVAL


#include "TObject.h"

class aKey : public TObject {
private:
  Int_t m_key;
public:
  aKey(Int_t Key);
  aKey() {m_key = 0;};
  virtual ~aKey();
  Int_t GetKey();
  ClassDef(aKey,1)
};

class McPart: public TObject {
 private:
  Int_t m_type;
 public:
  McPart(Int_t type);
  McPart() {m_type=0;};
  virtual ~McPart();
  Int_t GetType();
  ClassDef(McPart,1)
};

class aVal : public TObject {
private:
  Float_t m_val;
  McPart* m_mcp;
public:
  aVal(Float_t Val, McPart* McPart);
  aVal() {m_val=0.; m_mcp = 0;};
  virtual ~aVal();
  Float_t GetVal();
  McPart* GetMcPart();
  ClassDef(aVal,1)
};


#endif
