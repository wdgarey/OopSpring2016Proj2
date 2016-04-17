/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#include <memory>
#include <random>

#include "norm-rnd-gen.h"
#include "rnd-gen.h"

using namespace std;

namespace Project2
{
    NormRndGen::NormRndGen(const double& avg, const double& stdDev)
        : m_dist(0)
    {
        shared_ptr<normal_distribution<> > dist = make_shared<normal_distribution<> >(avg, stdDev);
        
        this->SetDist(dist);
    }
    
    NormRndGen::NormRndGen(const NormRndGen& src)
        : RndGen(src)
    {
        this->Copy(src);
    }
    
    shared_ptr<normal_distribution<> > NormRndGen::GetDist() const
    {
        return this->m_dist;
    }
    
    double NormRndGen::Next()
    {
        shared_ptr<normal_distribution<> > dist = this->GetDist();
        shared_ptr<default_random_engine> engine = this->GetEngine();
        
        double next = dist->operator()(*engine);
        
        return next;
    }
    
    NormRndGen& NormRndGen::operator =(const NormRndGen& src)
    {
        RndGen::operator =(src);
        
        if (this != &src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void NormRndGen::SetDist(const shared_ptr<normal_distribution<> > dist)
    {
        this->m_dist = dist;
    }
    
    void NormRndGen::Copy(const NormRndGen& src)
    {
        shared_ptr<normal_distribution<> > theirDist = src.GetDist();
        
        shared_ptr<normal_distribution<> > myDist = make_shared<normal_distribution<> >(*theirDist);
        
        this->SetDist(myDist);
    }
}