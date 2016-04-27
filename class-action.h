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
    template <class DataType>
    class ClassAction : public Action
    {
        public:
            ClassAction();
            ClassAction(shared_ptr<DataType> obj, void (DataType::*func)());
            virtual void Invoke();
        private:
            void (DataType::*m_func)();
            shared_ptr<DataType> m_obj;
    };
    
    template <class DataType>
    ClassAction<DataType>::ClassAction()
    {
        
    }
    
    template <class DataType>
    ClassAction<DataType>::ClassAction(shared_ptr<DataType> obj, void(DataType::*func)())
    {
        m_obj = obj;
        m_func = func;
    }
    
    template <class DataType>
    void ClassAction<DataType>::Invoke()
    {
        ((*m_obj).*m_func)();
    }
}

#endif