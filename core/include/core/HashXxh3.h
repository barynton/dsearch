#include <memory>
#include <stdexcept>

// #include <xxh3.h>
#include <xxhash.h>

namespace core {

struct Xxh3StateDeleter
{
    void operator()(XXH3_state_t * state) { XXH3_freeState(state); }
};

class HashXxh3 {
public:
    typedef std::unique_ptr<XXH3_state_t, Xxh3StateDeleter> StatePtr;
    HashXxh3() {
        _state = StatePtr(XXH3_createState());
        
        if (!_state) {
            throw std::runtime_error("can't create xxh3 state");
        }

        if (XXH3_64bits_reset(_state.get()) == XXH_ERROR) {
            throw std::runtime_error("can't reset xxh3 state");
        }
    }

    void update(const std::vector<int8_t> & data) {
        if (data.empty()) {
            return;
        }

        if (XXH3_64bits_update(_state.get(), data.data(), data.size()) == XXH_ERROR) {
            throw std::runtime_error("xx3 update error");
        }
    }

    void update(const std::string & data) {
        if (XXH3_64bits_update(_state.get(), data.data(), data.size()) == XXH_ERROR) {
            throw std::runtime_error("xx3 update error");
        }
    }

    int64_t digest() {
        XXH64_hash_t hash = XXH3_64bits_digest(_state.get());
        return hash;
    }

private:
    StatePtr _state;
};

}
