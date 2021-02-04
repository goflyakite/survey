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
          print ("\You are not Alice!");
        }
    };

  private:
  
};