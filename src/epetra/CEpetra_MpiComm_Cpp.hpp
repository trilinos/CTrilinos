#include "CTrilinos_config.h"


#ifdef HAVE_MPI


#include "CEpetra_MpiComm.h"
#include "Epetra_MpiComm.h"
#include "Teuchos_RCP.hpp"
#include "CTrilinos_enums.h"


#ifndef CEPETRA_MPICOMM_CPP_HPP
#define CEPETRA_MPICOMM_CPP_HPP


class Epetra_MpiComm;


namespace CEpetra {


using Teuchos::RCP;


const RCP<Epetra_MpiComm>
getMpiComm( CT_Epetra_MpiComm_ID_t id );

const RCP<Epetra_MpiComm>
getMpiComm( CTrilinos_Object_ID_t id );

CT_Epetra_MpiComm_ID_t
storeMpiComm( const Epetra_MpiComm *pobj );

void
purgeMpiCommTable(  );


} // namespace CEpetra


#endif // CEPETRA_MPICOMM_CPP_HPP


#endif /* HAVE_MPI */


