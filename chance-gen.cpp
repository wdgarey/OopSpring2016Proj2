/* 
 * Author: Wesley Garey
 * Date: April 27, 2016
 */

#include <memory>

#include "chance-gen.h"

namespace Project2
{
    ChanceGen::ChanceGen(const double& probability, const uint32_t& seed)
    {
        shared_ptr<UniformRndGen> rnd = make_shared<UniformRndGen>(0.0, 1.0, seed);
        
        this->SetProbability(probability);
        this->SetRnd(rnd);
    }
    
    ChanceGen::ChanceGen(const ChanceGen& src)
    {
        this->Copy(src);
    }
    
    double ChanceGen::GetProbability() const
    {
        return this->m_probability;
    }
    
    bool ChanceGen::Next()
    {
        double probability = this->GetProbability();
        shared_ptr<UniformRndGen> rnd = this->GetRnd();
        
        bool occurred = ((1.0 - probability) < rnd->Next());
        
        return occurred;
    }
    
    ChanceGen& ChanceGen::operator =(const ChanceGen& src)
    {
        if (this != & src)
        {
            this->Copy(src);
        }
        
        return *this;
    }
    
    void ChanceGen::SetProbability(const double& probability)
    {
        this->m_probability = probability;
    }
    
    void ChanceGen::Copy(const ChanceGen& src)
    {
        double probability = src.GetProbability();
        shared_ptr<UniformRndGen> theirRnd = src.GetRnd();
        
        shared_ptr<UniformRndGen> myRnd = make_shared<UniformRndGen>(*theirRnd);
        
        this->SetProbability(probability);
        this->SetRnd(myRnd);
    }
    
    shared_ptr<UniformRndGen> ChanceGen::GetRnd() const
    {
        return this->m_rnd;
    }
    
    void ChanceGen::SetRnd(const shared_ptr<UniformRndGen>& rnd)
    {
        this->m_rnd = rnd;
    }
}