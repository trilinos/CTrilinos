#include "FEpetra_SerialComm.h"
#include "FEpetra_SerialComm_Cpp.hpp"
#include "Epetra_SerialComm.h"
#include "Epetra_SerialComm.h"
#include "Teuchos_Array.hpp"
#include "Teuchos_RCP.hpp"

namespace {
  using Teuchos::Array;
  using Teuchos::RCP;

  Array< RCP<const Epetra_SerialComm> >& tableOfSerialComms(){
    static Array< RCP<const Epetra_SerialComm> > loc_tableOfSerialComms;
    return loc_tableOfSerialComms;
  }
} // namespace

//
// Definitions from Epetra_SerialComm.h
//

#ifdef __cplusplus
extern "C" {
#endif
  FEpetra_SerialCommID Epetra_SerialComm_Create(){
    using Teuchos::rcp;
    Epetra_SerialComm  serialComm;
    tableOfSerialComms().push_back(rcp(new Epetra_SerialComm(serialComm)));
    return tableOfSerialComms().size() - 1;
  }

  void Epetra_Comm_Destroy( FEpetra_SerialCommID id ){
    tableOfSerialComms()[id] = Teuchos::null;
  }
#ifdef __cplusplus
} // extern "C"
#endif

//
// Definitions from Epetra_SerialComm_Cpp.hpp
//
const Teuchos::RCP<const Epetra_SerialComm> 
FEpetra::getSerialComm( FEpetra_SerialCommID id ){
  return tableOfSerialComms()[id];
}
