#include "file_creator.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <nlohmann/json.hpp>

namespace
{

class file_creator_test : public ::testing::Test
{
protected:

    file_creator_test()
    {

    };

    void SetUp()
    {

    }

    void TearDown()
    {

    }
};

TEST_F(file_creator_test, when_calling_file_create_expect_throw)
{
    std::cout<<" This is the test!"<<std::endl;
    nlohmann::json js;

    js["one"] = 1;
    js["string"] = "Hey there!";
    std::cout<<js.dump()<<std::endl;
    std::string file_path = "/home/root";
    seneca::example::file_creator fl(file_path);
    std::string file_name = "Hi.txt";
    EXPECT_THROW(fl.create_file(js,file_name), std::error_code);
    
}

}
