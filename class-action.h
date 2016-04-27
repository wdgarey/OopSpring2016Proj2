/* 
 * Author: Wesley Garey
 * Date: April 27, 2016
 */

#ifndef CLASS_ACTION_H
#define CLASS_ACTION_H

#include <memory>

#include "action.h"

using namespace std;

namespace Project2
{
    /**
     * A class used to invoke class actions.
     */
    template <class DataType>
    class ClassAction : public Action
    {
        public:
            /**
             * Creates an instance of the ClassAction class.
             */
            ClassAction();
            /**
             * Creates an instance of the ClassAction class.
             * @param obj The object that the function will be called for.
             * @param func The function that will be called for the object.
             */
            ClassAction(const shared_ptr<DataType>& obj, void (DataType::* const& func)());
            /**
             * Gets a pointer to the function that will be called for the object.
             * @returns A pointer to the function.
             */
            virtual void (DataType::*GetFunc() const)();
            /**
             * Get the object that the function will be called for.
             * @return The object.
             */
            virtual shared_ptr<DataType> GetObj() const;
            /**
             * Sets the function that will be called for the object.
             * @param func The function.
             */
            virtual void SetFunc(void (DataType::* const& func)());
            /**
             * Sets the object that the function will be called for.
             * @param obj The object.
             */
            virtual void SetObj(const shared_ptr<DataType>& obj);
            /**
             * Calls the function with the object.
             */
            virtual void Invoke();
        private:
            void (DataType::*m_func)(); /// A pointer to the function to call.
            shared_ptr<DataType> m_obj; /// The object to call the function for.
    };
    
    template <class DataType>
    ClassAction<DataType>::ClassAction()
        : m_func(0),
          m_obj(0)
    { }
    
    template <class DataType>
    ClassAction<DataType>::ClassAction(const shared_ptr<DataType>& obj, void(DataType::* const& func)())
    {
        this->SetFunc(func);
        this->SetObj(obj);
    }
    
    template <class DataType>
    void (DataType::*ClassAction<DataType>::GetFunc() const)() 
    {
        return this->m_func;
    }
    
    template <class DataType>
    shared_ptr<DataType> ClassAction<DataType>::GetObj() const
    {
        return this->m_obj;
    }
    
    template <class DataType>
    void ClassAction<DataType>::Invoke()
    {
        ((*m_obj).*m_func)();
    }
    
    template <class DataType>
    void ClassAction<DataType>::SetFunc(void(DataType::* const& func)())
    {
        this->m_func = func;
    }
    
    template <class DataType>
    void ClassAction<DataType>::SetObj(const shared_ptr<DataType>& obj)
    {
        this->m_obj = obj;
    }
}

#endif