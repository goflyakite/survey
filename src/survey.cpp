#include <eosio/eosio.hpp> 
#include <eosio/system.hpp>

using namespace eosio;

CONTRACT survey : public contract {
  public:
    using contract::contract;

    ACTION hi( name user ) {
        print( "Hello there, ", user, " value is ", user.value);
        check( user != name( "bob" ), "I only fail with bob.");
        if ( user.value == 3773036822876127232) {
          print ("\nHello Alice!");
        } else {
          print ("\nYou are not Alice!");
        }

        survey_index survey(get_self(), get_self().value );
        //                  ^Code       ^Scope
        //              vPayer       v Lamba fn
        survey.emplace( get_self(), [&]( auto& new_row) {
          new_row.subject = user;
          new_row.timestamp = current_time_point();
        });
    };

  private:
    //struct [[eosio::table]] survey_record {
    // FYI: the above line is the same as the below line. Pick one.
    TABLE survey_record { 
        name subject;
        eosio::time_point timestamp;

        uint64_t primary_key() const { return subject.value; }
        EOSLIB_SERIALIZE(survey_record, (subject)(timestamp))
    };

    typedef eosio::multi_index<name("survey"), survey_record> survey_index;
    //FYI: This following statement does exactly the same as the one above.
    //using survey_index=eosio::multi_index<name("survey"), survey_record>;

    //something_index _something; 
};