
/*! @HEADER */
/*
************************************************************************

                CTrilinos:  C interface to Trilinos
                Copyright (2009) Sandia Corporation

Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
license for use of this work by or on behalf of the U.S. Government.

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
USA
Questions? Contact M. Nicole Lemaster (mnlemas@sandia.gov)

************************************************************************
*/
/*! @HEADER */


#include "CTrilinos_config.h"

#include "CTrilinos_enums.h"
#include "CEpetra_SerialDenseVector.h"
#include "CEpetra_SerialDenseVector_Cpp.hpp"
#include "Epetra_SerialDenseVector.h"
#include "Teuchos_RCP.hpp"
#include "CTrilinos_utils.hpp"
#include "CTrilinos_utils_templ.hpp"
#include "CTrilinos_TableRepos.hpp"


namespace {


using Teuchos::RCP;
using CTrilinos::Table;


/* table to hold objects of type Epetra_SerialDenseVector */
Table<Epetra_SerialDenseVector>& tableOfSerialDenseVectors()
{
    static Table<Epetra_SerialDenseVector> loc_tableOfSerialDenseVectors(CT_Epetra_SerialDenseVector_ID);
    return loc_tableOfSerialDenseVectors;
}


} // namespace


//
// Definitions from CEpetra_SerialDenseVector.h
//


extern "C" {


CT_Epetra_SerialDenseVector_ID_t Epetra_SerialDenseVector_Degeneralize ( 
  CTrilinos_Universal_ID_t id )
{
    return CTrilinos::concreteType<CT_Epetra_SerialDenseVector_ID_t>(id);
}

CTrilinos_Universal_ID_t Epetra_SerialDenseVector_Generalize ( 
  CT_Epetra_SerialDenseVector_ID_t id )
{
    return CTrilinos::abstractType<CT_Epetra_SerialDenseVector_ID_t>(id);
}

CT_Epetra_SerialDenseVector_ID_t Epetra_SerialDenseVector_Create_Empty ( 
   )
{
    return CEpetra::storeNewSerialDenseVector(new Epetra_SerialDenseVector());
}

CT_Epetra_SerialDenseVector_ID_t Epetra_SerialDenseVector_Create ( 
  int Length )
{
    return CEpetra::storeNewSerialDenseVector(new Epetra_SerialDenseVector(
        Length));
}

CT_Epetra_SerialDenseVector_ID_t Epetra_SerialDenseVector_Create_FromArray ( 
  CT_Epetra_DataAccess_E_t CV, double * Values, int Length )
{
    return CEpetra::storeNewSerialDenseVector(new Epetra_SerialDenseVector(
        (Epetra_DataAccess) CV, Values, Length));
}

CT_Epetra_SerialDenseVector_ID_t Epetra_SerialDenseVector_Duplicate ( 
  CT_Epetra_SerialDenseVector_ID_t SourceID )
{
    const Teuchos::RCP<const Epetra_SerialDenseVector> Source = 
        CEpetra::getConstSerialDenseVector(SourceID);
    return CEpetra::storeNewSerialDenseVector(new Epetra_SerialDenseVector(
        *Source));
}

void Epetra_SerialDenseVector_Destroy ( 
  CT_Epetra_SerialDenseVector_ID_t * selfID )
{
    CEpetra::removeSerialDenseVector(selfID);
}

int Epetra_SerialDenseVector_Size ( 
  CT_Epetra_SerialDenseVector_ID_t selfID, int Length_in )
{
    return CEpetra::getSerialDenseVector(selfID)->Size(Length_in);
}

int Epetra_SerialDenseVector_Resize ( 
  CT_Epetra_SerialDenseVector_ID_t selfID, int Length_in )
{
    return CEpetra::getSerialDenseVector(selfID)->Resize(Length_in);
}

int Epetra_SerialDenseVector_Random ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return CEpetra::getSerialDenseVector(selfID)->Random();
}

