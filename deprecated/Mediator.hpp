/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

/// \file Mediator.hpp
/// \author Arthur L.
/// \brief Mediator declaration

#pragma once

#include <thread>

#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "ConfReader.hpp"
#include "Hub.hpp"
#include "Rfc.hpp"

/// \namespace Server
/// \brief Used for the all server classes
namespace Server {

    /// \def path for the file containing all event declaration for the game
    constexpr auto const CONF_FILE_PATH = "ressources/r-type-event.conf";
    constexpr auto const SCENE_CONF_FILE_PATH = "ressources/rtype.conf";

    /// \class Mediator
    /// \brief Encapsulate interaction between all elements of rType game
    class Mediator {

        public:
            /// \brief constructor
            /// Initialize Mediator class
            Mediator();
            /// \brief destructor
            /// Destroy Mediator class
            ~Mediator();

            /// \brief return number of hub
            int hubNumber();
            /// \brief method for starting the Mediator
            void start();
            /// \param socket pointer to the received socket
            /// \brief treat all Tcp message received
            void processTcpMessage(Server::TcpConnection *socket);

        private:
            /*! Boost contexte */
            boost::asio::io_context _ioContext;
            /*! Mediator mutex */
            std::mutex _mut;
            /*! reader */
            Common::ConfReader _reader;
            /*! Object handling tcp dialogue */
            Server::TcpNetwork _tcp;
            /*! Thread list of all hub */
            std::vector<std::thread> _threads;
            /*! List of hub */
            std::vector<std::unique_ptr<Server::Hub>> _hubs;
            /*! state of the server */
            bool _isRunning;
            /*! Thread for running boost */
            std::thread _boostThread;
            /*! Map of all actions when you received a tcp message from client */
            std::unordered_map<int, void (Mediator::*)(Server::TcpConnection *socket, Network::headerTcp *packet)> _actions;

            /*! Map of all events need in the game */
            std::unordered_map<int, std::string> _eventTemplate;

            /*! list of shell commands */
            std::unordered_map<std::string, std::function<void(const std::vector<std::string> &)>> _commands;

            /// \param command : the command to parse
            /// \brief get all commands separeted without non-command characters.
            /// \return a vector of command strings.
            std::vector<std::string> parseCommand(const std::string &command);

            // POSSIBLE COMMANDS
            void exit(const std::vector<std::string> &command);
            void kick(const std::vector<std::string> &command);
            void help(const std::vector<std::string> &command);
            void hubs(const std::vector<std::string> &command);

            /// \brief read the conf file for the game
            /// The conf file is specified in Server::CONF_FILE_PATH
            void readEventFile();

            /// \param ip ip of the hub creator
            /// \brief method for creating a new hub
            void createHub(std::string ip);

            /// \brief Launch Boost librairire
            void launchBoost();

            /// \param ip ip of the asking client
            /// \return return number of the assigned hub
            /// \brief assign a hub to the current ip. If no hub is available, it create a thread with the new hub inside.
            int assignHub(std::string ip);

            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client ask a hub
            void askHub(Server::TcpConnection *socket, Network::headerTcp *packet);

            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client is ready
            void setPlayerReady(Server::TcpConnection *socket, Network::headerTcp *packet);

            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client is ready
            void setPlayerNotReady(Server::TcpConnection *socket, Network::headerTcp *packet);

            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client ask for sprite list
            void sendSprite(Server::TcpConnection *socket, Network::headerTcp *packet);

            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client ask for event list
            void sendEvent(Server::TcpConnection *socket, Network::headerTcp *packet);

            /// \brief display shell help
            void dispHelp();
    };
}