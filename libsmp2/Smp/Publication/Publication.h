#ifndef SMP_MANAGEMENT_PUBLICATION_H
#define SMP_MANAGEMENT_PUBLICATION_H

#include <map>

#include <Smp/IPublication.h>

namespace Smp
{
// TODO: fix namespace
namespace Implementation
{    
    
/// Publication receiver.
/// Provide functionality to allow publishing fields and operations.
/// @remarks This interface is platform specific.
class Publication: public IPublication
{
public:
    // FIXME. Implement according to standard
    struct PublishedField {
        String8 name;
        String8 description;
        void* address;
        Bool view;
        Bool state;
        Bool input;
        Bool output;
    };

    Publication();
    /// Virtual destructor.
    /// This is needed to be able to destroy instances
    /// using the actual derived destructor.
    virtual ~Publication();

    // ---------------------------------------------------------------------
    // Type registration mechanism
    // ---------------------------------------------------------------------

    /// Give access to the global type registry.
    /// @return Reference to global type registry.
    /// @remarks The type registry is typically a singleton, and must not
    ///          be null, to allow use of existing types, and registration 
    ///          of new types.
    Smp::Publication::ITypeRegistry* GetTypeRegistry() const;

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
    void PublishField(
        String8 name,
        String8 description,
        Char8* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish a Bool field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Bool* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish Int8 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Int8* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish Int16 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Int16* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish Int32 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Int32* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish Int64 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Int64* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish UInt8 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        UInt8* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish UInt16 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        UInt16* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish UInt32 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        UInt32* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish UInt64 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        UInt64* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish Float32 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Float32* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish Float64 field.
    /// @param name Field name.
    /// @param description Field description.
    /// @param address Field memory address.
    /// @param view Show field in model tree.
    /// @param state Include field in store/restore of simulation state.
    /// @param input True if field is an input field, false otherwise.
    /// @param output True if field is an output field, false otherwise.
    void PublishField(
        String8 name,
        String8 description,
        Float64* address,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

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
    void PublishField(
        String8 name,
        String8 description,
        void* address,
        const Smp::Uuid typeUuid,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

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
    void PublishArray(
        String8 name,
        String8 description,
        const Int64 count,
        void* address,
        const SimpleTypeKind type,
        const Bool view = true,
        const Bool state = true,
        const Bool input = false,
        const Bool output = false);

    /// Publish array of any type.
    /// @param name Array name.
    /// @param description Array description.
    IPublication* PublishArray(
        String8 name,
        String8 description);

    /// Publish structure.
    /// @param name Structure name.
    /// @param description Structure description.
    IPublication* PublishStructure(
        String8 name,
        String8 description);

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
    Smp::Publication::IPublishOperation* PublishOperation(
        String8 name,
        String8 description,
        const Smp::Uuid returnTypeUuid);

    // ---------------------------------------------------------------------
    // Property publication mechanism
    // ---------------------------------------------------------------------

    /// Publish a property.
    /// @param   name Property name.
    /// @param   description Property description.
    /// @param   typeUuid Uuid of type of Property.
    /// @param   accessKind Access kind of Property
    void PublishProperty(
        String8 name,
        String8 description,
        const Smp::Uuid typeUuid,
        const AccessKind accessKind);

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
    AnySimple GetFieldValue(String8 fullName);

    /// Set the value of a field which is typed by a system type.
    /// @param   fullName Fully qualified field name.
    /// @param   value Field value.
    /// @remarks This method can only be used to set values of simple
    ///          fields. For setting values of structured fields,
    ///          this method may be called multiply, e.g. specifying
    ///          "Position.x" to set the x component of a position.
    ///          For arrays of simple type, use SetArrayValue.
    void SetFieldValue(String8 fullName, AnySimple value);

    /// Get the value of an array field which is typed by a system type.
    /// @param   fullName Fully qualified array field name.
    /// @param   values Array of field values.
    /// @param   length Length of array for safety checks.
    /// @remarks This method can only be used to get values of arrays of
    ///          simple type. These may be nested in a structure or array.
    void GetArrayValue(
        String8 fullName,
        const AnySimpleArray values,
        const Int32 length);

    /// Set the value of an array field which is typed by a system type.
    /// @param   fullName Fully qualified array field name.
    /// @param   values Array of field values.
    /// @param   length Length of array for safety checks.
    /// @remarks This method can only be used to set values of arrays of
    ///          system type. For setting values of structured or array
    ///          fields, this method may be called multiply, e.g. by
    ///          specifying a field name "MyField.Position[2]"
    ///          in order to access an array item of a structure.
    void SetArrayValue(
        String8 fullName, 
        const AnySimpleArray values, 
        const Int32 length);

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
    IRequest* CreateRequest(String8 operationName);

    /// Delete request object.
    /// Destroys a request object that has been created
    /// with the CreateRequest() method before.
    /// @param   request Request object to delete.
    /// @remarks The request object must not be used anymore after
    ///             DeleteRequest has been called for it.
    void DeleteRequest(IRequest* request);
private:
    std::map<std::string,PublishedField> m_publishedFields;
};

} // end namespace Implementation
} // end namespace Smp

#endif // SMP_MANAGEMENT_PUBLICATION_H