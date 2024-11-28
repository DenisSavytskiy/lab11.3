#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include <vector>
#include "../AP_Lab№11.3/AP_Lab№11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1 {
    TEST_CLASS(ProductManagerTest) {
public:
    struct Product {
        std::string name;
        std::string storeName; // Corrected member name
        double price;
        int quantity;
        std::string unitOfMeasurement; // Corrected member name
    };
    TEST_METHOD(TestAddProduct) {
        // Створення тестового файлу
        string testFilename = "test_products.txt";
        ofstream testFile(testFilename);
        testFile.close();

        // Підготовка тестових даних
        ofstream prepFile(testFilename);
        prepFile << "Молоко\nАТБ\n25.50\n10\nл\n";
        prepFile.close();

        // Читаємо товари
        vector<Product> products = readProductsFromFile(testFilename);

        // Перевіряємо правильність зчитування
        Assert::AreEqual(1u, products.size());
        Assert::AreEqual(string("Молоко"), products[0].name);
        Assert::AreEqual(string("АТБ"), products[0].storeName); // Corrected member name
        Assert::AreEqual(25.50, products[0].price, 0.01);
        Assert::AreEqual(10, products[0].quantity);
        Assert::AreEqual(string("л"), products[0].unitOfMeasurement); // Corrected member name
    }

    TEST_METHOD(TestFindProductByName) {
        // Створення тестового файлу
        std::string testFilename = "test_products.txt";
        std::ofstream testFile(testFilename);
        testFile << "Хліб\nСільпо\n15.00\n20\nшт\n";
        testFile.close();

        // Читаємо товари
        std::vector<Product> products = readProductsFromFile(testFilename);

        // Перевіряємо пошук товару за назвою
        bool found = false;
        for (const auto& p : products) {
            if (p.name == "Хліб") {
                found = true;
                Assert::AreEqual(std::string("Сільпо"), p.storeName, L"Назва магазину не збігається"); // Corrected member name
                Assert::AreEqual(15.00, p.price, 0.01, L"Ціна товару не збігається");
                break;
            }
        }
        Assert::IsTrue(found, L"Товар не знайдено");
    }

    TEST_METHOD(TestFindProductsByStore) {
        // Створення тестового файлу
        std::string testFilename = "test_products.txt";
        std::ofstream testFile(testFilename);
        testFile << "Хліб\nАТБ\n15.00\n20\nшт\n";
        testFile << "Молоко\nАТБ\n25.50\n10\nл\n";
        testFile.close();

        // Читаємо товари
        std::vector<Product> products = readProductsFromFile(testFilename);

        // Перевіряємо пошук товарів за магазином
        int atbCount = 0;
        for (const auto& p : products) {
            if (p.storeName == "АТБ") { // Corrected member name
                atbCount++;
            }
        }
        Assert::AreEqual(2, atbCount, L"Кількість товарів у магазині АТБ не збігається");
    }
    };
}