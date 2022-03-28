#include <map>

template <class IdentifierType, class AbstractProduct>
class DefaultFactoryError
{
public:
    class Exception : public std::exception
    {
    public:
        Exception(const IdentifierType &unknownId) : unknownId_(unknownId)
        {
        }
        virtual const char *what() const throw()
        {
            return "Unknown object type passed to factory.\n";
        }
        const IdentifierType GetId()
        {
            return unknownId_;
        }

    private:
        IdentifierType unknownId_;
    };

public:
    AbstractProduct *OnUnknownType(const IdentifierType &id)
    {
        throw Exception(id);
    }
};

template <
    class AbstractProduct,
    class IdentifierType,
    class ProductCreator = AbstractProduct *(*)(),
    template <typename, class>
    class FactoryErrorPolicy = DefaultFactoryError>
class Factory : FactoryErrorPolicy <IdentifierType, AbstractProduct>
{
public:
    bool Register(const IdentifierType &id, ProductCreator creator)
    {
        return associations_.insert(typename AssocMap::value_type(id, creator)).second;
    }
    bool Unregister(const IdentifierType &id)
    {
        return associations_.erase(id) == 1;
    }
    AbstractProduct *CreateObject(const IdentifierType &id)
    {
        typename AssocMap::const_iterator i = associations_.find(id);
        if (i != associations_.end())
        {
            return (i->second)();
        }
        return this->OnUnknownType(id);
    }

private:
    typedef std::map<IdentifierType, ProductCreator> AssocMap;
    AssocMap associations_;
};