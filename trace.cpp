/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>

#include "trace.h"

using namespace std;

namespace Project2
{
    void Trace::CloseInst()
    {
        if (Trace::IsInstOpen())
        {
            Trace::s_instance.Close();
        }
    }
    
    bool Trace::IsInstOpen()
    {
        bool isOpen = Trace::s_instance.IsOpen();
        
        return isOpen;
    }
    
    void Trace::OpenInst(const string& path)
    {
        if (Trace::IsInstOpen())
        {
            Trace::s_instance.Close();
        }
        
        Trace::s_instance.Open(path);
    }
    
    void Trace::WriteLineToInst(const string& text)
    {
        if (Trace::IsInstOpen())
        {
            Trace::s_instance.WriteLine(text);
        }
    }
    
    Trace Trace::s_instance = Trace();
    
    Trace::Trace()
        : m_stream (0)
    { }
    
    Trace::Trace(const string& path)
        : m_stream (0)
    {
        this->Open(path);
    }
    
    Trace::~Trace()
    {
        this->Close();
    }
    
    void Trace::Close()
    {
        if (this->IsOpen())
        {
            shared_ptr<ofstream> stream = this->GetStream();
            
            stream->flush();
            stream->close();
            
            stream.reset();
            
            this->SetStream(0);
        }
    }
    
    bool Trace::IsOpen() const
    {
        shared_ptr<ofstream> stream = this->GetStream();
        
        bool isOpen = (stream != 0) && stream->is_open();
        
        return isOpen;
    }
    
    void Trace::Open(const string& path)
    {
        if (this->IsOpen())
        {
            this->Close();
        }
        
        shared_ptr<ofstream> stream = make_shared<ofstream>();
        
        stream->open(path);
        
        this->SetStream(stream);
    }
    
    void Trace::WriteLine(const string& text)
    {
        if (this->IsOpen())
        {
            shared_ptr<ofstream> stream = this->GetStream();
            
            (*stream) << text << "\n";
        }
    }
    
    shared_ptr<ofstream> Trace::GetStream() const
    {
        return this->m_stream;
    }
    
    void Trace::SetStream(const shared_ptr<ofstream> stream)
    {
        this->m_stream = stream;
    }
    
    Trace::Trace(const Trace& src)
    {
        throw runtime_error("Cannot create a copy of a Trace object");
    }
    
    Trace& Trace::operator =(const Trace& src)
    {
        throw runtime_error("Cannot create a copy of a Trace object");
    }
}