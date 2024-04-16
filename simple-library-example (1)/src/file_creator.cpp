#include "file_creator.hpp"
#include <fstream>

namespace seneca::example
{
    file_creator::file_creator(const std::string& file_path)
        : m_file_path(file_path)
    {
        std::cout << "Files will be created in " << m_file_path << std::endl;
    }

    file_creator::~file_creator()
    {
        std::cout << "Destructor" << std::endl;
    }

    void file_creator::create_file(const nlohmann::json& json_object, const std::string& file_name)
    {
        try
        {
            std::ofstream file(m_file_path + "/" + file_name);
            if (file.is_open())
            {
                file << std::setw(4) << json_object << std::endl;
                std::cout << "File " << file_name << " created successfully" << std::endl;
            }
            else
            {
                throw std::runtime_error("Unable to open file for writing");
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error creating file " << file_name << ": " << e.what() << std::endl;
        }
    }

    nlohmann::json file_creator::read_file(const std::string& file_name)
    {
        try
        {
            std::ifstream file(m_file_path + "/" + file_name);
            if (file.is_open())
            {
                nlohmann::json json_object;
                file >> json_object;
                std::cout << "File " << file_name << " read successfully" << std::endl;
                return json_object;
            }
            else
            {
                throw std::runtime_error("Unable to open file for reading");
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error reading file " << file_name << ": " << e.what() << std::endl;
            return nlohmann::json();
        }
    }
}
