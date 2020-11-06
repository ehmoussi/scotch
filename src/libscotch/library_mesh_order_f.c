/* Copyright 2004,2007,2010,2018 IPB, Universite de Bordeaux, INRIA & CNRS
**
** This file is part of the Scotch software package for static mapping,
** graph partitioning and sparse matrix ordering.
**
** This software is governed by the CeCILL-C license under French law
** and abiding by the rules of distribution of free software. You can
** use, modify and/or redistribute the software under the terms of the
** CeCILL-C license as circulated by CEA, CNRS and INRIA at the following
** URL: "http://www.cecill.info".
**
** As a counterpart to the access to the source code and rights to copy,
** modify and redistribute granted by the license, users are provided
** only with a limited warranty and the software's author, the holder of
** the economic rights, and the successive licensors have only limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading, using, modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean that it is complicated to manipulate, and that also
** therefore means that it is reserved for developers and experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards
** their requirements in conditions enabling the security of their
** systems and/or data to be ensured and, more generally, to use and
** operate it in the same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
*/
/************************************************************/
/**                                                        **/
/**   NAME       : library_mesh_order_f.c                  **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : This module is the Fortran API for the  **/
/**                mesh ordering routines of the libSCOTCH **/
/**                library.                                **/
/**                                                        **/
/**   DATES      : # Version 4.0  : from : 14 jan 2004     **/
/**                                 to   : 20 dec 2005     **/
/**                # Version 5.0  : from : 04 aug 2007     **/
/**                                 to   : 04 aug 2007     **/
/**                # Version 5.1  : from : 27 mar 2010     **/
/**                                 to   : 25 jul 2010     **/
/**                # Version 6.0  : from : 20 apr 2018     **/
/**                                 to   : 25 apr 2018     **/
/**                                                        **/
/************************************************************/

/*
**  The defines and includes.
*/

#define LIBRARY

#include "module.h"
#include "common.h"
#include "scotch.h"

/**************************************/
/*                                    */
/* These routines are the Fortran API */
/* for the ordering routines.         */
/*                                    */
/**************************************/

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDERINIT, meshorderinit, (       \
const SCOTCH_Mesh * const   meshptr,  \
SCOTCH_Ordering * const     ordeptr,  \
SCOTCH_Num * const          permtab,  \
SCOTCH_Num * const          peritab,  \
SCOTCH_Num * const          cblkptr,  \
SCOTCH_Num * const          rangtab,  \
SCOTCH_Num * const          treetab,  \
int * const                 revaptr), \
(meshptr, ordeptr, permtab, peritab,  \
 cblkptr, rangtab, treetab, revaptr))
{
  *revaptr = SCOTCH_meshOrderInit (meshptr, ordeptr, permtab, peritab, cblkptr, rangtab, treetab);
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDEREXIT, meshorderexit, (       \
const SCOTCH_Mesh * const   meshptr,  \
SCOTCH_Ordering * const     ordeptr), \
(meshptr, ordeptr))
{
  SCOTCH_meshOrderExit (meshptr, ordeptr);
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDERSAVE, meshordersave, (       \
const SCOTCH_Mesh * const   meshptr,  \
SCOTCH_Ordering * const     ordeptr,  \
int * const                 fileptr,  \
int * const                 revaptr), \
(meshptr, ordeptr, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (MESHORDERSAVE)) ": cannot duplicate handle");

    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "w")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (MESHORDERSAVE)) ": cannot open output stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_meshOrderSave (meshptr, ordeptr, stream);

  fclose (stream);                                /* This closes filenum too */

  *revaptr = o;
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDERSAVEMAP, meshordersavemap, ( \
const SCOTCH_Mesh * const   meshptr,  \
SCOTCH_Ordering * const     ordeptr,  \
int * const                 fileptr,  \
int * const                 revaptr), \
(meshptr, ordeptr, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (MESHORDERSAVEMAP)) ": cannot duplicate handle");

    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "w")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (MESHORDERSAVEMAP)) ": cannot open output stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_meshOrderSaveMap (meshptr, ordeptr, stream);

  fclose (stream);                                /* This closes filenum too */

  *revaptr = o;
}

/*
**
*/

