#ifndef _SINGLETON_H
#define _SINGLETON_H

template <typename T, typename CONTEXT>
class Singleton
{
public:
    // Very fast inlined operator accessors
    T* operator->() {return mpInstance;}
    const T* operator->() const {return mpInstance;}
    T& operator*() {return *mpInstance;}
    const T& operator*() const {return *mpInstance;}

    // TODO: delete this method - it was
    //       just used for benchmarking in
    //       the post.
    static T *getInstance()
    {
        static bool static_init = []()->bool {
            mpInstance = new T;
            return true;
        }();
        return mpInstance;
    }

protected:
    Singleton()
    {
        static bool static_init = []()->bool {
            mpInstance = new T;
            return true;
        }();
    }

    Singleton(int)
    {
        static bool static_init = []()->bool {
            mpInstance = CONTEXT::init();
            return true;
        }();
    }

private:
    static T *mpInstance;
};

template <typename T, typename CONTEXT>
T *Singleton<T, CONTEXT>::mpInstance;

#endif // _SINGLETON_H