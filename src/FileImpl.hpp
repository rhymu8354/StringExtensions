#ifndef SYSTEM_ABSTRACTIONS_FILE_IMPL_HPP
#define SYSTEM_ABSTRACTIONS_FILE_IMPL_HPP

/**
 * @file FileImpl.hpp
 *
 * This module contains the platform-independent part of the
 * implementation of the SystemAbstractions::File class.
 *
 * © 2013-2018 by Richard Walters
 */

#include <memory>
#include <SystemAbstractions/File.hpp>

namespace SystemAbstractions {

    struct File::Impl {
        // Properties

        /**
         * This is the path to the file in the file system.
         */
        std::string path;

        /**
         * This contains any platform-specific private properties
         * of the class.
         */
        std::unique_ptr< Platform > platform;

        // Lifecycle Management

        ~Impl();
        Impl(Impl&&);
        Impl& operator =(Impl&&);

        // Methods

        /**
         * This is the default constructor.
         */
        Impl();
    };

}

#endif /* SYSTEM_ABSTRACTIONS_FILE_IMPL_HPP */