double Epetra_SerialDenseVector_Dot ( 
  CT_Epetra_SerialDenseVector_ID_t selfID, 
  CT_Epetra_SerialDenseVector_ID_t xID )
{
    const Teuchos::RCP<const Epetra_SerialDenseVector> x = 
        CEpetra::getConstSerialDenseVector(xID);
    return CEpetra::getConstSerialDenseVector(selfID)->Dot(*x);
}

double Epetra_SerialDenseVector_Norm1 ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return CEpetra::getConstSerialDenseVector(selfID)->Norm1();
}

double Epetra_SerialDenseVector_Norm2 ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return CEpetra::getConstSerialDenseVector(selfID)->Norm2();
}

double Epetra_SerialDenseVector_NormInf ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return CEpetra::getConstSerialDenseVector(selfID)->NormInf();
}

int Epetra_SerialDenseVector_Length ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return CEpetra::getConstSerialDenseVector(selfID)->Length();
}

double * Epetra_SerialDenseVector_Values ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return CEpetra::getConstSerialDenseVector(selfID)->Values();
}

CT_Epetra_DataAccess_E_t Epetra_SerialDenseVector_CV ( 
  CT_Epetra_SerialDenseVector_ID_t selfID )
{
    return (CT_Epetra_DataAccess_E_t)( CEpetra::getConstSerialDenseVector(
        selfID)->CV() );
}

void Epetra_SerialDenseVector_Assign ( 
  CT_Epetra_SerialDenseVector_ID_t selfID, 
  CT_Epetra_SerialDenseVector_ID_t SourceID )
{
    Epetra_SerialDenseVector& self = *( CEpetra::getSerialDenseVector(
        selfID) );

    const Teuchos::RCP<const Epetra_SerialDenseVector> Source = 
        CEpetra::getConstSerialDenseVector(SourceID);
    self = *Source;
}

void Epetra_SerialDenseVector_setElement ( 
  CT_Epetra_SerialDenseVector_ID_t selfID, int Index, 
  double * value )
{
    Epetra_SerialDenseVector& self = *( CEpetra::getSerialDenseVector(
        selfID) );

    self(Index) = *value;
}

double Epetra_SerialDenseVector_getElement ( 
  CT_Epetra_SerialDenseVector_ID_t selfID, int Index )
{
    const Epetra_SerialDenseVector& self = *( 
        CEpetra::getConstSerialDenseVector(selfID) );

    return self(Index);
}


} // extern "C"


//
// Definitions from CEpetra_SerialDenseVector_Cpp.hpp
//


/* get Epetra_SerialDenseVector from non-const table using CT_Epetra_SerialDenseVector_ID */
const Teuchos::RCP<Epetra_SerialDenseVector>
CEpetra::getSerialDenseVector( CT_Epetra_SerialDenseVector_ID_t id )
{
    if (tableOfSerialDenseVectors().isType(id.table))
        return tableOfSerialDenseVectors().get<Epetra_SerialDenseVector>(
        CTrilinos::abstractType<CT_Epetra_SerialDenseVector_ID_t>(id));
    else
        return CTrilinos::TableRepos::get<Epetra_SerialDenseVector>(
        CTrilinos::abstractType<CT_Epetra_SerialDenseVector_ID_t>(id));
}

/* get Epetra_SerialDenseVector from non-const table using CTrilinos_Universal_ID_t */
const Teuchos::RCP<Epetra_SerialDenseVector>
CEpetra::getSerialDenseVector( CTrilinos_Universal_ID_t id )
{
    if (tableOfSerialDenseVectors().isType(id.table))
        return tableOfSerialDenseVectors().get<Epetra_SerialDenseVector>(id);
    else
        return CTrilinos::TableRepos::get<Epetra_SerialDenseVector>(id);
}

/* get const Epetra_SerialDenseVector from either the const or non-const table
 * using CT_Epetra_SerialDenseVector_ID */
