#include "TList.h"
#include "TProof.h"

#include "MyParameters.h"

void testMyParms(const char *master = "")
{
    // Create the parameters object
    MyParameters *mp = new MyParameters("set1");
    mp->SetInt(1); mp->SetDouble(99.5);
    mp->SetNamedInt("i1", 4); mp->SetNamedInt("i2", 5); mp->SetNamedInt("i3", 6);
    mp->SetNamedBool("b1", 1);
    mp->SetNamedDouble("d1", 11.); mp->SetNamedDouble("d2", 22.);

    // Start PROOF
    TProof *p = TProof::Open(master);
    if (!p || !p->IsValid()) {
       Printf("Could not start Proof!");
       return;
    }

    // Load the parameter class on master and workers
    p->Load("MyParameters.h+", kTRUE);

    // Add the set of parameters to the input lists
    p->AddInput(mp);

    // Run the test selector
    p->Process("ProofParms.C+", 1);
}

