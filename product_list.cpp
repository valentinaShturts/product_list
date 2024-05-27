#include <filesystem>
#include <iostream>
using namespace std;

struct Product
{
    char* name;
    float value = 0;
    int quantity = 0;
    bool availability = false;
};

Product create()
{
    Product product;
    char* name = new char[20]; //створюю рядок
    cout << "Enter item name : ";
    cin >> name; //заповнюю його
    int size = strlen(name); //записую розмір рядка
    product.name = new char[size + 1]; //створюю новий рядок з цим розміром
    strcpy_s(product.name, size + 1, name);

    cout << "Enter value of item: ";
    cin >> product.value;

    cout << "Enter quantity of item: ";
    cin >> product.quantity;

    cout << "Enter this item is avaible (1- true, 0 - false): ";
    cin >> product.availability;
   
    delete[] name;
    return product;
}

int main()
{
    string file_name = "myfiles";
    if (!filesystem::exists(file_name)) //проверка существует ли папка
    {
        filesystem::create_directory(file_name);//создание папки

    }
    if (filesystem :: exists(file_name))
    {
        //створення файлу
        FILE* file;
        const char* PATH_TO_FILE = ".\\myfiles\\products.bin";
       
        if (fopen_s(&file, PATH_TO_FILE, "wb+") == 0)
        {
            int size = 3;
            Product* product_list = new Product[size];
            for (int i = 0; i < size; i++)
            {
                product_list[i] = create(); //створюю масив продуктів на заповнюю його
            }
            fwrite(product_list, sizeof(Product), size, file);//записую цей масив у файл
            fseek(file, 0, SEEK_SET);
            

            Product* new_product_list = new Product[size];//створюю новий масив
            fread(new_product_list, sizeof(Product), size, file);//зчитую туди із файлу
            cout << endl << endl;
            for (int i = 0; i < size; i++)//друкую
            {
                cout << "Item: " << new_product_list[i].name << endl << "Value: " << new_product_list[i].value << endl << "Quantity: " << new_product_list[i].quantity << endl << "Availability: " << new_product_list[i].availability << endl;
                cout << endl << endl;
            }
            fclose(file);
            delete[] product_list;
            delete[] new_product_list;
        }


    }
}
