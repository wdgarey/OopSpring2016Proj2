/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <vector>

#include "call.h"
#include "call-queue.h"
#include "call-taker.h"
#include "system-stats.h"

namespace Project2
{
    /**
     * Forward declaration of the server class.
     */
    class Server;
    
    /**
     * A class used to represent a tech support system.
     */
    class System : public CallTaker
    {
    public:
        /**
         * Creates an instance of the system class.
         */
        System();
        /**
         * The copy constructor of the system class.
         * @param src The instance to copy.
         */
        System(const System& src);
        /**
         * Adds a server to process calls.
         * @param server The server to add.
         */
        virtual void AddServer(const shared_ptr<Server> server);
        /**
         * Gets the system statistics.
         * @return The statistics.
         */
        virtual SystemStats GetStats() const;
        /**
         * The assignment operator of the System class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual System& operator =(const System& src);
        /**
         * Takes a call.
         * @param call The call to process.
         */
        virtual void TakeCall(Call& call) override;
        /**
         * Receives a notification that a call has been processed.
         * @param call The call that has been completely processed.
         */
        virtual void ReceiveCallProcessedNotification(Call& call);
        /**
         * Tries to get a call from the queue for processing.
         * @param call The call, if available, to process.
         * @return True, if a call is available to process.
         */
        virtual bool TryGiveCallForProcessing(Call& call);
    protected:
        /**
         * Deep copies a system.
         * @param src The instance to copy. 
         */
        virtual void Copy(const System& src);
        /**
         * Gets the collection of calls that need to be processed.
         * @return The collection of calls.
         */
        virtual shared_ptr<CallQueue> GetCalls() const;
        /**
         * Gets the collection of servers that process calls.
         * @return The collection of servers.
         */
        virtual shared_ptr<vector<shared_ptr<Server>>> GetServers() const;
        /**
         * Notifies all servers that a call is ready to be processed.
         */
        virtual void SendCallReadyNotification();
        /**
         * Sets the collection of calls that need to be processed.
         * @param calls The collection of calls.
         */
        virtual void SetCalls(const shared_ptr<CallQueue> calls);
        /**
         * Sets the collection of servers that process calls.
         * @param servers The collection of servers.
         */
        virtual void SetServers(const shared_ptr<vector<shared_ptr<Server>>> servers);
        /**
         * Sets the system statistics.
         * @param stats The statistics.
         */
        virtual void SetStats(const SystemStats& stats);
    private:
        shared_ptr<CallQueue> m_calls; /// The collection of calls that need to be processed.
        shared_ptr<vector<shared_ptr<Server>>> m_servers; /// The collection of servers to process the calls.
        SystemStats m_stats; /// The system statistics.
    };
}

#endif