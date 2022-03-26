//
// Title:
//      IType.h
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
//      This file defines the IType interface.
//      This is the base interface for types in the type registry.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PUBLICATION_ITYPE_H
#define SMP_PUBLICATION_ITYPE_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/IObject.h"

// ---------------------------------------------------------------------------
// --------------------------- IType interface -------------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    // Forward declaration for circular references.
    class IPublication;

    namespace Publication
    {
        /// This base interface defines a type in the type registry.
        class IType : public virtual Smp::IObject
        {
        public:
            /// Get simple type that this type describes.
            virtual Smp::SimpleTypeKind GetSimpleType() const = 0;

            /// Get Universally Unique Identifier of type.
            virtual const Smp::Uuid GetUuid() const = 0;

            /// Publish an instance of the type against a receiver.
            virtual void Publish(
                Smp::IPublication* receiver,
                Smp::String8 name,
                Smp::String8 description,
                void* address,
                const Smp::Bool view,
                const Smp::Bool state,
                const Smp::Bool input,
                const Smp::Bool output) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_ITYPE_H

/***********
 * History *
 ***********/

//$Log: IType.h,v $
//Revision 1.2  2006/09/27 11:44:13  nin
//SMP2 v1.2
// 

