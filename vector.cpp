#include<iostream>

template<typename T>
class Vector{
    
    public:
        Vector():size(0),capacity(16),elements(new T[16]()){}
        Vector(const size_t _size):size(_size),capacity(_size),elements(new T[_size]()){}
        Vector(const size_t _size,const T& val):size(_size),capacity(_size),elements(new T[_size]()){
            for(size_t i=0;i<_size;i++){
                elements[i]=val;
            }
        }
        Vector(const Vector& other):size(other.size),capacity(other.capacity),elements(new T[other.capacity]()){
            for(size_t i=0;i<size;i++){
                elements[i]=other.elements[i];
            }
        }
        Vector(Vector&& other):size(other.size),capacity(other.capacity),elements(new T[other.capacity]()){
            for(size_t i=0;i<size;i++){
                elements[i]=other.elements[i];
            }
            other.clear();
        }
        ~Vector(){
            if(elements!=nullptr)
                delete []elements;
            elements=nullptr;
            size=0;
            capacity=0;
        }
        Vector& operator=(const Vector& other){
            if(this!=other){
                delete[]elements;
                capacity=other.capacity;
                size=other.size;
                elements=new T[capacity]();
                for(size_t i=0;i<size;i++){
                    elements[i]=other.elements[i];
                }
            }

            return *this;
        }
        Vector& operator=(Vector&& other){
            if(this!=other){
                delete[]elements;
                capacity=other.capacity;
                size=other.size;
                elements=new T[capacity]();
                for(size_t i=0;i<size;i++){
                    elements[i]=other.elements[i];
                }

                other.clear();
            }

            return *this;
        }
        T& operator[](const size_t index){
            if(index>=size)
                throw std::out_of_range("Index out of bounds!");
            return elements[index];
        } 
        const T& operator[](const size_t index) const{
            if(index>=size)
                throw std::out_of_range("Index out of bounds!");
            return elements[index];
        }
        T at(const size_t index)const{
            if(index>=size)
                throw std::out_of_range("Index out of bounds!");
            return elements[index];
        }
        size_t getSize()const{
            return size;
        }
        size_t getCapacity()const {
            return capacity;
        }
        void clear(){
            capacity=0;
            size=0;
            delete[]elements;
            elements=nullptr;
        }
        void resize(const size_t _size){
            if(_size<capacity){
                if(size>_size){
                    for(size_t i=_size;i<size;i++){
                        elements[i]=T{};
                    }
                }

                size=_size;
                return;
            }

            while(_size>=capacity){
                capacity<<=1;
            }

            T* newArray=new T[capacity]();
            for(size_t i=0;i<size;i++){
                newArray[i]=elements[i];
            }

            if(elements!=nullptr)
                delete[]elements;
            elements=newArray;
            size=_size;
        }
        void push_back(const T& val){
            if(elements==nullptr){
                capacity=16;
                size=0;
                elements=new T[capacity];
            }

            if(size<capacity){
                elements[size++]=val;
                return;
            }

            capacity<<=1;
            T* newArray=new T[capacity]();
            for(size_t i=0;i<size;i++){
                newArray[i]=elements[i];
            }
            newArray[size++]=val;

            delete[]elements;
            elements=newArray;
        }
        bool empty()const{
            return size==0;
        }

    private:
        size_t size=0;
        size_t capacity=0;
        T* elements=nullptr;
};

void print(const Vector<int>&vec){
    size_t size=vec.getSize();
    size_t cap=vec.getCapacity();

    std::cout<<size<<" "<<cap<<'\n';
    for(size_t i=0;i<size;i++){
        std::cout<<vec[i]<<" ";
    }
    std::cout<<'\n';
}

int main(){
    Vector<int>vec;
    vec.resize(0);
    std::cout<<vec.empty()<<'\n';
    print(vec);
    for(size_t i=1;i<=33;i++){
        vec.push_back(i);
        //vec.resize(i);
        //vec[i-1]=i;
        print(vec);
    }
    std::cout<<vec.at(32);
    return 0;
}
