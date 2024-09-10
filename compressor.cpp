#pragma once
#include <iostream>
#include <zlib.h>

class Compressor {
public:
    static std::string compressData(const std::string& data) {
        uLong sourceLen = data.size();
        uLong destLen = compressBound(sourceLen);
        std::string compressedData(destLen, '\0');

        if (compress(reinterpret_cast<Bytef*>(&compressedData[0]), &destLen,
                     reinterpret_cast<const Bytef*>(data.data()), sourceLen) != Z_OK) {
            std::cerr << "Error compressing data" << std::endl;
            return "";
        }

        compressedData.resize(destLen);
        return compressedData;
    }
};