//
// Title:
//      ITypeRegistry.h
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
//      This file defines the ITypeRegistry interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_PUBLICATION_ITYPEREGISTRY_H
#define SMP_PUBLICATION_ITYPEREGISTRY_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/SimpleTypes.h"
#include "Smp/Publication/IType.h"
#include "Smp/Publication/IEnumerationType.h"
#include "Smp/Publication/IStructureType.h"
#include "Smp/Publication/IClassType.h"
#include "Smp/Exceptions.h"

// ---------------------------------------------------------------------------
// --------------------------- Constant Declarations -------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        // --------------------------------------------------------------------
        // These are the type identifiers of the predefined primitive types.
        // --------------------------------------------------------------------
        static const Uuid Uuid_Void     = { 0, 0, 0, { ' ',' ',' ',' ','V','o','i','d'} };
        static const Uuid Uuid_Char8    = { 0, 0, 0, { ' ',' ',' ','C','h','a','r','8'} };
        static const Uuid Uuid_Bool     = { 0, 0, 0, { ' ',' ',' ',' ','B','o','o','l'} };
        static const Uuid Uuid_Int8     = { 0, 0, 0, { ' ',' ',' ',' ','I','n','t','8'} };
        static const Uuid Uuid_Int16    = { 0, 0, 0, { ' ',' ',' ','I','n','t','1','6'} };
        static const Uuid Uuid_Int32    = { 0, 0, 0, { ' ',' ',' ','I','n','t','3','2'} };
        static const Uuid Uuid_Int64    = { 0, 0, 0, { ' ',' ',' ','I','n','t','6','4'} };
        static const Uuid Uuid_UInt8    = { 0, 0, 0, { ' ',' ',' ','U','I','n','t','8'} };
        static const Uuid Uuid_UInt16   = { 0, 0, 0, { ' ',' ','U','I','n','t','1','6'} };
        static const Uuid Uuid_UInt32   = { 0, 0, 0, { ' ',' ','U','I','n','t','3','2'} };
        static const Uuid Uuid_UInt64   = { 0, 0, 0, { ' ',' ','U','I','n','t','6','4'} };
        static const Uuid Uuid_Float32  = { 0, 0, 0, { ' ','F','l','o','a','t','3','2'} };
        static const Uuid Uuid_Float64  = { 0, 0, 0, { ' ','F','l','o','a','t','6','4'} };
        static const Uuid Uuid_DateTime = { 0, 0, 0, { 'D','a','t','e','T','i','m','e'} };
        static const Uuid Uuid_Duration = { 0, 0, 0, { 'D','u','r','a','t','i','o','n'} };
        static const Uuid Uuid_String8  = { 0, 0, 0, { ' ','S','t','r','i','n','g','8'} };
    }
}

// ---------------------------------------------------------------------------
// --------------------------- NotRegistered exception -----------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        static const Smp::String8 NotRegisteredTemplate = "Type with Uuid = {%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X} has not been registered";

        /// A type with the given Uuid has not been registered.
        class NotRegistered : public Smp::Exception
        {
        public:
            /// Uuid that does not correspond to a registered type.
            Uuid uuid;

            NotRegistered(
                Uuid _uuid) :
            Smp::Exception("NotRegistered"),
                uuid(_uuid)
            {
                description = new Char8[strlen(NotRegisteredTemplate)];

                sprintf(description, NotRegisteredTemplate, 
                    uuid.Data1,
                    uuid.Data2,
                    uuid.Data3,
                    uuid.Data4[0],
                    uuid.Data4[1],
                    uuid.Data4[2],
                    uuid.Data4[3],
                    uuid.Data4[4],
                    uuid.Data4[5],
                    uuid.Data4[6],
                    uuid.Data4[7]);
            }
            ~NotRegistered() {}
        };
    }
}

// ---------------------------------------------------------------------------
// --------------------------- AlreadyRegistered exception -------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        static const Smp::String8 AlreadyRegisteredTemplate   = "Type '%s' uses Uuid that has been used by Type '%s' already";

        /// A type with the same Uuid has already been registered.
        class AlreadyRegistered : public Smp::Exception
        {
        public:
            /// Name of new type that cannot be registered.
            String8 name;
            /// Type that uses the same Uuid already
            IType* type;

            AlreadyRegistered(
                String8 _name,
                IType* _type) :
            Smp::Exception("AlreadyRegistered"),
                name(_name),
                type(_type)
            {
                description = new Char8[strlen(AlreadyRegisteredTemplate) 
                    + strlen(name)
                    + strlen(type->GetName())];

                sprintf(description, AlreadyRegisteredTemplate, 
                    name,
                    type->GetName());
            }
            ~AlreadyRegistered() {}
        };
    }
}

