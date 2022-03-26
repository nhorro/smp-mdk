//
// Title:
//      IStructureType.h
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
//      This file defines the IStructureType interface.
//      This is the interface to a user-defined structure type.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PUBLICATION_ISTRUCTURETYPE_H
#define SMP_PUBLICATION_ISTRUCTURETYPE_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/Publication/IType.h"

// ---------------------------------------------------------------------------
// --------------------------- IStructureType interface ----------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        /// This interface defines a user defined structure.
        class IStructureType : public virtual Smp::Publication::IType
        {
        public:
            /// Add a field to the Structure.
            /// @param name Name of field.
            /// @param description Description of field.
            /// @param uuid Uuid of Type of field.
            /// @param offset Memory offset of field relative to Structure.
            /// @param view View flag of field.
            /// @param state State flag of field.
            /// @param input Input flag of field.
            /// @param output Output flag of field.
            virtual void AddField(
                Smp::String8 name,
                Smp::String8 description,
                const Smp::Uuid uuid,
                const Smp::Int64 offset,
                const Smp::Bool view = true,
                const Smp::Bool state = true,
                const Smp::Bool input = false,
                const Smp::Bool output = false) = 0;
        };
    }
}

#endif //  SMP_PUBLICATION_ISTRUCTURETYPE_H

/***********
 * History *
 ***********/

//$Log: IStructureType.h,v $
//Revision 1.2  2006/09/27 11:44:13  nin
//SMP2 v1.2
// 