const Teuchos::RCP<const Epetra_SerialDenseVector>
CEpetra::getConstSerialDenseVector( CT_Epetra_SerialDenseVector_ID_t id )
{
    if (tableOfSerialDenseVectors().isType(id.table))
        return tableOfSerialDenseVectors().getConst<Epetra_SerialDenseVector>(
        CTrilinos::abstractType<CT_Epetra_SerialDenseVector_ID_t>(id));
    else
        return CTrilinos::TableRepos::getConst<Epetra_SerialDenseVector>(
        CTrilinos::abstractType<CT_Epetra_SerialDenseVector_ID_t>(id));
}

/* get const Epetra_SerialDenseVector from either the const or non-const table
 * using CTrilinos_Universal_ID_t */
const Teuchos::RCP<const Epetra_SerialDenseVector>
CEpetra::getConstSerialDenseVector( CTrilinos_Universal_ID_t id )
{
    if (tableOfSerialDenseVectors().isType(id.table))
        return tableOfSerialDenseVectors().getConst<Epetra_SerialDenseVector>(id);
    else
        return CTrilinos::TableRepos::getConst<Epetra_SerialDenseVector>(id);
}

/* store Epetra_SerialDenseVector (owned) in non-const table */
CT_Epetra_SerialDenseVector_ID_t
CEpetra::storeNewSerialDenseVector( Epetra_SerialDenseVector *pobj )
{
    return CTrilinos::concreteType<CT_Epetra_SerialDenseVector_ID_t>(
        tableOfSerialDenseVectors().store<Epetra_SerialDenseVector>(pobj, true));
}

/* store Epetra_SerialDenseVector in non-const table */
CT_Epetra_SerialDenseVector_ID_t
CEpetra::storeSerialDenseVector( Epetra_SerialDenseVector *pobj )
{
    return CTrilinos::concreteType<CT_Epetra_SerialDenseVector_ID_t>(
        tableOfSerialDenseVectors().store<Epetra_SerialDenseVector>(pobj, false));
}

/* store const Epetra_SerialDenseVector in const table */
CT_Epetra_SerialDenseVector_ID_t
CEpetra::storeConstSerialDenseVector( const Epetra_SerialDenseVector *pobj )
{
    return CTrilinos::concreteType<CT_Epetra_SerialDenseVector_ID_t>(
        tableOfSerialDenseVectors().store<Epetra_SerialDenseVector>(pobj, false));
}

/* remove Epetra_SerialDenseVector from table using CT_Epetra_SerialDenseVector_ID */
void
CEpetra::removeSerialDenseVector( CT_Epetra_SerialDenseVector_ID_t *id )
{
    CTrilinos_Universal_ID_t aid = 
        CTrilinos::abstractType<CT_Epetra_SerialDenseVector_ID_t>(*id);
    if (tableOfSerialDenseVectors().isType(aid.table))
        tableOfSerialDenseVectors().remove(&aid);
    else
        CTrilinos::TableRepos::remove(&aid);
    *id = CTrilinos::concreteType<CT_Epetra_SerialDenseVector_ID_t>(aid);
}

/* remove Epetra_SerialDenseVector from table using CTrilinos_Universal_ID_t */
void
CEpetra::removeSerialDenseVector( CTrilinos_Universal_ID_t *aid )
{
    if (tableOfSerialDenseVectors().isType(aid->table))
        tableOfSerialDenseVectors().remove(aid);
    else
        CTrilinos::TableRepos::remove(aid);
}

/* purge Epetra_SerialDenseVector table */
void
CEpetra::purgeSerialDenseVector(  )
{
    tableOfSerialDenseVectors().purge();
}

/* store Epetra_SerialDenseVector in non-const table */
CTrilinos_Universal_ID_t
CEpetra::aliasSerialDenseVector( const Teuchos::RCP< Epetra_SerialDenseVector > & robj )
{
    return tableOfSerialDenseVectors().alias(robj);
}

/* store const Epetra_SerialDenseVector in const table */
CTrilinos_Universal_ID_t
CEpetra::aliasConstSerialDenseVector( const Teuchos::RCP< const Epetra_SerialDenseVector > & robj )
{
    return tableOfSerialDenseVectors().alias(robj);
}



