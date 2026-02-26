#include <iostream>
#include <memory>

class Demo {
private:
    std::string name_;
public:
    Demo() : name_("Default") {
        std::cout << "Конструктор по умолчанию: " << name_ << std::endl;
    }

    Demo(const std::string& name) : name_(name) {
        std::cout << "Конструктор с параметром: " << name_ << std::endl;
    }

    Demo(const Demo& other) : name_(other.name_ + "_copy") {
        std::cout << "Конструктор копирования: " << name_ << std::endl;
    }
    Demo& operator=(const Demo& other) {
        std::cout << "Оператор присваивания копированием: " << name_ << " -> " << other.name_ << std::endl;
        if (this != &other) {
            name_ = other.name_ + "_copy";
        }
        return *this;
    }

     Demo(Demo&& other) noexcept : name_(std::move(other.name_) + "_moved") {
        std::cout << "Конструктор перемещения: " << name_ << std::endl;
        other.name_ = "empty";
    }
    Demo& operator=(Demo&& other) noexcept {
        std::cout << "Оператор присваивания перемещением: " << name_ << " -> " << other.name_ << std::endl;
        if (this != &other) {
            name_ = std::move(other.name_) + "_moved";
            other.name_ = "empty";
        }
        return *this;
    }

    ~Demo() {
        std::cout << "Деструктор: " << name_ << std::endl;
    }


    std::string get() const {
        return name_;
    }
};


void test1() {
    std::cout << "\n=== Тест 1: Операторы * и -> ===" << std::endl;

    std::unique_ptr<Demo> ptr1 = std::make_unique<Demo>("Object1");    
    std::cout << "ptr1->get(): " << ptr1->get() << std::endl;
    std::cout << "(*ptr1).get(): " << (*ptr1).get() << std::endl;
    std::cout << std::endl;
}

void test2() {
    std::cout << "\n=== Тест 1: метод get() ===" << std::endl;
    std::unique_ptr<Demo> ptr = std::make_unique<Demo>("Hello!");
    
    Demo* rawPtr = ptr.get();
    
    std::cout << "ptr->get(): " << ptr->get() << std::endl;
    std::cout << "rawPtr->get(): " << rawPtr->get() << std::endl;
    
    std::cout << "Адрес через ptr: " << ptr.get() << std::endl;
    std::cout << "Адрес через rawPtr: " << rawPtr << std::endl;
    std::cout << std::endl;
}


void test3() {
    std::cout << "\n=== Тест 3: Метод reset() ===" << std::endl;
    
    std::cout << "Создаем ptr с объектом First" << std::endl;
    std::unique_ptr<Demo> ptr = std::make_unique<Demo>("First");
    
    std::cout << "\nВызываем reset() без параметров - удаляем объект:" << std::endl;
    ptr.reset();
    
    std::cout << "\nПроверяем ptr после reset(): " 
              << (ptr ? "не пустой" : "пустой") << std::endl;
    
    std::cout << "\nВызываем reset(new Demo('Second')):" << std::endl;
    ptr.reset(new Demo("Second")); 
    
    std::cout << "\nСнова reset с новым объектом:" << std::endl;
    ptr.reset(new Demo("Third"));
    std::cout << std::endl;
}


void test4() {
    std::cout << "\n=== Тест 4: Метод release() ===" << std::endl;
    
    std::unique_ptr<Demo> ptr = std::make_unique<Demo>("ForRelease");
    std::cout << "ptr управляет объектом: " << ptr->get() << std::endl;
    
    std::cout << "\nВызываем release()..." << std::endl;
    Demo* rawPtr = ptr.release();
    
    std::cout << "ptr после release(): " << (ptr ? "не пустой" : "пустой") << std::endl;
    std::cout << "rawPtr указывает на: " << rawPtr->get() << std::endl;
    
    std::cout << "\nОбъект все еще жив, нужно удалить вручную!" << std::endl;
    delete rawPtr;
    
    std::cout << std::endl;
}


void test5() {
    std::cout << "\n=== Тест 5: Работа с массивами ===" << std::endl;

    std::cout << "Создаем массив из 3 объектов:" << std::endl;
    std::unique_ptr<Demo[]> arr = std::make_unique<Demo[]>(3);

    std::cout << "\nДоступ к элементам массива:" << std::endl;
    for (size_t i = 0; i < 3; ++i) {
        std::cout << "arr[" << i << "].get(): " << arr[i].get() << std::endl;
    }
    
    std::cout << "\nСоздаем массив с именами:" << std::endl;
    auto arr2 = std::unique_ptr<Demo[]>(new Demo[2]{
        Demo("Array0"), 
        Demo("Array1")
    });
    
    std::cout << "\nЭлементы второго массива:" << std::endl;
    for (size_t i = 0; i < 2; ++i) {
        std::cout << "arr2[" << i << "].get(): " << arr2[i].get() << std::endl;
    }
    std::cout << std::endl;
}


void testUniquePtr() {
    std::cout << "============================================\n"; 
    test1();
    test2();
    test3();
    test4();
    test5();
    std::cout << "============================================\n"; 
}


struct BadNode {
    std::shared_ptr<BadNode> next;
    BadNode() { 
        std::cout << "BadNode создан\n"; 
    }
    ~BadNode() { 
        std::cout << "BadNode удален\n"; 
    }
};

struct GoodNode {
    std::weak_ptr<GoodNode> next;
    GoodNode() { 
        std::cout << "GoodNode создан\n"; 
    }
    ~GoodNode() { 
        std::cout << "GoodNode удален\n"; 
    }
};


void testSharedPtr() {
    std::cout << "=== ПРОБЛЕМА: циклические shared_ptr ===\n";
    auto a = std::make_shared<BadNode>();
    auto b = std::make_shared<BadNode>();
    
    a->next = b;  
    b->next = a; 
    
    std::cout << "Выход из области видимости...\n";
}

void testWeakPtr() {
    std::cout << "\n=== РЕШЕНИЕ: weak_ptr разрывает цикл ===\n";
        auto a = std::make_shared<GoodNode>();
        auto b = std::make_shared<GoodNode>();
        
        a->next = b;  
        b->next = a; 
        
        std::cout << "Выход из области видимости...\n";
    }

void testLock() {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ lock() ===\n";
    std::weak_ptr<GoodNode> weak;
    auto shared = std::make_shared<GoodNode>();
    weak = shared;
    if (auto locked = weak.lock()) {
        std::cout << "Объект жив\n";
    }
    if (auto locked = weak.lock()) {
        std::cout << "Никогда не выполнится\n";
    } else {
        std::cout << "Объекта больше нет (weak::lock() == nullptr)\n";
    }
    
    std::cout << "expired? " << (weak.expired() ? "да" : "нет") << "\n";
}


void testSharedAndWeak() {
    std::cout << "============================================\n"; 
    testSharedPtr();
    testWeakPtr();
    testLock();
    std::cout << "============================================\n";
}




int main(void) {
    std::cout << "============================================\n";
    testUniquePtr();
    std::cout << "============================================\n";
    testSharedAndWeak();
    std::cout << "============================================\n";
    return 0;
}