#include "KeyVal.h"

ClassImp(aKey)

     aKey::aKey(Int_t Key) {
     m_key = Key;
     };
     aKey::~aKey() {};
     Int_t aKey::GetKey() { return m_key;};

ClassImp(McPart)

      McPart::McPart(Int_t Type) {
     m_type = Type;
     };
      McPart::~McPart() {};
      Int_t McPart::GetType() { return m_type;};

ClassImp(aVal)

     aVal::aVal(Float_t Val, McPart* McPart) {
     m_val = Val;
     m_mcp = McPart;
     };
     aVal::~aVal() {};
     Float_t aVal::GetVal() { return m_val;};
     McPart* aVal::GetMcPart() {return m_mcp;}
