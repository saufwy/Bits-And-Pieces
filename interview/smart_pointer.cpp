// #include <iostream>
#include <memory>

class T {
public:
    T() {
        // std::cout << "constructor" << std::endl;
    }
    ~T() {
        // std::cout << "deconstructor" << std::endl;
    }
};

int main() {
    std::shared_ptr<int> p1(new int);
    std::shared_ptr<int> p2 = p1;
    // std::cout << p2.use_count() << std::endl;
    // std::cout << "p1 == p2  " <<  (p1 == p2 ? 1 : 0) << std::endl;

    std::unique_ptr<T> p3(new T());
    return 0;
}

// std::make_shared  内部实现就是构造了一个shared_ptr

template<typename _Tp, typename _Alloc, typename... _Args>
  inline shared_ptr<_Tp>
  allocate_shared(const _Alloc& __a, _Args&&... __args)
  {
    return shared_ptr<_Tp>(_Sp_make_shared_tag(), __a,
  		     std::forward<_Args>(__args)...);
  }

/**
 *  @brief  Create an object that is owned by a shared_ptr.
 *  @param  __args  Arguments for the @a _Tp object's constructor.
 *  @return A shared_ptr that owns the newly created object.
 *  @throw  std::bad_alloc, or an exception thrown from the
 *          constructor of @a _Tp.
 */
template<typename _Tp, typename... _Args>
  inline shared_ptr<_Tp>
  make_shared(_Args&&... __args)
  {
    typedef typename std::remove_const<_Tp>::type _Tp_nc;
    return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(),
  			       std::forward<_Args>(__args)...);
  }

