#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>


struct Contact 
{
    int id;
    std::string name;
    std::string phone;
    std::string email;
};

class PhoneBook 
{
private:
    std::vector<Contact> contacts;
    int nextId = 1;

public:
    void Add(const std::string& name, const std::string& phone, const std::string& email) 
    {
        contacts.push_back({ nextId++, name, phone, email });
    }

    void Remove(int id) 
    {
        contacts.erase(
            std::remove_if(contacts.begin(), contacts.end(),
                [id](const Contact& c) { return c.id == id; }),
            contacts.end()
        );
    }

    void Update(int id, const std::string& name, const std::string& phone, const std::string& email) 
    {
        for (auto& c : contacts) {
            if (c.id == id) {
                c.name = name;
                c.phone = phone;
                c.email = email;
                return;
            }
        }
    }

    void List() const 
    {
        std::cout << "\n--- CONTACTS ---\n";
        for (const auto& c : contacts) {
            std::cout << "ID: " << c.id
                      << " | Name: " << c.name
                      << " | Phone: " << c.phone
                      << " | Email: " << c.email << "\n";
        }
    }

    void Save(const std::string& filename) 
    {
        std::ofstream file(filename);
        for (const auto& c : contacts) {
            file << c.id << ";" << c.name << ";" << c.phone << ";" << c.email << "\n";
        }
    }

    void Load(const std::string& filename) 
    {
        std::ifstream file(filename);
        contacts.clear();

        std::string line;
        while (std::getline(file, line)) 
        {
            std::stringstream ss(line);
            std::string part;

            Contact c;
            std::getline(ss, part, ';'); c.id = std::stoi(part);
            std::getline(ss, c.name, ';');
            std::getline(ss, c.phone, ';');
            std::getline(ss, c.email, ';');

            contacts.push_back(c);
            nextId = std::max(nextId, c.id + 1);
        }
    }

    void PrintToFile(const std::string& filename) 
    {
        std::ofstream file(filename);
        file << "PHONE BOOK\n\n";

        for (const auto& c : contacts) {
            file << "ID: " << c.id << "\n";
            file << "Name: " << c.name << "\n";
            file << "Phone: " << c.phone << "\n";
            file << "Email: " << c.email << "\n";
            file << "----------------------\n";
        }
    }
};

// UI
void ShowMenu() 
{
    std::cout << "\n=== PHONE BOOK ===\n";
    std::cout << "1. Add contact\n";
    std::cout << "2. Remove contact\n";
    std::cout << "3. Update contact\n";
    std::cout << "4. List contacts\n";
    std::cout << "5. Save\n";
    std::cout << "6. Load\n";
    std::cout << "7. Print to file\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() 
{
    PhoneBook pb;
    int choice;

    while (true) 
    {
        ShowMenu();
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) 
        {
            std::string name, phone, email;
            std::cout << "Name: "; std::cin >> name;
            std::cout << "Phone: "; std::cin >> phone;
            std::cout << "Email: "; std::cin >> email;
            pb.Add(name, phone, email);
        }

        else if (choice == 2) 
        {
            int id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            pb.Remove(id);
        }

        else if (choice == 3) 
        {
            int id;
            std::string name, phone, email;
            std::cout << "Enter ID: "; std::cin >> id;
            std::cout << "New Name: "; std::cin >> name;
            std::cout << "New Phone: "; std::cin >> phone;
            std::cout << "New Email: "; std::cin >> email;
            pb.Update(id, name, phone, email);
        }

        else if (choice == 4) 
        {
            pb.List();
        }

        else if (choice == 5) 
        {
            pb.Save("contacts.txt");
        }

        else if (choice == 6) 
        {
            pb.Load("contacts.txt");
        }

        else if (choice == 7) 
        {
            pb.PrintToFile("print.txt");
        }
    }

    return 0;
}