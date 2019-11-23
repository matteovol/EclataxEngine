/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ConfReader
*/

#include "ConfReader.hpp"
#include "Logger.hpp"

Client::ConfReader::ConfReader()
{
    try {
        readFile("ressources/.conf");
    } catch (Debug::MissingFileException &e) {
        throw e;
    }
}

Client::ConfReader::ConfReader(const std::string &file)
{
    try {
        readFile(file);
    } catch (Debug::MissingFileException &e) {
        throw e;
    }
}

Client::ConfReader::~ConfReader() {}

std::optional<std::string> Client::ConfReader::conf(const std::string &key) const
{
    if (_conf.count(key) > 0)
        return _conf.at(key);
    return {};
}

void Client::ConfReader::readFile(const std::string &file)
{
    std::ifstream ifs(file);

    if (!ifs)
        throw Debug::MissingFileException("configuration file not found",
            "Client::ConfReader::readFile");

    std::string line;
    while (std::getline(ifs, line)) {
        auto pos = line.find(":");

        if (pos == std::string::npos) {
            Debug::Logger *log = Debug::Logger::getInstance(Debug::STANDARD, Debug::Flags::fatal_off);
            log->generateDebugMessage(Debug::WARNING, "invalid line in configuration file",
                "Client::ConfReader::readFile");
            continue;
        }

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.size());

        _conf.insert({key, value});
    }
}