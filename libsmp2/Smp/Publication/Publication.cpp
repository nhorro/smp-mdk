#include "Publication.h"

namespace Smp
{

namespace Implementation
{    


Publication::Publication()
{

}


Publication::~Publication()
{
    
}

// ---------------------------------------------------------------------
// Type registration mechanism
// ---------------------------------------------------------------------

/// Give access to the global type registry.
/// @return Reference to global type registry.
/// @remarks The type registry is typically a singleton, and must not
///          be null, to allow use of existing types, and registration 
///          of new types.
Smp::Publication::ITypeRegistry* Publication::GetTypeRegistry() const
{
    // FIXME
    return nullptr;
}

// ---------------------------------------------------------------------
// Simple field publication mechanism
// ---------------------------------------------------------------------
/// Publish Char8 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Char8* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}

/// Publish a Bool field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Bool* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}

/// Publish Int8 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Int8* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}

/// Publish Int16 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Int16* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish Int32 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Int32* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish Int64 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Int64* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish UInt8 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    UInt8* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish UInt16 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    UInt16* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish UInt32 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    UInt32* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    this->m_publishedFields[name] = PublishedField{
            name,
            description,
            address,
            view,
            state,
            input,
            output
    };
}    

/// Publish UInt64 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    UInt64* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish Float32 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Float32* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish Float64 field.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    Float64* address,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

// ---------------------------------------------------------------------
// Field publication mechanism
// ---------------------------------------------------------------------
/// Publish field of any type.
/// @param name Field name.
/// @param description Field description.
/// @param address Field memory address.
/// @param typeUuid Uuid of field type (determines the size).
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishField(
    String8 name,
    String8 description,
    void* address,
    const Smp::Uuid typeUuid,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish array of simple type.
/// @param name Array name.
/// @param description Array description.
/// @param count Size of array.
/// @param address Array field memory address.
/// @param type Array item type.
/// @param view Show field in model tree.
/// @param state Include field in store/restore of simulation state.
/// @param input True if field is an input field, false otherwise.
/// @param output True if field is an output field, false otherwise.
void Publication::PublishArray(
    String8 name,
    String8 description,
    const Int64 count,
    void* address,
    const SimpleTypeKind type,
    const Bool view,
    const Bool state,
    const Bool input,
    const Bool output)
{
    //FIXME
}    

/// Publish array of any type.
/// @param name Array name.
/// @param description Array description.
IPublication* Publication::PublishArray(
    String8 name,
    String8 description)
{
    //FIXME
    return this;
}    

/// Publish structure.
/// @param name Structure name.
/// @param description Structure description.
IPublication* Publication::PublishStructure(
    String8 name,
    String8 description)
{
    //FIXME
    return this;
}    

// ---------------------------------------------------------------------
// Operation publication mechanism
// ---------------------------------------------------------------------

/// Publish an operation with complex return type.
/// @param name Operation name.
/// @param description Operation description.
/// @param returnTypeUuid Uuid of return type of operation.
/// @return  Reference to publish parameters against.
/// @remarks The operation parameters may be published
///          against the returned IPublishOperation interface
///          after calling PublishOperation().
Smp::Publication::IPublishOperation* Publication::PublishOperation(
    String8 name,
    String8 description,
    const Smp::Uuid returnTypeUuid)
{
    //FIXME
    return nullptr;
}    

// ---------------------------------------------------------------------
// Property publication mechanism
// ---------------------------------------------------------------------

/// Publish a property.
/// @param   name Property name.
/// @param   description Property description.
/// @param   typeUuid Uuid of type of Property.
/// @param   accessKind Access kind of Property
void Publication::PublishProperty(
    String8 name,
    String8 description,
    const Smp::Uuid typeUuid,
    const AccessKind accessKind)
{
    //FIXME
}    

// ---------------------------------------------------------------------
// Managed Model method implementation
// ---------------------------------------------------------------------

/// Get the value of a field which is typed by a system type.
/// @param   fullName Fully qualified field name.
/// @return  Field value.
/// @remarks This method can only be used to get values of simple
///          fields. For setting values of structured fields,
///          this method may be called multiply, e.g. specifying
///          "Position.x" to get the x component of a position.
///          For arrays of simple type, use GetArrayValue.
AnySimple Publication::GetFieldValue(String8 fullName)
{
    //FIXME
    Smp::AnySimple none;
    return none;
}

/// Set the value of a field which is typed by a system type.
/// @param   fullName Fully qualified field name.
/// @param   value Field value.
/// @remarks This method can only be used to set values of simple
///          fields. For setting values of structured fields,
///          this method may be called multiply, e.g. specifying
///          "Position.x" to set the x component of a position.
///          For arrays of simple type, use SetArrayValue.
void Publication::SetFieldValue(String8 fullName, AnySimple value)
{
    //FIXME
}

/// Get the value of an array field which is typed by a system type.
/// @param   fullName Fully qualified array field name.
/// @param   values Array of field values.
/// @param   length Length of array for safety checks.
/// @remarks This method can only be used to get values of arrays of
///          simple type. These may be nested in a structure or array.
void Publication::GetArrayValue(
    String8 fullName,
    const AnySimpleArray values,
    const Int32 length)
{
    //FIXME
}    

/// Set the value of an array field which is typed by a system type.
/// @param   fullName Fully qualified array field name.
/// @param   values Array of field values.
/// @param   length Length of array for safety checks.
/// @remarks This method can only be used to set values of arrays of
///          system type. For setting values of structured or array
///          fields, this method may be called multiply, e.g. by
///          specifying a field name "MyField.Position[2]"
///          in order to access an array item of a structure.
void Publication::SetArrayValue(
    String8 fullName, 
    const AnySimpleArray values, 
    const Int32 length)
{
    //FIXME
}    

// ---------------------------------------------------------------------
// Dynamic Invocation method implementation
// ---------------------------------------------------------------------
/// Create request object.
/// Returns a request object for the given operation
/// that describes the parameters and the return value.
/// @param   operationName Name of operation.
/// @return  Request object for operation.
/// @remarks Request object may be undefined if no operation with
///             given name could be found.
IRequest* Publication::CreateRequest(String8 operationName)
{
    //FIXME
}

/// Delete request object.
/// Destroys a request object that has been created
/// with the CreateRequest() method before.
/// @param   request Request object to delete.
/// @remarks The request object must not be used anymore after
///             DeleteRequest has been called for it.
void Publication::DeleteRequest(IRequest* request)
{
    //FIXME
}


} // end namespace Implementation

} // end namespace Smp