// ---------------------------------------------------------------------------
// --------------------------- ITypeRegistry interface -----------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    namespace Publication
    {
        /// This interface defines a registration mechanism for user types.
        class ITypeRegistry
        {
        public:
            /// Virtual destructor.
            /// This is needed to be able to destroy instances
            /// using the actual derived destructor.
            virtual ~ITypeRegistry() { }

            // -----------------------------------------------------------------
            // Type query mechanism
            // -----------------------------------------------------------------

            /// Returns a type by its simple type kind.
            /// @param   type   Primitive type the type is requested for.
            /// @return  Interface to the requested type.
            /// @remarks This method can be used to map primitive types to the 
            ///          IType interface, to treat all types identically.
            virtual IType* GetType(const SimpleTypeKind type) const = 0;

            /// Returns a type by universally unique identifier.
            /// @param   typeUuid   Universally unique identifier for the 
            ///          requested type.
            /// @return  Interface of the requested type, or null if no type
            ///          with the registered Uuid could be found.
            /// @remarks This method can be used to find out whether a specific
            ///          type has been registered before.
            virtual IType* GetType(const Uuid typeUuid) const = 0;

            // -----------------------------------------------------------------
            // Type registration mechanism
            // -----------------------------------------------------------------

            /// Add a float type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @param   minimum    Minimum value for float.
            /// @param   maximum    Maximum value for float.
            /// @param   minInclusive   Flag whether the minimum value for
            ///          float is valid or not.
            /// @param   maxInclusive   Flag whether the maximum value for
            ///          float is valid or not.
            /// @param   unit   Unit of the type.
            /// @param   type   Primitive type to use for Float type.
            /// @return  Interface to new type.
            /// @remarks IManagedModel and IDynamicInvocation support fields,
            ///          parameters and operations of Float types via the
            ///          ST_Float32 and ST_Float64 primitive type, as a Float
            ///          is mapped either to Float32 or Float64.
            virtual const IType* AddFloatType(
                String8 name,
                String8 description,
                const Uuid typeUuid,
                const Float64 minimum,
                const Float64 maximum,
                const Bool minInclusive,
                const Bool maxInclusive,
                String8 unit,
                const SimpleTypeKind type = ST_Float64) = 0;

            /// Add an integer type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @param   minimum    Minimum value for integer.
            /// @param   maximum    Maximum value for integer.
            /// @param   type   Primitive type to use for Integer type.
            /// @return  Interface to new type.
            /// @remarks IManagedModel and IDynamicInvocation support fields,
            ///          parameters and operations of Integer types via the
            ///          ST_Int primitive types, as an Integer is mapped to
            ///          one of Int8/Int16/Int32/Int64/UInt8/UInt16/UInt32.
            virtual const IType* AddIntegerType(
                String8 name,
                String8 description,
                const Uuid typeUuid,
                const Int64 minimum,
                const Int64 maximum,
                const SimpleTypeKind type = ST_Int32) = 0;

            /// Add an enumeration type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @param   memorySize Size of an instance of this enumeration in
            ///          bytes. Valid values are 1, 2, 4, 8
            /// @return  Interface to new type that allows enumeration literals.
            /// @remarks Fields, parameters and operations of Enumeration types
            ///          are supported by IManagedModel and IDynamicInvocation
            ///          via one of the ST_Int8, ST_Int16, ST_Int32 or ST_Int64
            ///          primitive types, depending on their memory size.
            virtual IEnumerationType* AddEnumerationType(
                String8 name,
                String8 description,
                const Uuid typeUuid,
                const Int16 memorySize) = 0;

            /// Add an array type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @param   itemTypeUuid   Universally unique identifier of the
            ///          Type of the array items.
            /// @param   itemSize   Size of an array item in bytes.
            /// @param   arrayCount Number of elements in the array.
            /// @return  Interface to new typ.
            /// @remarks None.
            virtual const IType* AddArrayType(
                String8 name,
                String8 description,
                const Uuid typeUuid,
                const Uuid itemTypeUuid,
                const Int64 itemSize,
                const Int64 arrayCount) = 0;

            /// Add a string type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @param   length Maximum length of the string.
            /// @return  Interface to new type.
            /// @remarks None.
            virtual const IType* AddStringType(
                String8 name,
                String8 description,
                const Uuid typeUuid,
                const Int64 length) = 0;

            /// Add a structure type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @return  Interface to new type that allows adding fields.
            /// @remarks None.
            virtual IStructureType* AddStructureType(
                String8 name,
                String8 description,
                const Uuid typeUuid) = 0;

            /// Add a class type to the registry.
            /// @param   name   Name of the registered type.
            /// @param   description    Description of the registered type.
            /// @param   typeUuid   Universally unique identifier of the
            ///          registered type.
            /// @param   baseClassUuid  Universally unique identifier of the 
            ///          Base class.
            /// @return  Interface to new type that allows adding fields and
            ///          operations.
            /// @remarks None.
            virtual IClassType* AddClassType(
                String8 name,
                String8 description,
                const Uuid typeUuid,
                const Smp::Uuid baseClassUuid) = 0;
        };
    }
}

#endif // SMP_PUBLICATION_ITYPEREGISTRY_H

/***********
 * History *
 ***********/

//$Log: ITypeRegistry.h,v $
//Revision 1.3  2006/12/21 16:02:53  nin
//Uuid_String8 added.
//
//Revision 1.2  2006/09/27 11:44:13  nin
//SMP2 v1.2
// 

