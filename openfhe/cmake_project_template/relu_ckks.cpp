#include "relu_ckks.h"

ReluCKKS::ReluCKKS(std::string ccLocation, std::string pubKeyLocation, std::string multKeyLocation,
                       std::string rotKeyLocation,
                       std::string inputLocation,
                       std::string outputLocation)
    : m_PubKeyLocation(pubKeyLocation),
      m_MultKeyLocation(multKeyLocation),
      m_RotKeyLocation(rotKeyLocation),
      m_CCLocation(ccLocation),
      m_InputLocation(inputLocation),
      m_OutputLocation(outputLocation)
{
    initCC();
};

void ReluCKKS::initCC()
{
    if (!Serial::DeserializeFromFile(m_CCLocation, m_cc, SerType::JSON))
    {
        std::cerr << "Could not deserialize cryptocontext file" << std::endl;
        std::exit(1);
    }

    if (!Serial::DeserializeFromFile(m_PubKeyLocation, m_PublicKey, SerType::JSON))
    {
        std::cerr << "Could not deserialize public key file" << std::endl;
        std::exit(1);
    }

    std::ifstream multKeyIStream(m_MultKeyLocation, std::ios::in | std::ios::binary);
    if (!multKeyIStream.is_open())
    {
        std::exit(1);
    }
    if (!m_cc->DeserializeEvalMultKey(multKeyIStream, SerType::JSON))
    {
        std::cerr << "Could not deserialize rot key file" << std::endl;
        std::exit(1);
    }

    std::ifstream rotKeyIStream(m_RotKeyLocation, std::ios::in | std::ios::binary);
    if (!rotKeyIStream.is_open())
    {
        std::exit(1);
    }

    if (!m_cc->DeserializeEvalAutomorphismKey(rotKeyIStream, SerType::JSON))
    {
        std::cerr << "Could not deserialize eval rot key file" << std::endl;
        std::exit(1);
    }

    if (!Serial::DeserializeFromFile(m_InputLocation, m_InputC, SerType::JSON))
    {
        std::exit(1);
    }
}

void ReluCKKS::eval()
{
}

void ReluCKKS::serializeOutput()
{
    if (!Serial::SerializeToFile(m_OutputLocation, m_OutputC, SerType::JSON))
    {
        std::cerr << " Error writing ciphertext 1" << std::endl;
    }
}