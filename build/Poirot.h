//
// Created by kjell-olovhogdahl on 7/27/2016.
//

#ifndef CLANG_BCC_POIROT_H
#define CLANG_BCC_POIROT_H

#include <string>

namespace poirot { namespace comp {

        using ObjectFileDescriptor = std::string;

        ObjectFileDescriptor object_file_description();

    }
}


#endif //CLANG_BCC_POIROT_H
