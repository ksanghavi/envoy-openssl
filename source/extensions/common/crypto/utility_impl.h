#pragma once

#include "common/crypto/utility.h"

#include "openssl/evp.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"

#include "boringssl_compat/cbs.h"

namespace Envoy {
namespace Common {
namespace Crypto {

class UtilityImpl : public Envoy::Common::Crypto::Utility {
public:
  std::vector<uint8_t> getSha256Digest(const Buffer::Instance& buffer) override;
  std::vector<uint8_t> getSha256Hmac(const std::vector<uint8_t>& key,
                                     absl::string_view message) override;
  const VerificationOutput verifySignature(absl::string_view hash, CryptoObject& key,
                                           const std::vector<uint8_t>& signature,
                                           const std::vector<uint8_t>& text) override;
  CryptoObjectPtr importPublicKey(const std::vector<uint8_t>& key) override;

private:
  const EVP_MD* getHashFunction(absl::string_view name);
};

std::unique_ptr<Crypto::ScopedUtilitySingleton> utility_ =
    std::make_unique<Crypto::ScopedUtilitySingleton>(std::make_unique<Crypto::UtilityImpl>());

} // namespace Crypto
} // namespace Common
} // namespace Envoy
