/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <memory>
#include <random>

#include "exp-rnd-gen.h"
#include "rnd-gen.h"

namespace Project2
{
    ExpRndGen::ExpRndGen(const double& bound, const double& lambda, const uint32_t& seed)
        : RndGen(seed),
          m_bound(0),
          m_dist(0)
    {
        shared_ptr<exponential_distribution<> > dist = make_shared<exponential_distribution<> >(lambda);
        
        this->SetBound(bound);
        this->SetDist(dist);
    }
    
    ExpRndGen::ExpRndGen(const ExpRndGen& src)
        : RndGen(src)
    {
        this->Copy(src);
    }
    
    double ExpRndGen::GetBound() const
    {
        return this->m_bound;
    }
    
    shared_ptr<exponential_distribution<> > ExpRndGen::GetDist() const
    {
        return this->m_dist;
    }
    
    double ExpRndGen::Next()
    {
        double bound = this->GetBound();
        shared_ptr<exponential_distribution<> > dist = this->GetDist();
        shared_ptr<default_random_engine> engine = this->GetEngine();
        
        double rndNum = dist->operator()(*engine);
        
        double next = bound * rndNum;
        
        return next;
    }
    
    ExpRndGen& ExpRndGen::operator =(const ExpRndGen& src)
    {
        RndGen::operator =(src);
        
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void ExpRndGen::SetBound(const double& bound)
    {
        this->m_bound = bound;
    }
    
    void ExpRndGen::SetDist(const shared_ptr<exponential_distribution<> > dist)
    {
        this->m_dist = dist;
    }
    
    void ExpRndGen::Copy(const ExpRndGen& src)
    {
        double bound = src.GetBound();
        shared_ptr<exponential_distribution<> > theirDist = src.GetDist();
        
        shared_ptr<exponential_distribution<> > myDist = make_shared<exponential_distribution<> >(*theirDist);
        
        this->SetBound(bound);
        this->SetDist(myDist);
    }
}