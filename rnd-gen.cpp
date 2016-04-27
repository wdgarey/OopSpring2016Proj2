/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <memory>
#include <random>

#include "rnd-gen.h"

namespace Project2
{
    RndGen::RndGen(const uint32_t& seed)
        : m_engine (0)
    {
        shared_ptr<default_random_engine> engine = make_shared<default_random_engine>(seed);
        
        this->SetEngine(engine);
    }
    
    RndGen::RndGen(const RndGen& src)
    {
        this->Copy(src);
    }
    
    shared_ptr<default_random_engine> RndGen::GetEngine() const
    {
        return this->m_engine;
    }
    
    RndGen& RndGen::operator =(const RndGen& src)
    {
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void RndGen::SetEngine(const shared_ptr<default_random_engine>& engine)
    {
        this->m_engine = engine;
    }
    
    void RndGen::Copy(const RndGen& src)
    {
        shared_ptr<default_random_engine> theirEngine = src.GetEngine();
        
        shared_ptr<default_random_engine> myEngine = make_shared<default_random_engine>(*theirEngine);
        
        this->SetEngine(myEngine);
    }
}