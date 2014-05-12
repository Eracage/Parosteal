#include <UtH/Engine/TMX/ObjectGroup.hpp>

#include <tinyxml2.h>

using namespace uth;
using namespace TMX;

ObjectGroup::ObjectGroup(tinyxml2::XMLElement* objectGroupElement)
{
    parseObjectGroup(objectGroupElement);
}

ObjectGroup::~ObjectGroup()
{
    m_types.clear();

    for(auto it = m_objects.begin(); it != m_objects.end(); ++it)
		delete (*it).second;
}


// Public

const Object* ObjectGroup::GetObject(const std::string& name) const
{
    auto object = m_objects.find(name);
    if(object != m_objects.end())
        return object->second;

    return nullptr;
}

const ObjectGroup::ObjectList* ObjectGroup::GetObjectsByType(const std::string& type) const
{
    auto objects = m_types.find(type);

    if(objects != m_types.end())
        return &objects->second;

    return nullptr;
}

// Private

void ObjectGroup::parseObjectGroup(tinyxml2::XMLElement* element)
{
    // Parse properties
    m_name = element->Attribute("name");
    m_width = element->UnsignedAttribute("width");
    m_height = element->UnsignedAttribute("height");

    auto properties = element->FirstChildElement("properties");
    if(properties != nullptr)
    {
        parseProperties(properties);
    }

    // Parse objects
    auto objectElement = element->FirstChildElement("object");
    while(objectElement != nullptr)
    {
        auto object = new Object(objectElement);

        m_objects[object->GetName()] = object;
        m_types[object->GetType()].push_back(object);

        objectElement->NextSiblingElement("object");
    }
}

void ObjectGroup::parseProperties(tinyxml2::XMLElement* element)
{
    auto p = element->FirstChildElement("property");
	while(p != nullptr)
	{
		std::pair<std::string, std::string> tmp;
		tmp.first = p->Attribute("name");
		tmp.second = p->Attribute("value");

		m_properties.insert(tmp);

		p = p->NextSiblingElement("property");
	}
}
