/* 
 * Author: Wesley Garey
 * Date: April 16, 2016
 */

#ifndef TRACE_H
#define TRACE_H

#include <fstream>
#include <string>
#include <memory>

using namespace std;

namespace Project2
{
    /**
     * A class that represents a trace.
     */
    class Trace
    {
    public:
        /**
         * Closes the static instance of the trace.
         */
        static void CloseInst();
        /**
         * Indicates whether or not the static instance is open.
         * @return True, if the static instance is open.
         */
        static bool IsInstOpen();
        /**
         * Initializes the static instance of the trace.
         * @param path The path of the file that should be written to.
         */
        static void OpenInst(const string& path);
        /**
         * Writes the given text and adds a new line to the trace.
         * @param text The text to write.
         */
        static void WriteLineToInst(const string& text);
    private:
        /**
         * The static instance of the trace.
         */
        static Trace s_instance;
    public:
        /**
         * Creates an instance of the Trace class.
         */
        Trace();
        /**
         * Creates an instance of the Trace class.
         * @param path The file path of the trace file.
         */
        Trace(const string& path);
        /**
         * The destructor of the Trace class.
         */
        virtual ~Trace();
        /**
         * Closes the file if it is open.
         */
        virtual void Close();
        /**
         * Indicates whether or not the file is open.
         * @param text
         */
        virtual bool IsOpen() const;
        /**
         * Opens a file with the given path to write to.
         * @param path The file path.
         */
        virtual void Open(const string& path);
        /**
         * Writes the given text to the trace file and adds a new line.
         * @param text The text to write.
         */
        virtual void WriteLine(const string& text);
    protected:
        /**
         * Gets the output file stream.
         * @return The output file stream.
         */
        virtual shared_ptr<ofstream> GetStream() const;
        /**
         * Sets the output file stream.
         * @param stream The output file stream.
         */
        virtual void SetStream (const shared_ptr<ofstream> stream);
    private:
        shared_ptr<ofstream> m_stream; /// The stream to write to.
        /**
         * The copy constructor of the Trace class.
         * @param src The instance to copy.
         */
        Trace(const Trace& src); 
        /**
         * The assignment operator of the Trace class.
         * @param src The instance to assign to.
         * @return The instance that was assigned.
         */
        Trace& operator =(const Trace& src); 
    };
}

#endif