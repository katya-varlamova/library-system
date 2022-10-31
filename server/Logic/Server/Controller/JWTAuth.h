//
// Created by Екатерина on 29.09.2022.
//

#ifndef SRC_JWTAUTH_H
#define SRC_JWTAUTH_H
#include <jwt-cpp/jwt.h>
#define KEY "secret"
class JWTAuth
{
public:
    JWTAuth() = default;
    std::string createToken(const std::string &login, const std::string &role)
    {
        return  jwt::create()
                .set_issuer(login)
                .set_payload_claim("role", jwt::claim(std::string(role)))
                .set_type("JWS")
                .sign(jwt::algorithm::hs256{KEY});
    }
    bool checkToken(const std::string &token)
    {
        try {
            auto decoded = jwt::decode(token);

            auto verifier = jwt::verify()
                    .allow_algorithm(jwt::algorithm::hs256{KEY})
                    .with_issuer(decoded.get_issuer());
            verifier.verify(decoded);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
    std::string getLogin(const std::string &token)
    {
        auto decoded = jwt::decode(token);
        return decoded.get_issuer();
    }
    std::string getRole(const std::string &token)
    {
        auto decoded = jwt::decode(token);
        for(auto& e : decoded.get_payload_claims())
            if (e.first == "role")
                return e.second.as_string();
        return "";
    }

};


#endif //SRC_JWTAUTH_H
