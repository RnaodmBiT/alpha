#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <map>
#include <chaiscript.hpp>

class IComponent {
public:
    virtual ~IComponent() { }
};


typedef int ActorID;


class Actor {
public:

    template <typename T>
    T* GetComponent() {
        for (auto& c : components) {
            T* ptr = dynamic_cast<T*>(c.get());
            if (ptr) {
                return ptr;
            }
        }
        return nullptr;
    }

    ActorID GetID() const {
        return id;
    }

private:
    ActorID id;
    std::vector<std::unique_ptr<IComponent>> components;

    void AddComponent(IComponent* component) {
       components.emplace_back(component);
    }

    friend class ActorFactory;
};


class ActorFactory {
public:
    typedef std::function<IComponent*(const json::JSON&)> ComponentCreator;

    ActorFactory() : nextID(0) { }

    void AddCreator(const std::string& name, ComponentCreator creator) {
        creators[name] = creator;
    }

    Actor* CreateActor(const json::JSON& desc) {
        Actor* actor = new Actor();
        actor->id = nextID++;

        for (auto keyValue : desc.object_range()) {
            IComponent* component = CreateComponent(keyValue.first, keyValue.second);
            if (component) {
                actor->AddComponent(component);
            } else {
                delete actor;
                return nullptr;
            }
        }

        return actor;
    }


private:

    IComponent* CreateComponent(const std::string& type, const json::JSON& node) {
        return creators.count(type) ? creators[type](node) : nullptr;
    }

    std::map<std::string, ComponentCreator> creators;
    ActorID nextID;
};

