#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "ledger/chain/main_chain_controller_protocol.hpp"
#include "ledger/chain/main_chain_service.hpp"
#include "network/p2pservice/p2p_peer_details.hpp"
#include "network/service/client.hpp"

#include <unordered_map>
namespace fetch {
namespace chain {

class MainChainRemoteControl
{
public:
  using service_type         = service::ServiceClient;
  using shared_service_type  = std::shared_ptr<service_type>;
  using mainchain_index_type = uint32_t;

  enum
  {
    CONTROLLER_PROTOCOL_ID = MainChainService::CONTROLLER,
    IDENTITY_PROTOCOL_ID   = MainChainService::IDENTITY
  };

  MainChainRemoteControl() {}
  MainChainRemoteControl(MainChainRemoteControl const &other) = default;
  MainChainRemoteControl(MainChainRemoteControl &&other)      = default;
  MainChainRemoteControl &operator=(MainChainRemoteControl const &other) = default;
  MainChainRemoteControl &operator=(MainChainRemoteControl &&other) = default;

  ~MainChainRemoteControl() = default;

  void SetClient(shared_service_type const &client) { client_ = client; }

  void Connect(byte_array::ByteArray const &host, uint16_t const &port)
  {
    if (!client_)
    {
      TODO_FAIL("Not connected or bad pointer");
    }

    auto p =
        client_->Call(CONTROLLER_PROTOCOL_ID, MainChainControllerProtocol::CONNECT, host, port);
    p.Wait();
  }

  void TryConnect(p2p::EntryPoint const &ep)
  {
    if (!client_)
    {
      TODO_FAIL("Not connected or bad pointer");
    }

    auto p = client_->Call(CONTROLLER_PROTOCOL_ID, MainChainControllerProtocol::TRY_CONNECT, ep);
    p.Wait();
  }

  void Shutdown()
  {
    if (!client_)
    {
      TODO_FAIL("Not connected or bad pointer");
    }

    auto p = client_->Call(CONTROLLER_PROTOCOL_ID, MainChainControllerProtocol::SHUTDOWN);
    p.Wait();
  }

  int IncomingPeers(mainchain_index_type const &mainchain)
  {

    if (!client_)
    {
      TODO_FAIL("Not connected or bad pointer");
    }

    auto p = client_->Call(CONTROLLER_PROTOCOL_ID, MainChainControllerProtocol::INCOMING_PEERS);
    return p.As<int>();

    return 0;
  }

  int OutgoingPeers(mainchain_index_type const &mainchain)
  {

    if (!client_)
    {
      TODO_FAIL("Not connected or bad pointer");
    }

    auto p = client_->Call(CONTROLLER_PROTOCOL_ID, MainChainControllerProtocol::OUTGOING_PEERS);
    return p.As<int>();

    return 0;
  }

  bool IsAlive(mainchain_index_type const &mainchain) { return bool(client_); }

private:
  shared_service_type client_;
};

}  // namespace chain
}  // namespace fetch
