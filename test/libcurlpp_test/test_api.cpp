#include <curlpp/OptionBase.hpp>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Option.hpp>

using namespace curlpp::options;

int main()
{
    
    curlpp::Easy req;
    req.setOpt<curlpp::OptionBase Url>("http://www.google.com");

}
