#include "../include/genesisdeden.hpp"


namespace eoscostarica {
    void genesisdeden::addaccount(name account) {
        require_auth(account);

        member_table_type member_tb(_self, 0);

        member_tb.emplace(account, [&](auto& row) {
         row.account() = account;
         row.status() = member_status::pending_membership;
         row.nft_template_id() = 0;
      });
    }

    void genesisdeden::setfulleden(name account) {
        require_auth(account);

        member_table_type member_tb(_self, 0);

        auto itr = member_tb.find(account.value);
        check( itr != member_tb.end(), "Account doesn't exist" );

        member_tb.modify(itr, account, [&](auto& row) {
            row.status() = member_status::active_member;
        });
    }

    void genesisdeden::setinactive (name account) {
        require_auth(account);

        member_table_type member_tb(_self, 0);

        auto itr = member_tb.find(account.value);
        check( itr != member_tb.end(), "Account doesn't exist" );

        member_tb.modify(itr, account, [&](auto& row) {
            row.status() = member_status::pending_membership;
        });
    }

} // namespace eoscostarica


EOSIO_ACTION_DISPATCHER(eoscostarica::actions)

EOSIO_ABIGEN(
    actions(eoscostarica::actions),
    table("member"_n, eoscostarica::member)
)
