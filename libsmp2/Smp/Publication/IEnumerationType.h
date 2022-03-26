//
// Title:
//      IEnumerationType.h
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
//      This file defines the IEnumerationType interface.
//      This interface is used to define a user-defined enumeration type.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PUBLICATION_IENUMERATIONTYPE_H
#define SMP_PUBLICATION_IENUMERATIONTYPE_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/Publication/IType.h"

// ---------------------------------------------------------------------------
// --------------------------- IEnumerationType interface --------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        /// This interface defines a user defined enumeration.
        class IEnumerationType : public virtual Smp::Publication::IType
        {
        public:
            virtual void AddLiteral(
                Smp::String8 name,
                Smp::String8 description,
                const Smp::Int32 value) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_IENUMERATIONTYPE_H

/***********
 * History *
 ***********/

//$Log: IEnumerationType.h,v $
//Revision 1.2  2006/09/27 11:44:13  nin
//SMP2 v1.2
// 

