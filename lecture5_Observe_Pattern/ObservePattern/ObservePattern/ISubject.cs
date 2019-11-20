using System;
namespace ObservePattern
{
    public interface ISubject
    {
        void registerSubscriber(IObserve observe);
        void removeSubscriber(IObserve observe);
        void notifySubscriber();
        
    }
}
