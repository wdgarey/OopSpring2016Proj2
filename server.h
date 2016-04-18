/* 
 * Author: Wesley Garey
 * Date: April 17, 2016
 */

#ifndef SERVER_H
#define SERVER_H

#include <cstdint>
#include <memory>

#include "norm-rnd-gen.h"
#include "system.h"

using namespace std;

namespace Project2
{
    /**
     * A class that represents a tech support representative.
     */
    class Server
    {
        /**
         * A class used to execute scheduled server actions.
         */
        friend class ServerAction;
    public:
        /**
         * Creates an instance of the Server class.
         */
        Server();
        /**
         * Creates an instance of the Server class.
         * @param id The ID of the server.
         * @param owner The owner of the server.
         * @param rnd The random number generator to use to determine service times.
         */
        Server(const uint32_t& id, System* owner, shared_ptr<NormRndGen> rnd);
        /**
         * The copy constructor of the server class.
         * @param src The instance to copy. 
         */
        Server(const Server& src);
        /**
         * Gets the ID of the server.
         * @return The ID.
         */
        virtual uint32_t GetId() const;
        /**
         * Gets the owner of this server.
         * @return The owner.
         */
        virtual System* GetOwner() const;
        /**
         * Gets the random number generator used to determine service times.
         * @return The random number generator.
         */
        virtual shared_ptr<NormRndGen> GetRnd() const;
        /**
         * Indicates whether or not a the server has a random number generator.
         * @return True, if the server has a random number generator.
         */
        virtual bool HasRnd() const;
        /**
         * Indicates whether or not the TRS is busy.
         * @return True, if the server is busy.
         */
        virtual bool IsBusy() const;
        /**
         * The assignment operator of the Server class.
         * @param src The instance being assigned to.
         * @return The instance that was assigned.
         */
        virtual Server& operator =(const Server& src);
        /**
         * Sets the ID of the server.
         * @param id The ID.
         */
        virtual void SetId(const uint32_t& id);
        /**
         * Sets the owner of this server.
         * @param owner The owner.
         */
        virtual void SetOwner(System* owner);
        /**
         * Sets the random number generator used to determine service times.
         * @param rnd The random number generator.
         */
        virtual void SetRnd(const shared_ptr<NormRndGen> rnd);
        /**
         * Notifies the server that a call is available.
         */
        virtual void ReceiveCallReadyNotification();
    protected:
        /**
         * Deep copies the given server.
         * @param src The instance to copy.
         */
        virtual void Copy(const Server& src);
        /**
         * Gets the current call being serviced.
         * @return The current call.
         */
        virtual shared_ptr<Call> GetCurrCall() const;
        /**
         * Tells the system that the call has been processed.
         */
        virtual void SendCallProcessedNotification();
        /**
         * Releases the current call.
         */
        virtual void ReleaseCall();
        /**
         * Requests another call to process from the system.
         * @return True, if another call was taken.
         */
        virtual bool TryRequestNextCall();
        /**
         * Schedules the next time at which a call will be serviced.
         */
        virtual void ScheduleNextService();
        /**
         * Services the next call in the queue.
         */
        virtual void ServiceNextCall();
        /**
         * Sets the current call being serviced.
         * @param The current call.
         */
        virtual void SetCurrCall(const shared_ptr<Call>);
    private:
        shared_ptr<Call> m_currCall; /// The call that is currently being serviced.
        uint32_t m_id; /// The ID of the tech support rep.
        System* m_owner; /// The owner of the server.
        shared_ptr<NormRndGen> m_rnd; /// The random number generator used to determine service times.
    };
}

#endif