SCOTCH_FORTRAN (                        \
MESHORDERSAVETREE, meshordersavetree, ( \
const SCOTCH_Mesh * const   meshptr,    \
SCOTCH_Ordering * const     ordeptr,    \
int * const                 fileptr,    \
int * const                 revaptr),   \
(meshptr, ordeptr, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (MESHORDERSAVETREE)) ": cannot duplicate handle");

    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "w")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (MESHORDERSAVETREE)) ": cannot open output stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_meshOrderSaveTree (meshptr, ordeptr, stream);

  fclose (stream);                                /* This closes filenum too */

  *revaptr = o;
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDERCOMPUTE, meshordercompute, ( \
SCOTCH_Mesh * const         meshptr,  \
SCOTCH_Ordering * const     ordeptr,  \
SCOTCH_Strat * const        straptr,  \
int * const                 revaptr), \
(meshptr, ordeptr, straptr, revaptr))
{
  *revaptr = SCOTCH_meshOrderCompute (meshptr, ordeptr, straptr);
}

/*
**
*/

SCOTCH_FORTRAN (                              \
MESHORDERCOMPUTELIST, meshordercomputelist, ( \
SCOTCH_Mesh * const         meshptr,          \
SCOTCH_Ordering * const     ordeptr,          \
const SCOTCH_Num *          listptr,          \
const SCOTCH_Num * const    listtab,          \
SCOTCH_Strat * const        straptr,          \
int * const                 revaptr),         \
(meshptr, ordeptr, listptr, listtab, straptr, revaptr))
{
  *revaptr = SCOTCH_meshOrderComputeList (meshptr, ordeptr, *listptr, listtab, straptr);
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDER, meshorder, (               \
SCOTCH_Mesh * const         meshptr,  \
SCOTCH_Strat * const        straptr,  \
SCOTCH_Num * const          permtab,  \
SCOTCH_Num * const          peritab,  \
SCOTCH_Num * const          cblkptr,  \
SCOTCH_Num * const          rangtab,  \
SCOTCH_Num * const          treetab,  \
int * const                 revaptr), \
(meshptr, straptr, permtab, peritab,  \
 cblkptr, rangtab, treetab, revaptr))
{
  *revaptr = SCOTCH_meshOrder (meshptr, straptr, permtab, peritab, cblkptr, rangtab, treetab);
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDERLIST, meshorderlist, (       \
SCOTCH_Mesh * const         meshptr,  \
const SCOTCH_Num *          listptr,  \
const SCOTCH_Num * const    listtab,  \
SCOTCH_Strat * const        straptr,  \
SCOTCH_Num * const          permtab,  \
SCOTCH_Num * const          peritab,  \
SCOTCH_Num * const          cblkptr,  \
SCOTCH_Num * const          rangtab,  \
SCOTCH_Num * const          treetab,  \
int * const                 revaptr), \
(meshptr, listptr, listtab, straptr,  \
 permtab, peritab, cblkptr, rangtab, treetab, revaptr))
{
  *revaptr = SCOTCH_meshOrderList (meshptr, *listptr, listtab, straptr, permtab, peritab, cblkptr, rangtab, treetab);
}

/*
**
*/

SCOTCH_FORTRAN (                      \
MESHORDERCHECK, meshordercheck, (     \
const SCOTCH_Mesh * const   meshptr,  \
SCOTCH_Ordering * const     ordeptr,  \
int * const                 revaptr), \
(meshptr, ordeptr, revaptr))
{
  *revaptr = SCOTCH_meshOrderCheck (meshptr, ordeptr);
}

/*
**
*/

SCOTCH_FORTRAN (                     \
STRATMESHORDER, stratmeshorder, (    \
SCOTCH_Strat * const        straptr, \
const char * const          string,  \
int * const                 revaptr, \
const int                   strnbr), \
(straptr, string, revaptr, strnbr))
{
  char * restrict     strtab;                     /* Pointer to null-terminated string */

  if ((strtab = (char *) memAlloc (strnbr + 1)) == NULL) { /* Allocate temporary space */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (STRATMESHORDER)) ": out of memory");
    *revaptr = 1;
    return;
  }
  memCpy (strtab, string, strnbr);                /* Copy string contents */
  strtab[strnbr] = '\0';                          /* Terminate string     */

  *revaptr = SCOTCH_stratMeshOrder (straptr, strtab); /* Call original routine */

  memFree (strtab);                               /* Prevent compiler warnings */
}

/*
**
*/

SCOTCH_FORTRAN (                            \
STRATMESHORDERBUILD, stratmeshorderbuild, ( \
SCOTCH_Strat * const        straptr,        \
const SCOTCH_Num * const    flagval,        \
const double * const        balrat,         \
int * const                 revaptr),       \
(straptr, flagval, balrat, revaptr))
{
  *revaptr = SCOTCH_stratMeshOrderBuild (straptr, *flagval, *balrat);
}
