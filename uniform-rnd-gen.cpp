/* 
 * Author: Wesley Garey
 * Date: April 27, 2016
 */

#include <memory>

#include "uniform-rnd-gen.h"

namespace Project2
{
    UniformRndGen::UniformRndGen(const double& a, const double& b,const uint32_t& seed)
        : RndGen(seed)
    {
        shared_ptr<uniform_real_distribution<> > dist = make_shared<uniform_real_distribution<> > (a, b);
        
        this->SetDist(dist);
    }
    
    UniformRndGen::UniformRndGen(const UniformRndGen& src)
        : RndGen(src)
    {
        this->Copy(src);
    }
    
    shared_ptr<uniform_real_distribution<> > UniformRndGen::GetDist() const
    {
        return this->m_dist;
    }
    
    double UniformRndGen::Next()
    {
        shared_ptr<uniform_real_distribution<> > dist = this->GetDist();
        shared_ptr<default_random_engine> engine = this->GetEngine();
        
        double next = dist->operator()(*engine);
        
        return next;
    }
    
    UniformRndGen& UniformRndGen::operator =(const UniformRndGen& src)
    {
        RndGen::operator =(src);
        
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void UniformRndGen::SetDist(const shared_ptr<uniform_real_distribution<> >& dist)
    {
        this->m_dist = dist;
    }
    
    void UniformRndGen::Copy(const UniformRndGen& src)
    {
        shared_ptr<uniform_real_distribution<> > theirDist = src.GetDist();
        shared_ptr<uniform_real_distribution<> > myDist = make_shared<uniform_real_distribution<> >(*theirDist);
        
        this->SetDist(myDist);
    }
}