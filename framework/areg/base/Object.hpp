#ifndef AREG_BASE_OBJECT_HPP
#define AREG_BASE_OBJECT_HPP
/************************************************************************
 * \file        areg/base/Object.hpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit 
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG Platform Generic Object class
 *
 ************************************************************************/
/************************************************************************
 * Include files.
 ************************************************************************/
#include "areg/base/GEGlobal.h"
#include "areg/base/IEGenericObject.hpp"

//////////////////////////////////////////////////////////////////////////
// Object class declaration
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   This class inherits IEGenericObject interface.
 *          Used to have common object class to be able to save
 *          pointers in typed template classes. As well as it has
 *          overwritten new and delete operators, and other basic 
 *          operators that are used.
 **/
class AREG_API Object  : public IEGenericObject
{
//////////////////////////////////////////////////////////////////////////
// Friend classes
//////////////////////////////////////////////////////////////////////////
    friend class TEObjectFactory<Object>;

//////////////////////////////////////////////////////////////////////////
// Constructors / Destructor
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Default constructor
     **/
    Object( void );

    /**
     * \brief   Store pointer as object data.
     * \param   objData     The pointer to store in object.
     **/
    Object( void* objData );

    /**
     * \brief   Copy data from given source.
     * \param   src     The source to copy data.
     **/
    Object( const Object & src );

    /**
     * \brief   Destructor.
     **/
    virtual ~Object( void );

//////////////////////////////////////////////////////////////////////////
// Attributes / Operations
//////////////////////////////////////////////////////////////////////////
public:
/************************************************************************/
// IEGenericObject interface overrides
/************************************************************************/
    /**
     * \brief   Call to clone object
     * \return  Pointer to cloned object
     **/
    virtual IEGenericObject* clone( void ) const;

    /**
     * \brief   Destroys created (cloned) object
     **/
    virtual void destroy( void );

    /**
     * \brief   Checks if object data is similar.
     *          In this class it checks address of pointer to void object.
     *          The method is used in map and vector objects.
     *          Override this method if it needs to have another logic of comparing 2 objects
     *
     * \param   other   Pointer to an object to compare
     * \return  Returns 'true' if 2 objects are equal
     **/
    virtual bool isEqual( const IEGenericObject * other ) const;

//////////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////////
public:
/************************************************************************/
// Basic operatos ( = , ==, 
/************************************************************************/
    /**
     * \brief   Assignment operator.
     * \param   src     Reference to a source object
     * \return  Reference to the object
     **/
    const Object & operator = ( const Object & src );

    /**
     * \brief   Checks whether 2 objects are equal
     * \param   other   Reference to an object to compare
     * \return  Returns 'true' if 2 objects are equal
     **/
    bool operator == ( const Object& other ) const;

    /**
     * \brief   Checks whether 2 objects are equal
     * \param   other   Reference to an object to compare
     * \return  Returns 'true' if 2 objects are not equal
     **/
    bool operator != ( const Object & other ) const;

    /**
     * \brief   Operator to get integer value of object, mainly used in map
     * \return  Integer value of object.
     **/
    operator unsigned int ( void ) const;

/************************************************************************
 * new operator
 ************************************************************************/
    /**
     * \brief   Overloaded new() operator
     * \param   size    Size of the memory block to allocate
     * \return  pointer to a memory block of size 'size' or NULL if an allocation error occurred
     **/
    void * operator new( size_t size );

    /**
     * \brief   Overloaded array new operator
     * \param   size    Size of the memory block to allocate
     * \return  Pointer to a memory block of size 'size' or NULL if an allocation error occurred
     **/
    void * operator new [ ] ( size_t size );

    /**
     * \brief   Overloaded placement new
     * \param   size    Not used. Size of the memory block to allocate
     * \param   ptr     Pointer to the memory block where the object is located
     * \return  Pointer to the memory block where the object is located, same as 'ptr'
     **/
    void * operator new( size_t /*size*/, void * ptr );

    /**
     * \brief   Overloaded placement new
     * \param   size    Not used. Size of the memory block to allocate
     * \param   ptr     Pointer to the memory block where the object is located
     * \return  Pointer to the memory block where the object is located, same as 'ptr'
     **/
    void * operator new [ ] ( size_t /*size*/, void *ptr );

    /**
     * \brief   Overloaded placement new. Stores block type, file name and line number information
     *          Used in debugging version. In other versions, only allocates memory without
     *          containing other information.
     * \param   size    Size of the memory block to allocate
     * \param   block   Not used. Block type. Always passed 1 as a normal block.
     * \param   file    Ignored in non-debug version. Source code file name, normally __FILE__
     * \param   line    Ignored in non-debug version. Source code line number, normally __LINE__
     * \return  Pointer to a memory block of size 'size' or NULL if an allocation error occurred
     **/
    void * operator new( size_t size, int /*block*/, const char * file, int line );

    /**
     * \brief   Overloaded placement new. Stores block type, file name and line number information
     *          Used in debugging version. In other versions, only allocates memory without
     *          containing other information.
     * \param   size    Size of the memory block to allocate
     * \param   block   Not used. Block type. Always passed 1 as a normal block.
     * \param   file    Ignored in non-debug version. Source code file name, normally __FILE__
     * \param   line    Ignored in non-debug version. Source code line number, normally __LINE__
     * \return  Pointer to a memory block of size 'size' or NULL if an allocation error occurred
     **/
    void * operator new [ ] ( size_t size, int /*block*/, const char * file, int line );

/************************************************************************
 * delete operators
 ************************************************************************/
    /**
     * \brief   Overloaded delete() operator
     * \param   ptr   pointer to the memory block to delete
     **/
    void operator delete( void * ptr );

    /**
     * \brief   Overloaded delete() operator
     * \param   ptr     Pointer to the memory block to delete
     * \param   size    Not used.
     **/
    void operator delete( void * ptr, size_t size );

    /**
     * \brief	Overloaded delete() operator
     * \param	ptr	Pointer to the memory block to delete
     **/
    void operator delete( void * ptr, int, const char *, int );

    /**
     * \brief   Overloaded array delete operator
     * \param   ptr     Pointer to the memory block to delete
     **/
    void operator delete [ ] ( void* ptr );

    /**
     * \brief   Overloaded array delete operator
     * \param   ptr     Pointer to the memory block to delete
     * \param   size    Not used.
     **/
    void operator delete [] (void* ptr, size_t /*size*/);

    /**
     * \brief	Overloaded delete[] operator
     * \param	ptr	Pointer to the memory block to delete
     **/
    void operator delete [ ] ( void * ptr, int, const char *, int );

//////////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////////
private:
    /**
     * \brief   Returns the reference to the object.
     **/
   inline const Object& self( void ) const;
};

//////////////////////////////////////////////////////////////////////////
// Object class inline functions
//////////////////////////////////////////////////////////////////////////
inline const Object& Object::self( void ) const
{   return (*this); }

#endif  // AREG_BASE_OBJECT_HPP