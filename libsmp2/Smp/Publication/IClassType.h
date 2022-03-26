//
// Title:
//      IClassType.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Mapping
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines the IClassType interface.
//      This interface is used to define user-defined class types.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PUBLICATION_ICLASSTYPE_H
#define SMP_PUBLICATION_ICLASSTYPE_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/Publication/IStructureType.h"

// ---------------------------------------------------------------------------
// --------------------------- IClassType interface --------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        /// This interface defines a user defined class.
        class IClassType : public virtual IStructureType
        {
        };
    }
}

#endif //  SMP_PUBLICATION_ICLASSTYPE_H

/***********
 * History *
 ***********/

//$Log: IClassType.h,v $
//Revision 1.2  2006/09/27 11:44:12  nin
//SMP2 v1.2
// 

