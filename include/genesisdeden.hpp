#pragma once

/*
 * @file
 * @author  (C) 2020 by eoscostarica [ https://eoscostarica.io ]
 * @version 1.1.0
 *
 * @section DESCRIPTION
 *
 *    Smart contract genesisdeden  
 *
 *    WebSite:        https://eosrate.io/
 *    GitHub:         https://github.com/eoscostarica/eos-rate
 *
 */

#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>
#include <eosio/permission.hpp> 
#include <algorithm>
#include <set>
#include "utils.hpp"


using namespace std;
using namespace eosio;
using eosio::public_key;


namespace eoscostarica {
    using member_status_type = uint8_t;
    enum member_status : member_status_type {
        pending_membership = 0,
        active_member = 1
    };

    using election_participation_status_type = uint8_t;
    enum election_participation_status : election_participation_status_type {
        not_in_election = 0,
        in_election = 1
    };

    struct member_v0
    {
      eosio::name account;
      std::string name;
      member_status_type status;
      uint64_t nft_template_id;
      // Only reflected in v1
      election_participation_status_type election_participation_status = not_in_election;
      uint8_t election_rank = 0;
      eosio::name representative{uint64_t(-1)};
      std::optional<eosio::public_key> encryption_key;

      uint64_t primary_key() const { return account.value; }
      uint128_t by_representative() const
      {
         return (static_cast<uint128_t>(election_rank) << 64) | representative.value;
      }
    };
    EOSIO_REFLECT(member_v0, account, name, status, nft_template_id)

    // - A member can donate at any time after the end of a scheduled election and before
    //   the start of the next scheduled election.
    // - A member who does not make a donation before the election starts will be deactivated.
    //
    struct member_v1 : member_v0
    {
    };
    EOSIO_REFLECT(member_v1,
                    base member_v0,
                    election_participation_status,
                    election_rank,
                    representative,
                    encryption_key);

    using member_variant = std::variant<member_v0, member_v1>;

    struct member
    {
        member_variant value;
        EDEN_FORWARD_MEMBERS(value,
                            account,
                            name,
                            status,
                            nft_template_id,
                            election_participation_status,
                            election_rank,
                            representative,
                            encryption_key);
        EDEN_FORWARD_FUNCTIONS(value, primary_key, by_representative)
    };
    EOSIO_REFLECT(member, value)
    using member_table_type = eosio::multi_index<"member"_n, member>;


    struct genesisdeden : public eosio::contract {
        // Use the base class constructors
        using eosio::contract::contract;

        genesisdeden(name receiver, name code, datastream<const char *> ds) :
            contract(receiver, code, ds) {}
        
        /**
        *
        *  Saves the info related with a sponsor within a community
        *
        * @param user - Voter account name
        */
        void addaccount(name account);


        /**
        *
        * Saves the info related with a sponsor within a community
        * 
        * @param name - Accout name to be set full eden
        *
        */
        void setfulleden(name account);
        
        /**
        *
        * Stores the rate stats within stats table
        * for a specific block producer
        *
        * @param name - Accout name to be set non eden
        *
        */
        void setinactive (name account);
    };

    EOSIO_ACTIONS(
        genesisdeden,
        "genesisdeden"_n,
        action(addaccount, account),
        action(setfulleden, account),
        action(setinactive, account)
    )
                 
} // namespace eoscostarica