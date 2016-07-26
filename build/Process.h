//
// Created by kjell-olovhogdahl on 7/26/2016.
//

#ifndef app_PROCESS_H
#define app_PROCESS_H

#include <vector>
#include <future>

namespace app { namespace process {
        using Path = std::string;
        using Parameter = std::string;
        using Parameters = std::vector<Parameter>;

        std::future<int> execute(const Path& cmd,const Parameters& parameters);
}}

#endif //app_PROCESS_H
