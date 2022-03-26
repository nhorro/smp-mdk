//
// Title:
//      IPublishOperation.h
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
//      This file defines the IPublishOperation interface.
//      This interface is used to publish parameters of operations.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PUBLICATION_IPUBLISHOPERATION_H
#define SMP_PUBLICATION_IPUBLISHOPERATION_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"
#include "Smp/Publication/ITypeRegistry.h"

// ---------------------------------------------------------------------------
// --------------------------- IPublishOperation interface -------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        // Forward declaration because of circular references.
        class IType;

        /// Publish operation parameters.
        /// Provide functionality to publish operation parameters.
        class IPublishOperation
        {
        public:
            /// Virtual destructor.
            /// This is needed to be able to destroy instances
            /// using the actual derived destructor.
            virtual ~IPublishOperation() { }

            /// Publish a parameter of an operation.
            /// @param name Parameter name.
            /// @param description Parameter description.
            /// @param typeUuid Uuid of parameter type.
            /// @remarks This method works for all types.
            virtual void PublishParameter(
                String8 name,
                String8 description,
                const Smp::Uuid typeUuid) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_IPUBLISHOPERATION_H

/***********
 * History *
 ***********/

//$Log: IPublishOperation.h,v $
//Revision 1.2  2006/09/27 11:44:13  nin
//SMP2 v1.2
// 

