#pragma once

/**
 * @file Base64.hpp
 *
 * This module declares the Base64 functions.
 *
 * © 2018 by Richard Walters
 */

#include <stdint.h>
#include <string>
#include <vector>

namespace Base64 {

    /**
     * This function encodes the given data using the Base64 algorithm.
     *
     * @param[in] data
     *     This is the data to encode using the Base64 algorithm.
     *
     * @return
     *     The Base64 encoding of the given data is returned.
     */
    std::string Encode(const std::vector< uint8_t >& data);

    /**
     * This function encodes the given data using the Base64 algorithm.
     *
     * @param[in] data
     *     This is the data to encode using the Base64 algorithm.
     *
     * @return
     *     The Base64 encoding of the given data is returned.
     */
    std::string Encode(const std::string& data);

    /**
     * This function decodes the given data using the Base64 algorithm.
     *
     * @param[in] data
     *     This is the data to decodes using the Base64 algorithm.
     *
     * @return
     *     The Base64 decoding of the given data is returned.
     */
    std::string Decode(const std::vector< uint8_t >& data);

    /**
     * This function decodes the given data using the Base64 algorithm.
     *
     * @param[in] data
     *     This is the data to decodes using the Base64 algorithm.
     *
     * @return
     *     The Base64 decoding of the given data is returned.
     */
    std::string Decode(const std::string& data);

    /**
     * This function encodes the given data using the Base64Url algorithm.
     *
     * @param[in] data
     *     This is the data to encode using the Base64Url algorithm.
     *
     * @return
     *     The Base64Url encoding of the given data is returned.
     */
    std::string UrlEncode(const std::vector< uint8_t >& data);

    /**
     * This function encodes the given data using the Base64Url algorithm.
     *
     * @param[in] data
     *     This is the data to encode using the Base64Url algorithm.
     *
     * @return
     *     The Base64Url encoding of the given data is returned.
     */
    std::string UrlEncode(const std::string& data);

    /**
     * This function decodes the given data using the Base64Url algorithm.
     *
     * @param[in] data
     *     This is the data to decodes using the Base64Url algorithm.
     *
     * @return
     *     The Base64Url decoding of the given data is returned.
     */
    std::string UrlDecode(const std::vector< uint8_t >& data);

    /**
     * This function decodes the given data using the Base64Url algorithm.
     *
     * @param[in] data
     *     This is the data to decodes using the Base64Url algorithm.
     *
     * @return
     *     The Base64Url decoding of the given data is returned.
     */
    std::string UrlDecode(const std::string& data);

}